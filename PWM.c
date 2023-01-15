
#include "lib/include.h"

extern void Configura_Reg_PWM1(uint16_t freq)
{
  //Experimento 1
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 50,000,000 Hz
 * junto con el generador 1  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 10KHz
 */

// AQUI UNICAMENTE SE CONFIGURA EL PWM EN ESTE EXPERIMENTO, UNICAMENTE SE VE LA SALIDA EN UN OSCILOSCOPIO EN EL PB4

    /*SE ESTA TRABAJANDO CON EL PB4 Y PWM2 Y MODULO 0 */
    /*SE HABILITA MODULO PWM0 P. 354*/
    SYSCTL->RCGCPWM |= (1<<0); 

    /*HABILITA GPIO PUERTO B PORQUE SE TRABAJA COON GEN. 1 MODULO 0, P. 340 Y 1233 PARA SABER QUE PUERTOS/PINEA CORRESPONDE A CADA PWM*/
    SYSCTL->RCGCGPIO |= (1<<1); /*Enable reloj de GPIO Puerto F pag 340 pin 5*/

    /*ENABLE O DISABLE DIVIRSOR P. 254*/
    SYSCTL->RCC &= ~(1<<20);  /*PORQUE SALEN 5MIL CUENTAS QUE CABEN EN 16 BITS DEL CONTADOR DEL PWM, 50 MILLONES/10MIL = 5 MIL CUENTAS*/
    // frecuencia, tarjeta/ frecuencia PWM = cuentas
    // si cabe en los 16 bits del PWM

   // GPIOF->AFSEL |= (1<<3)|(1<<2)|(1<<1); /*Control de registros ya sea por GPIO o Otros Pag 672*/
    GPIOB->AFSEL |= (1<<4); /*POR SER PWM0*/

    GPIOB -> DIR = (1<<4); //EL PIN B4 ES SALIDA 

    /*SE PONE UN 4 EN EL LUGAR 4 POR EL AFSEL Y LAS TABLAS DE LA 1351 Y 689*/
    GPIOB->PCTL |= (GPIOB->PCTL&0xFFF0FFFF) | 0x00040000; /*Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689*/
    

    GPIOB->DEN |= (1<<4); /* para decirle si es digital o no Pag 682 - solo el 4*/
    
    /*P. 1266 el bit 0 indica el modo habilitado o deshabilitado */
    PWM0->_1_CTL = (0<<0);/*Bloqueo y desbloqueo, SE DESACTIVA EL GENERADOR 1, LO DESABILITA PARA CONFIGURARLO p. 1266*/
    
    /*MODO DE TRABAJO - CUENTA REGRSIVA P. 1285 Y 1239 PARA SABER EL VALOR QUE SE USARA*/
    // P. 1248 para comparador para el pwm a usar 
    //PWM0->_1_GENB = 0x0000080C; /*Registro de las acciones del pwm Pag 1285*/
    PWM0->_1_GENA = 0x0000008C; /*Registro de las acciones del pwm Pag 1282 Y P. 1239 PARA 08C o 80C*/
    /*PARA GENERADOR CON PWM P. 1248 - PARA MODO REGRSIVO EL 8 */

    // CONFIGURACION DE CARGAS 
    PWM0->_1_LOAD = 5000; /*cuentas = fclk/fpwm  para 1khz cuentas = (50,000,000/10,000)*/

    //PWM0->_1_CMPB = 3750; /*25% DE LAS CUENTA DE TRABAJO */
    PWM0->_1_CMPA = 3750; //ciclo de trabajo 

    PWM0->_1_CTL = (1<<0);// Se activa el generador 1 para ser usado 

    PWM0->ENABLE = (1<<2); /*habilitar el bloque para que pase Pag 1247 y 1233*/
}
