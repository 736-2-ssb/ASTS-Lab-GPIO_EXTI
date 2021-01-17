/*******************************************************************************
* Copyright (C) 2020 TUSUR, FB, #2376  
* File              : main.cpp
* Compiler          : NetBeans
* Version           : 8.2
* Created File      : 29.09.2020
* Last modified     : 29.09.2020
*
* Support mail      : s.b_sharkova@mail.ru
*
* Target MCU        : MDR1986
*
* Description       : lab1 GPIO EXTI
*                   :
*******************************************************************************/
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include "mstn_version.h"
#include "mstn_clk.h" 
#include "mstn_led.h"
#include "mstn_usb.h"
#include "mstn_button.h"
#include "mstn_external_interrupt.h"

volatile uint8_t state;

void Interrupt() // 
{
    state = !state;
}


int main()
{
        state = 0;
        //Устанавливаем состояние вывода пользовательского зеленого светодиода
        LED_SetGreenState(state);
      
        //GPIO
        //Устанавливаем состояние вывода пользовательского красного светодиода
        LED_SetRedState(TURN_OFF);
        while (1)
        {
        if (BTN_UserButtonRead() == PRESSED)   
        {
               LED_SetRedState(TURN_ON);
               Delay(2000);
               LED_SetRedState(TURN_OFF);
               break;
        }
         }
        
        //EXTI
        //Задаем функцию обработки внешнего прерывания
    
        EINT_AttachExtInt(Interrupt,D6,CHANGE);
        while(1)
        {   
            LED_SetGreenState(state);
        }
        
        return EXIT_SUCCESS;
}
