#include "main.h" 

//const unsigned char str[] = "Hello word";
const char *str = "Hello word";

int main(){

	gpio_en();
	spi_en();
	Hard_PWM();
	//яркость подсветки экрана от 0 до 100
	lcd_brightness(80);
	lcd_init(0x37);
		
	lcd_clear();
	lcd_cursor(0,0); // установка координат для вывода текста
	LCD_write_string("Hello word!!!");
	
		while(1)
    {
			
		}
}
