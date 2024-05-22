/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"
#include "minmea.h"

#define US_IN_SEC 1000000

#define RUDDER_RIGHT_VAL 1650
#define RUDDER_STRAIGHT_VAL 2000
#define RUDDER_LEFT_VAL 2350
#define TRASHGATE_OPEN_VAL 2000
#define TRASHGATE_CLOSED_VAL 1000
#define THRUSTMOTOR_ON_VAL 1500
#define THRUSTMOTOR_OFF_VAL 1000

volatile uint8* inputControlsPtr;
volatile uint8 transmissionReceived = 0;
volatile uint16 pulseWidthUS = 0;
volatile uint8 newEchoPulseReceived = 0;
volatile uint8 disconnected = 0;
volatile uint8 controlsHaveBeenReset = 0;

char gpsLineBuff[MINMEA_MAX_SENTENCE_LENGTH];
uint8 gpsLineBuffSize = 0;
uint8 gpsBufferIndex = 0;
uint8 readingLine = 0;
uint8 gpsLineProcessed = 0;

cy_stc_ble_conn_handle_t connHandle;

void genericEventHandler(uint32_t event, void *eventParameter) {
    switch(event) {
        case CY_BLE_EVT_STACK_ON:
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED: {
            disconnected = 1;
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            break;
        }
        case CY_BLE_EVT_GATT_CONNECT_IND: {
            // Bluetooth connects to phone
            disconnected = 0;
            controlsHaveBeenReset = 0;
            connHandle = *(cy_stc_ble_conn_handle_t*)eventParameter;
            break;
        }
        case CY_BLE_EVT_GATTS_WRITE_REQ: {
            // PSoC receives value from phone
            cy_stc_ble_gatts_write_cmd_req_param_t *writeReqParameter = (cy_stc_ble_gatts_write_cmd_req_param_t *) eventParameter;
            if (CY_BLE_DEVICE_INTERFACE_DEVICE_INBOUND_CHAR_HANDLE == writeReqParameter->handleValPair.attrHandle) {
                inputControlsPtr = &writeReqParameter->handleValPair.value.val[0];
                transmissionReceived = 1;
            }
            Cy_BLE_GATTS_WriteRsp(writeReqParameter->connHandle);
            break;
        }
    }
}

void bleInterruptNotify() {
    uint32 source = Cy_TCPWM_GetInterruptStatusMasked(Echo_Counter_HW, Echo_Counter_CNT_NUM);
    Cy_BLE_ProcessEvents();
    Cy_TCPWM_ClearInterrupt(Echo_Counter_HW, Echo_Counter_CNT_NUM, source);
    NVIC_ClearPendingIRQ(Echo_IRQ_cfg.intrSrc);
}

void ble_startup() {
    Cy_BLE_Start(genericEventHandler);
    while(Cy_BLE_GetState() != CY_BLE_STATE_ON) {
        Cy_BLE_ProcessEvents();
    }
    Cy_BLE_RegisterAppHostCallback(bleInterruptNotify);
}

void updateCharacteristic(uint16 characteristic_handle, uint8* newBytePtr, uint8 numBytes) {
    cy_stc_ble_gatt_handle_value_pair_t serviceHandle;
    serviceHandle.attrHandle = characteristic_handle;
    
    cy_stc_ble_gatt_value_t serviceData;
    serviceData.val = newBytePtr;
    serviceData.len = numBytes;
    
    serviceHandle.value = serviceData;
    
    Cy_BLE_GATTS_WriteAttributeValueLocal(&serviceHandle);
    Cy_BLE_GATTS_SendNotification(&connHandle, &serviceHandle);
}

uint8 getControls(void) {
    return (uint8)*inputControlsPtr;
}

void echoHandler() {
    uint32 source = Cy_TCPWM_GetInterruptStatusMasked(Echo_Counter_HW, Echo_Counter_CNT_NUM);
    pulseWidthUS = Cy_TCPWM_Counter_GetCapture(Echo_Counter_HW, Echo_Counter_CNT_NUM);
    Cy_TCPWM_ClearInterrupt(Echo_Counter_HW, Echo_Counter_CNT_NUM, source);
    newEchoPulseReceived = 1;
    NVIC_ClearPendingIRQ(Echo_IRQ_cfg.intrSrc);
}

void processControls(uint8 inputControls) {
    transmissionReceived = 0;
    
    uint8 left_bit = inputControls & 0x01; // check bit for rudder left (LSB) first
    uint8 right_bit = (inputControls >> 1) & 0x01;
    uint16 compare_val_fin = 0;
    if (left_bit == 1 && right_bit == 0) {
        compare_val_fin = RUDDER_LEFT_VAL; // turn rudder servo left
    } else if (left_bit == 0 && right_bit == 1) {
        compare_val_fin = RUDDER_RIGHT_VAL; // turn rudder servo right
    } else {
        compare_val_fin = RUDDER_STRAIGHT_VAL; // rudder straight
    }
    PWM_fin_SetCompare0(compare_val_fin);
            
    uint8 trash_bit = (inputControls >> 2) & 0x01;
    if (trash_bit == 1){
        PWM_trashgate_SetCompare0(TRASHGATE_OPEN_VAL); // open trash gate
        CyDelay(5000); //open for 5 seconds
        PWM_trashgate_SetCompare0(TRASHGATE_CLOSED_VAL); // close trash gate
    }
            
    uint8 forward_bit = (inputControls >> 3) & 0x01;
    uint16 compare_val_thrustmotor = 0;
    if (forward_bit == 1){
        compare_val_thrustmotor = THRUSTMOTOR_ON_VAL; // thrust on
    } else {
        compare_val_thrustmotor = THRUSTMOTOR_ON_VAL; // thrust off 
    }
    PWM_thrustmotor_SetCompare0(compare_val_thrustmotor);
}

