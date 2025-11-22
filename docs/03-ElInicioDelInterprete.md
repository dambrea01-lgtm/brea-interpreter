# Capítulo 3: El inicio del Interprete (Scanning)

| [↩️ Volver al inicio del Proyecto](../README.md) | [⬅️ Ir a Capítulo 2](../docs/02-PiezasDeUnLenguaje.md) |
| :----------------------------------------------: | :----------------------------------------------------: |

<br/><hr/><br/>

El primer paso para que **Brea** entienda nuestro código es convertir la cadena de texto en algo que el programa pueda procesar.

El **scanner** se encarga de leer cada carácter y agruparlo en **tokens**, que son como las piezas de Lego del lenguaje. 🧩

Al final de este capítulo, tendremos un pequeño **“traductor”** que convierte nuestro código en información clara para el **parser**, listo para analizar la lógica del programa.

<br/><hr/><br/>

## Índice del capitulo 3

<br/><hr/><br/>

| [↩️ Volver al inicio del Proyecto](../README.md) | [⬆️ Ir al inicio del Capítulo](#capítulo-3-el-inicio-del-interprete-scanning) | [⬅️ Ir a Capítulo 2](../docs/02-PiezasDeUnLenguaje.md) |
| :----------------------------------------------: | :---------------------------------------------------------------------------: | :----------------------------------------------------: |
