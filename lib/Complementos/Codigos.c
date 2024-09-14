#include <Arduino.h>
#include "Macros.h"


//•••Funciones_Integrado••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
void PuertoSalida(void){
     DDRB |= (1 << PB3); 
}
//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
void PulsoClock(void)
{
  PORTB |= (1 << PB1);  // Le mando un 1 al pulso de clock
  PORTB &= ~(1 << PB1); // Le mando un 0 al pulso de clock
}
//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
void SeteoPulsoClock(void)
{
  PORTB |= (1 << PB0);  // Le mando un 1 al Latch que setea el clock
  PORTB &= ~(1 << PB0); // Le mando un 0 al Latch que setea el clock
}
//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
void EnviarDatos74HC595(uint8_t datos)
{
  for (uint8_t i = 0; i < 8; ++i)
  {
    if ((datos & 0x80) == 0)
    {
      PORTD &= ~(1 << PB2); // Limpiar el bit de datos
    }
    else
    {
      PORTD |= (1 << PB2); // Establecer el bit de datos
    }
    PulsoClock(); // Pulso de reloj
    datos <<= 1;  // Desplazar los datos un bit hacia la izquierda
  }
  SeteoPulsoClock(); // Latch para transferir los datos al registro del 74HC595
}
//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
void RegistrarShifteo(uint8_t numero)
{
  EnviarDatos74HC595(numero); //envio los bits al Integrado
}
//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
void config_TIMER0(void) //configuramos el timer para que podamos utilizar las interrupciones
{

  TCCR0A = 0b00000010; // CTC
  TCCR0B = 0b00000011; // clk/64
  OCR0A = 249;
  TIMSK0 = (1 << OCIE0A);
  /*
  16 Mhz
  16 Mhz / 8 = 2Mhz(500nS)  desborda max cada = 128useg
  16 Mhz / 64 = 250Khz  desborda max cada = 1.024mseg
  16 Mhz / 256 = 62500hz  desborda max cada = 4.096mseg
  16 Mhz / 1024 = 15625hz  desborda max cada = 16.384mseg

  250Khz(4useg)
  1mseg/4uSeg = 250cuentas
  */
}

