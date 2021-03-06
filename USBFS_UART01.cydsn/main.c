/*******************************************************************************
* File Name: main.c
*
* Version: 2.0
*
* Description:
*   The component is enumerated as a Virtual Com port. Receives data from the 
*   hyper terminal, then sends back the received data.
*   For PSoC3/PSoC5LP, the LCD shows the line settings.
*
* Related Document:
*  Universal Serial Bus Specification Revision 2.0
*  Universal Serial Bus Class Definitions for Communications Devices
*  Revision 1.2
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>
#include "stdio.h"

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow usage of the floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif

#define USBFS_DEVICE    (0u)

/* The buffer size is equal to the maximum packet size of the IN and OUT bulk
* endpoints.
*/
#define USBUART_BUFFER_SIZE (64u)
#define LINE_STR_LENGTH     (20u)

char8* parity[] = {"None", "Odd", "Even", "Mark", "Space"};
char8* stop[]   = {"1", "1.5", "2"};


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  The main function performs the following actions:
*   1. Waits until VBUS becomes valid and starts the USBFS component which is
*      enumerated as virtual Com port.
*   2. Waits until the device is enumerated by the host.
*   3. Waits for data coming from the hyper terminal and sends it back.
*   4. PSoC3/PSoC5LP: the LCD shows the line settings.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
//Do not know enough about C to make this more elegant
//Each changes value of DAC
//V = ((val+2)/255)*1.020
int Handle0(int a, int b, int c){
    
    int v1 = a - 48;
    int v2 = b - 48;
    int v3 = c - 48;
    uint8 val = v1 * 100 + v2 * 10 + v3;
    VDAC8_1_SetValue(val);
    
    /* Clear LCD line.*/ 
    LCD_Position(1u, 0u);
    LCD_PrintString("    ");
    
    LCD_Position(1u, 0u);
    LCD_PrintNumber(val * 1000 / 255 * 102 / 100);
    return 0;
}
int Handle1(int a, int b, int c){
    int v1 = a - 48;
    int v2 = b - 48;
    int v3 = c - 48;
    uint8 val = v1 * 100 + v2 * 10 + v3;
    VDAC8_2_SetValue(val);
    
    /* Clear LCD line.*/ 
    LCD_Position(1u, 4u);
    LCD_PrintString("    ");
    
    LCD_Position(1u, 4u);
    LCD_PrintNumber(val * 1000 / 255 * 102 / 100);
    return 0;
}
int Handle2(int a, int b, int c){
    int v1 = a - 48;
    int v2 = b - 48;
    int v3 = c - 48;
    uint8 val = v1 * 100 + v2 * 10 + v3;
    VDAC8_3_SetValue(val);
    
    /* Clear LCD line.*/ 
    LCD_Position(1u, 8u);
    LCD_PrintString("    ");
    
    LCD_Position(1u, 8u);
    LCD_PrintNumber(val * 1000 / 255 * 102 / 100);
    return 0;
}
int Handle3(int a, int b, int c){
    int v1 = a - 48;
    int v2 = b - 48;
    int v3 = c - 48;
    uint8 val = v1 * 100 + v2 * 10 + v3;
    
    /* Clear LCD line.*/ 
    LCD_Position(1u, 12u);
    LCD_PrintString("    ");
    
    VDAC8_4_SetValue(val);
    LCD_Position(1u, 12u);
    LCD_PrintNumber(val * 1000 / 255 * 102 / 100);
    return 0;
}

//Ex: 2550 is abcd and means 255 to DAC (d+1)
int ProcessMessage(int a, int b, int c, int d){
    //Using ASCII values
    int v = d - 48;
    if(v == 0)
        Handle0(a,b,c);
    if(v == 1)
        Handle1(a,b,c);
    if(v == 2)
        Handle2(a,b,c);
    if(v == 3)
        Handle3(a, b, c);
    return 0;
}



