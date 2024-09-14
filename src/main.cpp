#include <Arduino.h>
#include "Macros.h"
#include "Codigos.c"
#include "DefinicionesVariables.c"


int main(){
  
 PuertoSalida();

EnviarDatos74HC595(Numeros[3]);
RegistrarShifteo(Numeros[2]);
  config_TIMER0(); // configuro el Timer0
  sei();           // habilita las interrupciones
}











ISR(TIMER0_COMPA_vect) {
}
