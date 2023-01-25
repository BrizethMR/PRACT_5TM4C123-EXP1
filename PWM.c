
#include "lib/include.h"

extern void Configura_Reg_PWM1(uint16_t freq)
{
  //Experimento 1
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 50,000,000 Hz
 * junto con el generador 1  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 10KHz
 */

// AQUI UNICAMENTE SE CONFIGURA EL PWM EN ESTE EXPERIMENTO, SE VE LA SALIDA EN UN OSCILOSCOPIO EN EL PB4

// SE TRABAJA CON MODULO 0 Y GENERADOR 1
/* p. 1233 SE PUEDE TRABAJAR CON:
    - PB4 -> PWM2
    - PB5 -> PWM3*/

/*SE ESTA TRABAJANDO CON EL PB4 Y PWM2 Y MODULO 0 */

/*SE HABILITA MODULO PWM0 P. 354*/
SYSCTL->RCGCPWM |= (1<<0); 

/*HABILITA GPIO PUERTO B PORQUE SE TRABAJA COON GEN. 1 MODULO 0, P. 340 Y 1233 PARA SABER QUE PUERTOS/PINES CORRESPONDE A CADA PWM*/
// EN p. 1233 . PWM0, MODULO O 
// p. 1233 se indica el pwm, el modulo y generador con el que se trabaja 
SYSCTL->RCGCGPIO |= (1<<1); 

/*ENABLE O DISABLE DIVIRSOR P. 254*/
SYSCTL->RCC &= ~(1<<20);  /*PORQUE SALEN 5MIL CUENTAS QUE CABEN EN 16 BITS DEL CONTADOR DEL PWM, 50 MILLONES/10MIL (10mil por exp) = 5 MIL CUENTAS*/
// frecuencia tarjeta/ frecuencia PWM = cuentas
// si cabe en los 16 bits (65536) del PWM - NO SE USA DIVISOR 

// SE HABILITA LA FUNCION ALTERNATIVA PARA PB4
// GPIOF->AFSEL |= (1<<3)|(1<<2)|(1<<1); /*Control de registros ya sea por GPIO u otros Pag 672*/
GPIOB->AFSEL |= (1<<4); /*POR SER PWM0*/

// SE INDICA PB4 COMO SALIDA
GPIOB -> DIR = (1<<4);  

/*SE PONE UN 4 EN EL LUGAR 4 POR EL AFSEL Y LAS TABLAS DE LA 1351 Y 689*/
GPIOB->PCTL |= (GPIOB->PCTL&0xFFF0FFFF) | 0x00040000; 
    
// SE HABILITA COMO DIGITAL
GPIOB->DEN |= (1<<4); /* para decirle si es digital o no Pag 681 - solo el pin 4*/
    
/*P. 1266 el bit 0 indica el modo habilitado o deshabilitado */
PWM0->_1_CTL = (0<<0);/*Bloqueo y desbloqueo, SE DESACTIVA EL GENERADOR 1, LO DESABILITA PARA CONFIGURARLO p. 1266*/
// SE SABE CON QUE GENERADOR TRABAJA POR LA p. 1233

/*MODO DE TRABAJO - CUENTA REGRSIVA P. 1285 Y 1239 PARA SABER EL VALOR QUE SE USARA*/
// P. 1248 para comparador para el pwm a usar - PARA PWM2 SE USA COMPA
PWM0->_1_GENA = 0x0000008C; /*Registro de las acciones del pwm Pag 1282 Y P. 1239 PARA 08C o 80C*/
//PARA GENERADOR CON PWM P. 1248 - PARA MODO REGRSIVO EL 8 
//PARA GENERADOR A - 8C

// CONFIGURACION DE CARGAS 
//cuentas = fclk/fpwm  para 10khz cuentas = (50,000,000/10,000) = 5000
PWM0->_1_LOAD = 5000;

//PWM0->_1_CMPB = 3750; 
// 25% DE LAS CUENTAS DE TRABAJO - 75% DE LAS 5000 CUENTAS TOTALES
PWM0->_1_CMPA = 3750; //ciclo de trabajo 

PWM0->_1_CTL = (1<<0);// Se activa el generador 1 para ser usado 

// SE HABILITA EL PWM (PWM2) - p. 1233 y 1247
PWM0->ENABLE = (1<<2); //habilitar el bloque para que pase 
}
