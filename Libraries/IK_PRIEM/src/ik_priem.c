#include "ik_priem.h" 
//---------------------------------------------------
// pult 1
//---------------------------------------------------
#define BUTTON_0				0x0687CBFC
#define BUTTON_1				0x0687CBF0
#define BUTTON_2				0x0687CBC8
#define BUTTON_3				0x0687CBE8
#define BUTTON_4				0x0687CBF8
#define BUTTON_5				0x0687CBC4
#define BUTTON_6				0x0687CBE4
#define BUTTON_7				0x0687CBF4
#define BUTTON_8				0x0687CBCC
#define BUTTON_9				0x0687CBEC

#define BUTTON_CATV			0x0687CBDC
#define BUTTON_VIDEO		0x0687CBE2
#define BUTTON_AUDIO		0x0687CBEA
#define BUTTON_POWER		0x0687CBC0
#define BUTTON_AV				0x0687CBC6
#define BUTTON_FULLS		0x0687CBD0
#define BUTTON_STEREO		0x0687D7AC
#define BUTTON_MUTE			0x0687CBF6
#define BUTTON_VOLUP		0x0687CBCA
#define BUTTON_VOLDOW		0x0687CBFA
#define BUTTON_CHUP			0x0687CBD2
#define BUTTON_CHDOW		0x0687CBF2
#define BUTTON_RECALL		0x0687CBD8
#define BUTTON_ENTER		0x0687CBC2

//-----------------------------------------------------------------------
void LEDs_ini(void)
{
	GPIO_InitTypeDef GPIO_Init_Led;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_Init_Led.GPIO_Pin = LED;	
	GPIO_Init_Led.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init_Led.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(PORTC, &GPIO_Init_Led);
	GPIO_SetBits(PORTC, LED);
}

//-----------------------------------------------------------------------
uint16_t capture_data[256]={0};
uint8_t capture_data_w=0;
uint16_t capture_data_2[256]={0};

uint32_t IR_data=0;
uint32_t IR_data2[24]={0};
uint8_t IR_data_counter=0;
uint8_t IR_data_counter2=0;

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_CC1) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
		capture_data[capture_data_w] = TIM_GetCapture1(TIM2);
		capture_data_2[capture_data_w] = capture_data[capture_data_w] - capture_data[capture_data_w-1];
		
		if((capture_data_2[capture_data_w] > 490) && (capture_data_2[capture_data_w] < 520))
		{
			IR_data=0;//115 225
			IR_data_counter=0;
		} else if((capture_data_2[capture_data_w] > 100) && (capture_data_2[capture_data_w] < 125))
		{
			if(IR_data_counter < 32)
			{
				IR_data=IR_data<<1;
				IR_data_counter++;
			}
		} else if((capture_data_2[capture_data_w] > 210) && (capture_data_2[capture_data_w] < 240))
		{
			if(IR_data_counter < 32)
			{
				IR_data=(IR_data<<1)|1;
			  IR_data_counter++;
			}
		}
		
		if(IR_data_counter == 32)
		{
//			IR_data2[IR_data_counter2] = IR_data;
//			IR_data_counter2++;
			if(IR_data == BUTTON_1)
			{
				//GPIO_SetBits(PORTC, LED);
				GPIO_ResetBits(PORTC, LED);
			} else if(IR_data == BUTTON_2)
			{
				GPIO_SetBits(PORTC, LED);
				//GPIO_ResetBits(PORTC, LED);
			}
			IR_data_counter++;
		}
		
		capture_data_w++;
	}
}

//-----------------------------------------------------------------------
void pult_ini(void)
{
	GPIO_InitTypeDef					GPIO_Init_Led;
	TIM_TimeBaseInitTypeDef		Tim_user_ini;
	TIM_ICInitTypeDef					TIM_ICInit_user;
	RCC_ClocksTypeDef					RCC_ClocksType_user;
	
	RCC_GetClocksFreq(&RCC_ClocksType_user);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_Init_Led.GPIO_Pin = GPIO_Pin_0;	
	GPIO_Init_Led.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init_Led.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_Init_Led);	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	Tim_user_ini.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_user_ini.TIM_CounterMode = TIM_CounterMode_Up;
	Tim_user_ini.TIM_Period = 0xFFFF;
	Tim_user_ini.TIM_Prescaler = 720-1;
	
	TIM_TimeBaseInit(TIM2, &Tim_user_ini);
	
	TIM_ICInit_user.TIM_Channel = TIM_Channel_1;
	TIM_ICInit_user.TIM_ICFilter = 4;
	TIM_ICInit_user.TIM_ICPolarity = TIM_ICPolarity_Rising;
  //	TIM_ICInit_user.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICInit_user.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInit_user.TIM_ICSelection = TIM_ICSelection_DirectTI;
	
	TIM_ICInit(TIM2, &TIM_ICInit_user);
	
	NVIC_EnableIRQ(TIM2_IRQn);
	
	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
	
	TIM_Cmd(TIM2, ENABLE);
}

