#include "config.h"

int tiempo_rocio = TIEMPO_ROCIO;
int contador_rociadas = 0;

void setup() {
  attachInterrupt(digitalPinToInterrupt(PIN_ENTER, boton, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_PRESENCIA, rociar, RISING));
  pinMode(PIN_ASPERSOR, OUTPUT);
  pinMode(PIN_NIVEL, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void boton() {
}

void rociar()
{  
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > GUARDA_RUIDO)
  {
    if(digitalRead(PIN_NIVEL) == BUEN_NIVEL)
    {
      detachInterrupt(digitalPinToInterrupt(PIN_ENTER);
      // Este bloque es atómico (bloqueante) a propósito, no cambiar
      digitalWrite(PIN_ASPERSOR, HIGH);
      delay(tiempo_rocio);
      digitalWrite(PIN_ASPERSOR, LOW);
      contador_rociadas++;
      delay(GUARDA_PROCESO);
      // Fin del bloque atómico
      attachInterrupt(digitalPinToInterrupt(PIN_ENTER, boton, FALLING);
    } 
    else 
    {
      alarma_nivel();
    } 
  }
}

void alarma_nivel() {
}
