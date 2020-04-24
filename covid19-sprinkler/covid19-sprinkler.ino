#include "config.h"

int tiempo_rocio = TIEMPO_ROCIO;
int contador_rociadas = 0;
bool primer_ingreso = true;
bool alarma = false;
int encoder_tabla[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
char segunda_linea[17] = "0123456789ABCDEF";

LiquidCrystal_I2C lcd(LCD_cADDR, LCD_cCHAR, LCD_CLINE);

void setup() {
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print(SALUDO);
  lcd.setCursor(1,0);
  lcd.print(NOMBRE_FABRICANTE);
  delay(TIEMPO_SALUDO);
  
  mensaje_inicio();
  lcd.clear();
  lcd.print(NOMBRE_CLIENTE);
  lcd.setCursor(1,0);
  lcd.print(segunda_linea);
  
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
    if(alarma)
    {
      digitalWrite(PIN_ALARMA, LOW);
      mensaje_inicio();
      lcd.clear();
      lcd.print(NOMBRE_CLIENTE);
      lcd.setCursor(0,1);
      lcd.print(segunda_linea);
      alarma = false;
    }
  }
  else
  {
    digitalWrite(PIN_ALARMA, HIGH);
    alarma = true;
    lcd.setCursor(0,0);
    lcd.print(ALARMA_NIVEL);
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
      mensaje_configuracion();
      lcd.clear();
      lcd.print(CONFIGURACION);
      lcd.setCursor(0,1);
      lcd.print(segunda_linea);
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
        mensaje_configuracion();
        lcd.setCursor(0,1);
        lcd.print(segunda_linea);
        a0 = a1;
        b0 = b1;
      }
      // Fin de bloque atómico
      attachInterrupt(digitalPinToInterrupt(PIN_PRESENCIA), rociar, RISING);
    }
    else
    {
      primer_ingreso = true;
      mensaje_inicio();
      lcd.clear();
      lcd.print(NOMBRE_CLIENTE);
      lcd.setCursor(0,1);
      lcd.print(segunda_linea);
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

      mensaje_inicio();
      lcd.setCursor(0,1);
      lcd.print(segunda_linea);
      
      delay(GUARDA_PROCESO);
      // Fin del bloque atómico
      attachInterrupt(digitalPinToInterrupt(PIN_ENTER), boton, FALLING);
    } 
  }
}

