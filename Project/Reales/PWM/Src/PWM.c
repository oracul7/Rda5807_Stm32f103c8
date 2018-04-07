#include "PWM.h" 

void Hard_PWM(void)
{
	//объ€вл€ем стуктуру таймера
	TIM_TimeBaseInitTypeDef TIM_Time_user;
	TIM_OCInitTypeDef		Hard_PWM_ini;
	//объ€вл€ем стуктуру вывода
	GPIO_InitTypeDef GPIO_Init_LED;
	//включаем тактирование таймера
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//заполн€ем структуру таймера
	TIM_Time_user.TIM_Prescaler = 0;
	TIM_Time_user.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Time_user.TIM_Period = 1000;
	TIM_Time_user.TIM_ClockDivision = TIM_CKD_DIV1;
	//инициализируем таймер
	TIM_TimeBaseInit(TIM2, &TIM_Time_user);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_Init_LED.GPIO_Pin = BL;	
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_Init_LED);		
	
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE); //GPIO_FullRemap_TIM2
	
	Hard_PWM_ini.TIM_OCMode = TIM_OCMode_PWM1;
	Hard_PWM_ini.TIM_OutputState = TIM_OutputState_Enable;
	Hard_PWM_ini.TIM_Pulse = 900;
	Hard_PWM_ini.TIM_OCNPolarity = TIM_OCPolarity_High;	

	TIM_OC2Init(TIM2, &Hard_PWM_ini);
	
	//включаем таймер
	TIM_Cmd(TIM2, ENABLE);	
}
