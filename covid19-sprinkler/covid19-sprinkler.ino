#include "config.h"

int tiempo_rocio = TIEMPO_ROCIO;
int contador_rociadas = 0;
bool primer_ingreso = true;
bool alarma = false;
int encoder_tabla[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

void setup() {
  attachInterrupt(digitalPinToInterrupt(PIN_ENTER), boton, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_PRESENCIA), rociar, RISING);
  pinMode(PIN_ASPERSOR, OUTPUT);
  pinMode(PIN_NIVEL, INPUT);
  pinMode(PIN_ENCODER_A, INPUT);
  pinMode(PIN_ENCODER_B, INPUT);

}

void loop() {
  if(digitalRead(PIN_NIVEL) == BUEN_NIVEL)
  {
    digitalWrite(PIN_ALARMA, LOW);
    alarma = false;
  }
  else
  {
    digitalWrite(PIN_ALARMA, HIGH);
    alarma = true;
  }

}

void boton() 
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > GUARDA_RUIDO)
  {
    if(primer_ingreso)
    {
      primer_ingreso =! primer_ingreso;
      int a0 = digitalRead(PIN_ENCODER_A);
      int b0 = digitalRead(PIN_ENCODER_B);
      detachInterrupt(digitalPinToInterrupt(PIN_PRESENCIA));
      // Bloque atómico, lectura de encoder
      while(true)
      {
        int a1 = digitalRead(PIN_ENCODER_A);
        int b1 = digitalRead(PIN_ENCODER_B);
        int index = a0 + (2*b0) + (4*a1) + (8*b1);
        int incremento = encoder_tabla[index];
        if( incremento < 0 && tiempo_rocio > TIEMPO_MINIMO )
        {
          tiempo_rocio--;
        } 
        else if( incremento > 0 && tiempo_rocio < TIEMPO_MAXIMO)
        {
          tiempo_rocio++;
        }
        a0 = a1;
        b0 = b1;
      }
      // Fin de bloque atómico
      attachInterrupt(digitalPinToInterrupt(PIN_PRESENCIA), rociar, RISING);
    }
    else
    {
      primer_ingreso = true;
      attachInterrupt(digitalPinToInterrupt(PIN_PRESENCIA), rociar, RISING);
    }
  }
}

void rociar()
{  
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > GUARDA_RUIDO)
  {
    if(!alarma)
    {
      detachInterrupt(digitalPinToInterrupt(PIN_ENTER));
      // Este bloque es atómico (bloqueante) a propósito, no cambiar
      digitalWrite(PIN_ASPERSOR, HIGH);
      delay(tiempo_rocio);
      digitalWrite(PIN_ASPERSOR, LOW);
      contador_rociadas++;
      delay(GUARDA_PROCESO);
      // Fin del bloque atómico
      attachInterrupt(digitalPinToInterrupt(PIN_ENTER), boton, FALLING);
    } 
  }
}
