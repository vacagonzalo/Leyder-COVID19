////////////////////////////////////////////////////////////////////////////////
// Control del modo debug
// Si se habilita, se reportará al monitor serie el estado del programa
// y el ingreso a las distintas funciones
////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODE  1 // 0 para modo normal, 1 para modo debugger

////////////////////////////////////////////////////////////////////////////////
// Determinación de las conexiones a la placa Arduino Nano.
// El display solo puede ir conectado en los pines SDA y SCL
// SDA -> A4 (PIN 27)
// SCL -> A5 (PIN 28)
////////////////////////////////////////////////////////////////////////////////

// sensores
#define PIN_PRESENCIA   2 
#define PIN_NIVEL       6 

// encoder
#define PIN_PULSADOR    3
#define PIN_ENCODER_A   4
#define PIN_ENCODER_B   5

// actuadores
#define PIN_ASPERSOR    22
#define PIN_ALARMA	19

////////////////////////////////////////////////////////////////////////////////
// Máquina de estados
////////////////////////////////////////////////////////////////////////////////

#define INICIO		0
#define REPOSO		1
#define ROCIAR		2
#define CONFIGURAR	3
#define ALARMAR		4

////////////////////////////////////////////////////////////////////////////////
// Definición de textos a mostrar en pantalla.
////////////////////////////////////////////////////////////////////////////////

#define SALUDO              "   SALUDOS DE   "
#define NOMBRE_FABRICANTE   " LEYDER CONTROL "
#define NOMBRE_CLIENTE      "   -#CLIENTE#-  "
#define ALARMA_NIVEL        "ALERTA DE NIVEL!"
#define CONFIGURACION       "CONFIGURACION   "

////////////////////////////////////////////////////////////////////////////////
// Determinación de retardos internos para el correcto funcionamiento del
// firmware. Se recomienda no modificar.
////////////////////////////////////////////////////////////////////////////////

#define GUARDA_RUIDO	200
#define GUARDA_PROCESO	2000
#define TIEMPO_ROCIO	10000
#define TIEMPO_SALUDO	2000

////////////////////////////////////////////////////////////////////////////////
// Bibliotecas externas. Se recomienda no modificar.
////////////////////////////////////////////////////////////////////////////////

// name=LiquidCrystal I2C
// version=1.1.2
// author=Frank de Brabander
// maintainer=Marco Schwartz <marcolivier.schwartz@gmail.com>
// sentence=A library for I2C LCD displays.
// paragraph= The library allows to control I2C displays with functions 
// extremely similar to LiquidCrystal library. THIS LIBRARY MIGHT NOT BE 
// COMPATIBLE WITH EXISTING SKETCHES.
// category=Display
// url=https://github.com/marcoschwartz/LiquidCrystal_I2C
// architectures=avr
#include "LiquidCrystal_I2C.h"

////////////////////////////////////////////////////////////////////////////////
// Definiciones de constantes para hacer funcionar las bibliotecas externas.
////////////////////////////////////////////////////////////////////////////////

#define LCD_cADDR 0x27 // IMPORTANTE! depende del LCD. Buscar la dirección
#define LCD_cCHAR 16
#define LCD_CLINE 2       

////////////////////////////////////////////////////////////////////////////////
// Constantes lógicas. Cambiar según hardware y necesidades de la aplicación
////////////////////////////////////////////////////////////////////////////////

#define PRESENCIA	HIGH

#define PULSADO		LOW

#define MAL_NIVEL	LOW

#define SUENA_ALARMA	LOW
#define NO_SUENA_ALARMA	HIGH

#define ROCIANDO	LOW
#define NO_ROCIANDO	HIGH

#define TIEMPO_MINIMO	5000
#define TIEMPO_MAXIMO	20000
