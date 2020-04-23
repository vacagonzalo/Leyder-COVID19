////////////////////////////////////////////////////////////////////////////////
// Determinación de las conexiones a la placa Arduino Nano.
// El display solo puede ir conectado en los pines SDA y SCL
// SDA -> A4 (PIN 27)
// SCL -> A5 (PIN 28)
// El sensor de presencia y el boton del encoder solo pueden ir en los pines
// 2 y 3 de la placa arduino nano, son los únicos que pueden generar
// interrupciones externas.
////////////////////////////////////////////////////////////////////////////////

#define PIN_ENTER	      3 // INT1, lógica hecha con interrupciones
#define PIN_PRESENCIA   2 // INT0, lógica hecha con interrupciones
#define PIN_NIVEL	      6

#define PIN_ASPERSOR    22
#define PIN_ALARMA	    19

#define PIN_ENCODER_A   4
#define PIN_ENCODER_B   5

////////////////////////////////////////////////////////////////////////////////
// Definición de textos a mostrar en pantalla.
////////////////////////////////////////////////////////////////////////////////

#define SALUDO              "SALUDOS DE"
#define NOMBRE_FABRICANTE   "#LEYDER CONTROL#"
#define NOMBRE_CLIENTE      "-#CLIENTE#-"
#define ALARMA_NIVEL        "ALERTA DE NIVEL!"
#define CONFIGURACION       "CONFIGURACION"

////////////////////////////////////////////////////////////////////////////////
// Determinación de retardos internos para el correcto funcionamiento del
// firmware. Se recomienda no modificar.
////////////////////////////////////////////////////////////////////////////////

#define GUARDA_RUIDO    200
#define GUARDA_PROCESO  2000
#define TIEMPO_ROCIO	  10000
#define TIEMPO_SALUDO   2000

////////////////////////////////////////////////////////////////////////////////
// Bibliotecas externas. Se recomienda no modificar.
////////////////////////////////////////////////////////////////////////////////

#include "LiquidCrystal_I2C.h"

////////////////////////////////////////////////////////////////////////////////
// Definiciones de constantes para hacer funcionar las bibliotecas externas.
////////////////////////////////////////////////////////////////////////////////

#define LCD_cADDR 0x27 // IMPORTANTE! depende del LCD. Buscar la dirección
#define LCD_cCHAR 16
#define LCD_CLINE 2       

////////////////////////////////////////////////////////////////////////////////
// Constantes lógicas.
////////////////////////////////////////////////////////////////////////////////

#define BUEN_NIVEL LOW	// Cambiar a HIGH si la resistencia es de pull-up
#define TIEMPO_MINIMO 5000
#define TIEMPO_MAXIMO 20000
