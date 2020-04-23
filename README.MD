# Sistema de rocio COVID-19
Propiedad intelectual de Leyder Martinez Amador (leyjo8222@gmail.com).
## Materiales
* Placa arduino nano
* LCD 2x16 I2C
* Encoder con pulsador
* Sensor de nivel bajo en tanque
* Sensor de presencia en cámara de rocío
* Electro-válvula para el rociador
## Configuración del proyecto
* La configuración del proyecto se puede modificar desde el archivo config.h
* Hay pines que no se pueden mover de lugar, como por ejemplo el display LCD I2C
## Lógica del encoder
Se genera un arrar de 16 posiciones almacendando las posibles direcciones de giro del encoder tomando la posición anterior y la actual.
|Numero|A|B|A'|B'|Dirección|
|------|-|-|-|-|---------|
|0     |0|0|0|0|0        |
|1     |0|0|0|1|-1       |
|2     |0|0|1|0|+1       |
|3     |0|0|1|1|0        |
|4     |0|1|0|0|+1       |
|5     |0|1|0|1|0        |
|6     |0|1|1|0|0        |
|7     |0|1|1|1|-1       |
|8     |1|0|0|0|-1       |
|9     |1|0|0|1|0        |
|10    |1|0|1|0|0        |
|11    |1|0|1|1|+1       |
|12    |1|1|0|0|0        |
|13    |1|1|0|1|+1       |
|14    |1|1|1|0|-1       |
|15    |1|1|1|1|0        |

