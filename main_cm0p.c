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
#include "sys/time.h"

#define US_IN_SEC 1000000

volatile uint8 inputControlsPtr[1] = {0};
volatile uint8 transmissionReceived = 0;
volatile uint8 resetControls = 0;
volatile uint16 pulseWidthUS = 0;
volatile uint8 echoProcessed = 0;
volatile uint8 gpsReceived = 0;

uint8 left_bit = 0;
uint8 right_bit = 0;
uint8 trash_bit = 0;
uint8 accelerate_bit = 0;
uint8 reverse_bit = 0;

cy_stc_ble_conn_handle_t connHandle;

void genericEventHandler(uint32_t event, void *eventParameter) {
    switch(event) {
        case CY_BLE_EVT_STACK_ON:
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED: {
            // resetControls = 1;
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            break;
        }
        case CY_BLE_EVT_GATT_CONNECT_IND: {
            // Bluetooth connects to phone
            connHandle = *(cy_stc_ble_conn_handle_t*)eventParameter;
            break;
        }
        case CY_BLE_EVT_GATTS_WRITE_REQ: {
            // PSoC receives value from phone
            cy_stc_ble_gatts_write_cmd_req_param_t *writeReqParameter = (cy_stc_ble_gatts_write_cmd_req_param_t *) eventParameter;
            if (CY_BLE_DEVICE_INTERFACE_DEVICE_INBOUND_CHAR_HANDLE == writeReqParameter->handleValPair.attrHandle) {
                inputControlsPtr[0] = writeReqParameter->handleValPair.value.val[0];
                transmissionReceived = 1;
            }
            Cy_BLE_GATTS_WriteRsp(writeReqParameter->connHandle);
            break;
        }
    }
}

void echoHandler() {
    uint32 source = Cy_TCPWM_GetInterruptStatusMasked(Echo_Counter_HW, Echo_Counter_CNT_NUM);
    pulseWidthUS = Cy_TCPWM_Counter_GetCapture(Echo_Counter_HW, Echo_Counter_CNT_NUM);
    Cy_TCPWM_ClearInterrupt(Echo_Counter_HW, Echo_Counter_CNT_NUM, source);
    NVIC_ClearPendingIRQ(Echo_IRQ_cfg.intrSrc);
    echoProcessed = 1;
}

/*void UART_GPSHandler() {
    Cy_SCB_ClearRxInterrupt(UART_HW, CY_SCB_RX_INTR_NOT_EMPTY);
    NVIC_ClearPendingIRQ(UART_SCB_IRQ_cfg.intrSrc);
    gpsReceived = 1;
}*/

void bleInterruptNotify() {
    Cy_BLE_ProcessEvents();
}

uint8 getControls(void) {
    return inputControlsPtr[0];
}

void ble_startup() {
    Cy_BLE_Start(genericEventHandler);
    while(Cy_BLE_GetState() != CY_BLE_STATE_ON) {
        Cy_BLE_ProcessEvents();
    }
    Cy_BLE_RegisterAppHostCallback(bleInterruptNotify);
}
    