// 0123456789ABCDEF
// T:15 ROCIOS:0043 <- ejemplo de línea a lograr
void mensaje_inicio()
{
  int unidades = 0;
  int decenas = 0;
  int centenas = 0;
  int unidades_mil = 0;
  for(int i=0; i<16; ++i)
  {
    segunda_linea[i] = ' ';
  }
  segunda_linea[0] = 'T';
  segunda_linea[1] = ':';
  
  decenas = tiempo_rocio / 10;
  switch(decenas)
  {
    case 0: segunda_linea[2] = '0'; break;
    case 1: segunda_linea[2] = '1'; break;
    case 2: segunda_linea[2] = '2'; break;
    case 3: segunda_linea[2] = '3'; break;
    case 4: segunda_linea[2] = '4'; break;
    case 5: segunda_linea[2] = '5'; break;
    case 6: segunda_linea[2] = '6'; break;
    case 7: segunda_linea[2] = '7'; break;
    case 8: segunda_linea[2] = '8'; break;
    case 9: segunda_linea[2] = '9'; break;
    default: segunda_linea[2] = '?';
  }
  
  unidades = tiempo_rocio % 10;
  switch(unidades)
  {
    case 0: segunda_linea[3] = '0'; break;
    case 1: segunda_linea[3] = '1'; break;
    case 2: segunda_linea[3] = '2'; break;
    case 3: segunda_linea[3] = '3'; break;
    case 4: segunda_linea[3] = '4'; break;
    case 5: segunda_linea[3] = '5'; break;
    case 6: segunda_linea[3] = '6'; break;
    case 7: segunda_linea[3] = '7'; break;
    case 8: segunda_linea[3] = '8'; break;
    case 9: segunda_linea[3] = '9'; break;
    default: segunda_linea[3] = '?';
  }
  
  segunda_linea[5] = 'R';
  segunda_linea[6] = 'O';
  segunda_linea[7] = 'C';
  segunda_linea[8] = 'I';
  segunda_linea[9] = 'O';
  segunda_linea[10] = 'S';
  segunda_linea[11] = ':';
  
  unidades_mil = contador_rociadas / 1000;
  switch(unidades_mil)
  {
    case 0: segunda_linea[12] = '0'; break;
    case 1: segunda_linea[12] = '1'; break;
    case 2: segunda_linea[12] = '2'; break;
    case 3: segunda_linea[12] = '3'; break;
    case 4: segunda_linea[12] = '4'; break;
    case 5: segunda_linea[12] = '5'; break;
    case 6: segunda_linea[12] = '6'; break;
    case 7: segunda_linea[12] = '7'; break;
    case 8: segunda_linea[12] = '8'; break;
    case 9: segunda_linea[12] = '9'; break;
    default: segunda_linea[12] = '?';
  }

  centenas = (contador_rociadas % 1000) / 100;
  switch(centenas)
  {
    case 0: segunda_linea[13] = '0'; break;
    case 1: segunda_linea[13] = '1'; break;
    case 2: segunda_linea[13] = '2'; break;
    case 3: segunda_linea[13] = '3'; break;
    case 4: segunda_linea[13] = '4'; break;
    case 5: segunda_linea[13] = '5'; break;
    case 6: segunda_linea[13] = '6'; break;
    case 7: segunda_linea[13] = '7'; break;
    case 8: segunda_linea[13] = '8'; break;
    case 9: segunda_linea[13] = '9'; break;
    default: segunda_linea[13] = '?';
  }

  decenas = (contador_rociadas % 100) / 10;
  switch(decenas)
  {
    case 0: segunda_linea[14] = '0'; break;
    case 1: segunda_linea[14] = '1'; break;
    case 2: segunda_linea[14] = '2'; break;
    case 3: segunda_linea[14] = '3'; break;
    case 4: segunda_linea[14] = '4'; break;
    case 5: segunda_linea[14] = '5'; break;
    case 6: segunda_linea[14] = '6'; break;
    case 7: segunda_linea[14] = '7'; break;
    case 8: segunda_linea[14] = '8'; break;
    case 9: segunda_linea[14] = '9'; break;
    default: segunda_linea[14] = '?';
  }

  unidades = contador_rociadas % 10;
  switch(unidades)
  {
    case 0: segunda_linea[15] = '0'; break;
    case 1: segunda_linea[15] = '1'; break;
    case 2: segunda_linea[15] = '2'; break;
    case 3: segunda_linea[15] = '3'; break;
    case 4: segunda_linea[15] = '4'; break;
    case 5: segunda_linea[15] = '5'; break;
    case 6: segunda_linea[15] = '6'; break;
    case 7: segunda_linea[15] = '7'; break;
    case 8: segunda_linea[15] = '8'; break;
    case 9: segunda_linea[15] = '9'; break;
    default: segunda_linea[15] = '?';
  }
}


//CONFIGURACION
//TIEMPO: 15 <- ejemplo de línea a lograr
void mensaje_configuracion()
{
  int decenas = 0;
  int unidades = 0;
  segunda_linea[0] = 'T';
  segunda_linea[1] = 'I';
  segunda_linea[2] = 'E';
  segunda_linea[3] = 'M';
  segunda_linea[4] = 'P';
  segunda_linea[5] = 'O';
  segunda_linea[6] = ':';
  segunda_linea[7] = ' ';
  
  decenas = tiempo_rocio / 10;
  switch(decenas)
  {
    case 0: segunda_linea[8] = '0'; break;
    case 1: segunda_linea[8] = '1'; break;
    case 2: segunda_linea[8] = '2'; break;
    case 3: segunda_linea[8] = '3'; break;
    case 4: segunda_linea[8] = '4'; break;
    case 5: segunda_linea[8] = '5'; break;
    case 6: segunda_linea[8] = '6'; break;
    case 7: segunda_linea[8] = '7'; break;
    case 8: segunda_linea[8] = '8'; break;
    case 9: segunda_linea[8] = '9'; break;
    default: segunda_linea[8] = '?';
  }

  unidades = tiempo_rocio % 10;
  switch(unidades)
  {
    case 0: segunda_linea[9] = '0'; break;
    case 1: segunda_linea[9] = '1'; break;
    case 2: segunda_linea[9] = '2'; break;
    case 3: segunda_linea[9] = '3'; break;
    case 4: segunda_linea[9] = '4'; break;
    case 5: segunda_linea[9] = '5'; break;
    case 6: segunda_linea[9] = '6'; break;
    case 7: segunda_linea[9] = '7'; break;
    case 8: segunda_linea[9] = '8'; break;
    case 9: segunda_linea[9] = '9'; break;
    default: segunda_linea[9] = '?';
  }

  for(int i = 10; i < 16; ++i)
  {
    segunda_linea[i] = ' ';
  }
}
