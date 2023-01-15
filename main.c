#include "lib/include.h"
//volatile float valor,valor1;
//volatile uint16_t Result[2];
//volatile uint16_t duty;
//volatile uint16_t duty2;
//volatile uint16_t duty3;
//uint16_t count;
int main(void)
{
    //Experimento 1
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 50,000,000 Hz
 * junto con el generador 1  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 10KHz
 */
    Configurar_PLL(_50MHZ);  //Confiuracion de velocidad de reloj - SE CAMBIA POR CADA EXPERIMENTO 
    // Configurar_UART0();//Yo FCLK 20MHZ Baudrate 9600
    //Configura_Reg_ADC0();
    Configura_Reg_PWM1(8);
    
    //Experimento 0
    // count = 0;
    //duty=15999;
    //duty2=15999;
    // duty3=15999;

    while (1)
    {
        
    }
    
}

 