void updateUltrasonicCharacteristic(uint16 newData) {
    uint8 data[1] = {0};
    data[0] = newData;
    
    cy_stc_ble_gatt_handle_value_pair_t serviceHandle;
    cy_stc_ble_gatt_value_t serviceData;
    
    serviceData.val = data;
    serviceData.len = sizeof(newData);
    
    serviceHandle.attrHandle = CY_BLE_DEVICE_INTERFACE_ULTRASONICPULSE_CHAR_HANDLE;
    serviceHandle.value = serviceData;
    
    Cy_BLE_GATTS_WriteAttributeValueLocal(&serviceHandle);
    Cy_BLE_GATTS_SendNotification(&connHandle, &serviceHandle);
}

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR); 
  
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */    
    //start up for components
    printf("Starting up components ... ");
    UART_Start();
    ble_startup();
    PWM_fin_Start();
    PWM_trashgate_Start();
    PWM_thrustmotor_Start();
    PWM_ultrasonic_Start();
    
    int compare_val_fin = 2000; // rudder is straight
    PWM_fin_SetCompare0(compare_val_fin);
    
    int compare_val_trashgate = 1000; //trash gate closed
    PWM_trashgate_SetCompare0(compare_val_trashgate);
    
    int compare_val_thrustmotor = 1000; //thrust motor off
    PWM_thrustmotor_SetCompare0(compare_val_thrustmotor);
    
    int compare_val_ultrasonic = 15; // ultrasonic trigger is 15us wide
    PWM_ultrasonic_SetCompare0(compare_val_ultrasonic);
    
    uint8 inputControls = 0;
    
    printf("Enabling interrupts ... ");
    
    Cy_TCPWM_Counter_Init(Echo_Counter_HW, Echo_Counter_CNT_NUM, &Echo_Counter_config);
    Cy_TCPWM_Counter_Enable(Echo_Counter_HW, Echo_Counter_CNT_NUM);
    Cy_SysInt_Init(&Echo_IRQ_cfg, echoHandler);
    NVIC_EnableIRQ(Echo_IRQ_cfg.intrSrc);
    
    // Cy_SysInt_Init(&UART_SCB_IRQ_cfg, &UART_GPSHandler);
    // NVIC_EnableIRQ(UART_SCB_IRQ_cfg.intrSrc);
    
    printf("Setup complete\n");
    
    while(1) {
        /* Place your application code here. */
        //check if psoc is on w/ LED light
        // Cy_GPIO_Write(GreenLight_PORT, GreenLight_NUM, 0);
        
        /*if (resetControls > 0) {
            // printf("Reset controls\n");
            inputControls = 0;
        }*/
        
        if (echoProcessed > 0) {
            printf("Distance: %x\n", pulseWidthUS / 148);
            updateUltrasonicCharacteristic(pulseWidthUS);
            echoProcessed = 0;
        }
        
        if (gpsReceived > 0) {
            printf("Received new GPS coordinates\n");
            // unsigned char line[128];
            // TO DO: ADD MESSAGE PARSING AND TRANSMISSION PROTOCOL FOR LOCATION DATA
            // updateOutboundCharacteristic(0xFF);
            gpsReceived = 0;
        }
        
        if(transmissionReceived > 0) {
            inputControls = getControls();
            printf("User input detected: %d\n", inputControls);
            transmissionReceived = 0;
            
            left_bit = inputControls & 0x01; //check left bit first
            right_bit = (inputControls >> 1) & 0x01;
            if (left_bit == 1){
                compare_val_fin = 1650; //turn servo right to turn ROV left
            }
            else if(right_bit == 1){
                compare_val_fin = 2350; //turn servo left to turn ROV right
            }
            else{
                compare_val_fin = 2000; //rudder straight
            }
            PWM_fin_SetCompare0(compare_val_fin);
            
            trash_bit = (inputControls >> 2) & 0x01;
            if (trash_bit == 1){
                //compare_val_trashgate = 1000; //open trash gate
                PWM_trashgate_SetCompare0(2000); //open trash gate
                CyDelay(5000); //open for 5 seconds
                PWM_trashgate_SetCompare0(1000); //close gate
            }
            
            accelerate_bit = (inputControls >> 3) & 0x01;
            if (accelerate_bit == 1){
               compare_val_thrustmotor = 1500; // thrust on
            }
            else{
               compare_val_thrustmotor = 1000; // thrust off 
            }
            PWM_thrustmotor_SetCompare0(compare_val_thrustmotor);
           
            /*reverse_bit = (inputControls >> 4) & 0x01;
            if (reverse_bit == 1){
               compare_val_thrustmotor = 1000; // reverse thrust on
            }
            else{
               compare_val_thrustmotor = 0; // thrust off 
            }*/
            
        }
    }
}

/* [] END OF FILE */