int main()
{
    uint16 count;
    uint8 buffer[USBUART_BUFFER_SIZE];
    
#if (CY_PSOC3 || CY_PSOC5LP)
    uint8 state;
    char8 lineStr[LINE_STR_LENGTH];
    
    LCD_Start();
#endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    /* Start VDAC */
    VDAC8_1_Start();
    VDAC8_2_Start();
    VDAC8_3_Start();
    VDAC8_4_Start();
    /* Set the value 200 in VDAC data register */
    VDAC8_1_SetValue(0u);
    VDAC8_2_SetValue(0u);
    VDAC8_3_SetValue(0u);
    VDAC8_4_SetValue(0u);
    /* Initialize LCD values*/
    LCD_Position(1u, 0u);
    LCD_PrintNumber(0);
    LCD_Position(1u, 4u);
    LCD_PrintNumber(0);
    LCD_Position(1u, 8u);
    LCD_PrintNumber(0);
    LCD_Position(1u, 12u);
    LCD_PrintNumber(0);
    CyGlobalIntEnable;

    /* Start USBFS operation with 5-V operation. */
    USBUART_Start(USBFS_DEVICE, USBUART_5V_OPERATION);
    
    for(;;)
    {
        /* Host can send double SET_INTERFACE request. */
        if (0u != USBUART_IsConfigurationChanged())
        {
            /* Initialize IN endpoints when device is configured. */
            if (0u != USBUART_GetConfiguration())
            {
                /* Enumeration is done, enable OUT endpoint to receive data 
                 * from host. */
                USBUART_CDC_Init();
            }
        }

        /* Service USB CDC when device is configured. */
        if (0u != USBUART_GetConfiguration())
        {
            /* Check for input data from host. */
            if (0u != USBUART_DataIsReady())
            {
                /* Read received data and re-enable OUT endpoint. */
                count = USBUART_GetAll(buffer);

                if (0u != count)
                {
                    /* Wait until component is ready to send data to host. */
                    while (0u == USBUART_CDCIsReady())
                    {
                    }

                    /* Send data back to host. */
                    USBUART_PutData(buffer, count);
                    
                    //(val+2/255)*1.020 = V 

                    ProcessMessage(buffer[0], buffer[1], buffer[2], buffer[3]);
                    /* If the last sent packet is exactly the maximum packet 
                    *  size, it is followed by a zero-length packet to assure
                    *  that the end of the segment is properly identified by 
                    *  the terminal.
                    */
                    if (USBUART_BUFFER_SIZE == count)
                    {
                        /* Wait until component is ready to send data to PC. */
                        while (0u == USBUART_CDCIsReady())
                        {
                        }

                        /* Send zero-length packet to PC. */
                        USBUART_PutData(NULL, 0u);
                    }
                }
            }


        #if (CY_PSOC3 || CY_PSOC5LP)
            /* Check for Line settings change. */
            state = USBUART_IsLineChanged();
            if (0u != state)
            {
                /* Output on LCD Line Coding settings. */
                if (0u != (state & USBUART_LINE_CODING_CHANGED))
                {                  
                    /* Get string to output. */
                    sprintf(lineStr,"BR:%4ld %d%c%s", USBUART_GetDTERate(),\
                                   (uint16) USBUART_GetDataBits(),\
                                   parity[(uint16) USBUART_GetParityType()][0],\
                                   stop[(uint16) USBUART_GetCharFormat()]);

                    /* Clear LCD line. */
                    LCD_Position(0u, 0u);
                    LCD_PrintString("                    ");

                    /* Output string on LCD. */
                    LCD_Position(0u, 0u);
                    LCD_PrintString(lineStr);
                }

                /* Output on LCD Line Control settings. */
                if (0u != (state & USBUART_LINE_CONTROL_CHANGED))
                {                   
                    /* Get string to output. */
                    state = USBUART_GetLineControl();
                    sprintf(lineStr,"DTR:%s,RTS:%s",  (0u != (state & USBUART_LINE_CONTROL_DTR)) ? "ON" : "OFF",
                                                      (0u != (state & USBUART_LINE_CONTROL_RTS)) ? "ON" : "OFF");

                    /* Clear LCD line. */
                    //LCD_Position(1u, 0u);
                    //LCD_PrintString("                    ");

                    /* Output string on LCD. */
                    //LCD_Position(1u, 0u);
                    //LCD_PrintString(lineStr);
                }
            }
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        }
    }
}
/* [] END OF FILE */
