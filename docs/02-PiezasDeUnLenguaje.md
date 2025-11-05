# Capitulo 2: Las piezas que componen un lenguaje

| [↩️ Volver al inicio del Proyecto](../README.md) | [⬅️ Ir a Capítulo 1](../docs/01-Bienvenido.md) |
| :----------------------------------------------: | :--------------------------------------------: |

---

Desde hace mucho tiempo, buscamos que las computadoras **entiendan nuestras instrucciones**. Como hablar su lenguaje directamente resultó difícil, creamos **lenguajes de programación**: una forma más humana de comunicarnos con ellas.

Aunque hoy las máquinas son mucho más rápidas y poderosas, los principios para construir un lenguaje **siguen siendo casi los mismos** .

---

# 📚 Índice del Capítulo 2

| Sección                                                                                            | Descripción                                                                      |
| :------------------------------------------------------------------------------------------------- | :------------------------------------------------------------------------------- |
| [✍️ Dibujando el lenguaje en un papel](#-dibujando-el-lenguaje-en-un-papel-✍️)                     | Cómo un boceto inicial se convierte en un mapa claro del programa.               |
| [🔍 Escaneo (Scanning o Lexing)](#-escaneo-scanning-o-lexing)                                      | Primer paso: convertir texto crudo en tokens listos para el análisis.            |
| [👀 Qué es el escáner léxico (lexer)](#-qué-es-el-escáner-léxico-o-lexer)                          | Explicación de cómo el lexer organiza caracteres en bloques significativos.      |
| [🧩 Qué es un token](#-qué-es-un-token)                                                            | Concepto de token y ejemplos prácticos de los distintos tipos.                   |
| [🔧 De texto a tokens: primer paso del compilador](#-de-texto-a-tokens-primer-paso-del-compilador) | Cómo el lexer encaja en el proceso general del compilador.                       |
| [🌲 Análisis Sintáctico (Parsing)](#-análisis-sintáctico-parsing)                                  | Cómo los tokens se organizan en estructuras jerárquicas (AST).                   |
| [💡 Apunte técnico](#-apunte-técnico)                                                              | Detalles técnicos sobre el parsing y su importancia para las etapas posteriores. |

---

## Dibujando el lenguaje en un papel ✍️

Pensemos que crear un lenguaje empieza como un **boceto**. Nada grandioso, solo una idea garabateada con entusiasmo.

![mapa del lenguaje](../recursos/tema-02/img/mapa.png)

Al principio, el programa es **solo texto crudo** —una lista de símbolos sin mucho sentido por sí mismos. Pero poco a poco, vamos **trazando líneas, conectando ideas y dándole forma**. Cada paso nos ayuda a **organizar y entender mejor** lo que el código quiere expresar.

Al final, este garabato lleno de rayones se convierte en un **mapa claro del programa**.

> Todo gran lenguaje empezó alguna vez como un garabato en un papel.

Nuestro recorrido comienza con el **texto en bruto del código fuente** del usuario.

A lo largo de la historia, hubo muchos intentos fallidos y caminos sin salida: ideas que parecían prometedoras, pero que el tiempo dejó atrás. Aun así, esos experimentos forman parte del mapa de la computación y nos recuerdan que incluso los errores ayudan a construir el conocimiento.

---

## 🔍 Escaneo (Scanning o Lexing)

El primer paso para entender el código es el **escaneo**, también llamado **análisis léxico**.

En esta etapa, el programa deja de ser una simple secuencia de letras y símbolos y se convierte en una lista de **tokens** —las “palabras” del lenguaje.

Un **scanner** (o **lexer**) lee el texto y lo divide en partes con significado:  
números, nombres, paréntesis, operadores o cadenas.

Al mismo tiempo, ignora lo que no aporta nada al código, como los **espacios en blanco** o los **comentarios**.

El resultado es una secuencia limpia y ordenada de tokens.

---

## 👇 Qué es el escáner léxico (o lexer)

Cuando escribes un programa, lo que tienes es texto plano: letras, números, signos y espacios.

Por ejemplo:

```javascript
var suma = 10 + 5;
```

Para una computadora, eso al principio es solo una cadena de caracteres:

```java
v a r   s u m a   =   1 0   +   5 ;
```

El escáner léxico (también llamado **lexer**) es el encargado de leer ese texto y darle estructura, separándolo en bloques con significado, llamados **tokens**.

---

## 🧩 Qué es un token

Un token es como una pequeña etiqueta que indica qué tipo de cosa representa una parte del código. Por ejemplo, el código anterior se convertiría en esta lista de tokens:

| Texto  | Tipo de token | Descripción        |
| :----- | :------------ | :----------------- |
| `var`  | KEYWORD       | Palabra reservada  |
| `suma` | IDENTIFICADOR | Nombre de variable |
| `=`    | OPERADOR      | Asignación         |
| `10`   | NÚMERO        | Valor numérico     |
| `+`    | OPERADOR      | Suma               |
| `5`    | NÚMERO        | Valor numérico     |
| `;`    | PUNTUACIÓN    | Fin de instrucción |

El escáner también puede guardar la posición (línea y columna) de cada token.
Esto sirve para que, si hay un error, el compilador pueda decirte exactamente dónde ocurrió.

---

## 🔧 De texto a tokens: primer paso del compilador

El lexer es la primera etapa del proceso de compilación o interpretación:

```text
🔠 Texto crudo  →  🧮 Tokens  →  🧱 Estructura del programa
   (Scanner)        (Parser)
```

Primero, el **scanner** divide el texto en tokens.  
Después, el **parser** (analizador sintáctico) toma esos tokens y los **organiza** según las reglas del lenguaje.

Cada etapa se apoya en la anterior: el escaneo prepara el terreno, y el parser empieza a darle forma al código para que el lenguaje pueda interpretarlo o compilarlo correctamente

---

## 🌲 Análisis Sintáctico (Parsing)

El siguiente paso después del escaneo es el **parsing**, o análisis sintáctico.  
Aquí es donde el código empieza a **tomar forma**: el parser entiende cómo juntar las piezas (tokens) para formar expresiones y sentencias más grandes.

Un **parser** toma la secuencia de tokens y la organiza en una **estructura jerárquica**, mostrando cómo las distintas partes del código se relacionan entre sí 🌳. En la práctica, esa estructura se llama **árbol de sintaxis** o **AST** (Abstract Syntax Tree).

Para nosotros, lo importante es entender que **el parser da forma y sentido al código**, y nos permite trabajar con él de manera ordenada.

---

### Apunte técnico

El parser **convierte la lista de tokens** en una **estructura organizada** (AST) que refleja la lógica y jerarquía del programa.  
Esta estructura es clave para los siguientes pasos del compilador o intérprete, como:

- Revisar que el código tenga sentido (**análisis semántico**)
- Generar código que la máquina pueda ejecutar
- Optimizar el programa para que sea más rápido o eficiente

Existen diferentes formas de hacer parsing:

- **Descenso recursivo 🌀**: fácil de entender y de programar, ideal para aprender.
- **LL / LR parsers ⚙️**: más potentes, usados por herramientas automáticas como Yacc, Bison o ANTLR.

Por lo tanto:

🎟️ Tokens → 🌳 Árbol de sintaxis → 🏗️ Estructura lógica del programa

> 💡 Sin parsing, el compilador vería solo una lista de símbolos sin sentido.  
> Con él, el código **adquiere forma, jerarquía y lógica**, listo para ser entendido y procesado.

---

(desarrollando)

---

| [↩️ Volver al inicio del Proyecto](../README.md) | [⬅️ Ir a Capítulo 1](../docs/01-Bienvenido.md) |
| :----------------------------------------------: | :--------------------------------------------: |
