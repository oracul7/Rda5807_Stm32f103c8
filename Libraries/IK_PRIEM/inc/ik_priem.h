#ifndef __IK_PRIEM_H
#define __IK_PRIEM_H
//--------------------------------------------------------------
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "main.h" 

#define PORTC GPIOC
#define LED		GPIO_Pin_13	//PC13 LED

void LEDs_ini(void);
void pult_ini(void);
void TIM2_IRQHandler(void);

//--------------------------------------------------------------
#endif // __IK_PRIEM_H