void removeExtraCharsFromLine() {
    for (int i = gpsBufferIndex; i < MINMEA_MAX_SENTENCE_LENGTH; i++) {
        gpsLineBuff[i] = '\0';
    }
}

void loadGPSInput() {
    while (Cy_SCB_UART_GetNumInRxFifo(UART_GPS_HW) > 0) {
        char c = Cy_SCB_UART_Get(UART_GPS_HW);
        if (c == '$') {
            gpsLineBuffSize = 0;
            readingLine = 1;
        }
        if (readingLine == 1) {
            gpsLineBuff[gpsBufferIndex] = c;
            gpsBufferIndex++;
            gpsLineBuffSize++;
        }
        if (c == '\n') {
            readingLine = 0;
            gpsLineProcessed = 0;
            removeExtraCharsFromLine();
            gpsBufferIndex = 0;
        }
    }
}

void extractAndUpdateGPSData() {
    if (minmea_sentence_id(gpsLineBuff, false) == MINMEA_SENTENCE_RMC) {
        struct minmea_sentence_rmc frame;
        if (minmea_parse_rmc(&frame, gpsLineBuff)) {
            float latitude = minmea_tocoord(&frame.latitude);
            float longitude = minmea_tocoord(&frame.longitude);
            printf("Coordinates: %f (%d), %f (%d)\n", latitude, sizeof(latitude), longitude, sizeof(longitude));
            updateCharacteristic(CY_BLE_DEVICE_INTERFACE_LATITUDE_CHAR_HANDLE, (uint8*)&latitude, sizeof(latitude));
            updateCharacteristic(CY_BLE_DEVICE_INTERFACE_LONGITUDE_CHAR_HANDLE, (uint8*)&longitude, sizeof(longitude));
            
            float heading = minmea_getheading(&frame.course);
            printf("Heading: %f\n", heading);
            updateCharacteristic(CY_BLE_DEVICE_INTERFACE_HEADING_CHAR_HANDLE, (uint8*)&heading, sizeof(heading));
        }
    }
}

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);
    Cy_GPIO_Inv(GreenLight_PORT, GreenLight_NUM);
  
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */    
    //start up for components
    UART_Start();
    printf("Starting up components ... ");
    ble_startup();
    PWM_fin_Start();
    PWM_trashgate_Start();
    PWM_thrustmotor_Start();
    PWM_ultrasonic_Start();
    
    PWM_fin_SetCompare0(RUDDER_STRAIGHT_VAL); // straighten rudder
    PWM_trashgate_SetCompare0(TRASHGATE_CLOSED_VAL); // close trash gate
    PWM_thrustmotor_SetCompare0(THRUSTMOTOR_OFF_VAL); // thrust motor off
    
    uint8 inputControls = 0;
    
    printf("Enabling interrupts ... ");
    
    /*Cy_TCPWM_Counter_Init(Echo_Counter_HW, Echo_Counter_CNT_NUM, &Echo_Counter_config);
    Cy_TCPWM_Counter_Enable(Echo_Counter_HW, Echo_Counter_CNT_NUM);
    Cy_SysInt_Init(&Echo_IRQ_cfg, echoHandler);
    NVIC_EnableIRQ(Echo_IRQ_cfg.intrSrc);*/
    
    Cy_SCB_UART_Init(UART_GPS_HW, &UART_GPS_config, &UART_GPS_context);
    Cy_SCB_UART_Enable(UART_GPS_HW);
    
    printf("Setup complete\n");
    Cy_GPIO_Inv(GreenLight_PORT, GreenLight_NUM);
    
    while(1) {
        // Check if device is disconnected and reset if needed
        if (disconnected == 1 && controlsHaveBeenReset == 0) {
            processControls(0);
            printf("CONTROLS RESET\n");
            controlsHaveBeenReset = 1;
            continue;
        }
        
        // Check UART_GPS buffer, extract data if available
        loadGPSInput();
        if (readingLine == 0 && gpsLineProcessed == 0) {
            extractAndUpdateGPSData();
            gpsLineProcessed = 1;
        }
        
        // Check if new ultrasonic pulse was read, update data if available
        if (newEchoPulseReceived > 0) {
            printf("Object ahead in: %d cm (width: %d)\n", pulseWidthUS / 58, pulseWidthUS);
            updateCharacteristic(CY_BLE_DEVICE_INTERFACE_ULTRASONICPULSE_CHAR_HANDLE, (uint8*)&pulseWidthUS, sizeof(pulseWidthUS));
            newEchoPulseReceived = 0;
        }

        // Check if new input data from phone was received, process if available
        if(transmissionReceived > 0) {
            inputControls = getControls();
            printf("Received user controls: %d\n", inputControls);
            processControls(inputControls);
        }
    }
}

/* [] END OF FILE */
