# Capitulo 2: Las piezas que componen un lenguaje

| [↩️ Volver al inicio del Proyecto](../README.md) | [⬅️ Ir a Capítulo 1](../docs/01-Bienvenido.md) |
| :----------------------------------------------: | :--------------------------------------------: |

<br/><hr/><br/>

Desde hace mucho tiempo, buscamos que las computadoras **entiendan nuestras instrucciones**. Como hablar su lenguaje directamente resultó difícil, creamos **lenguajes de programación**: una forma más humana de comunicarnos con ellas.

Aunque hoy las máquinas son mucho más rápidas y poderosas, los principios para construir un lenguaje **siguen siendo casi los mismos** .

<br/><br/><br/>

# 📚 Índice del Capítulo 2

| Sección                                                                                                                                      | Descripción                                                                                                                                                          |
| :------------------------------------------------------------------------------------------------------------------------------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [1. ✍️ Dibujando el lenguaje en un papel](#1--️-dibujando-el-lenguaje-en-un-papel)                                                           | Cómo un boceto inicial se convierte en un mapa claro del programa.                                                                                                   |
| [2. 🔍 Escaneo (Scanning o Lexing)](#2--escaneo-scanning-o-lexing)                                                                           | Primer paso: convertir texto crudo en tokens listos para el análisis.                                                                                                |
| [3. 👀 ¿Qué es el escáner léxico (lexer)?](#3--qué-es-el-escáner-léxico-o-lexer)                                                             | Explicación de cómo el lexer organiza caracteres en bloques significativos.                                                                                          |
| [4. 🧩 ¿Qué es un token?](#4--qué-es-un-token)                                                                                               | Concepto de token y ejemplos prácticos de los distintos tipos.                                                                                                       |
| [5. 🔧 De texto a tokens: primer paso del compilador](#5--de-texto-a-tokens-primer-paso-del-compilador)                                      | Cómo el lexer encaja en el proceso general del compilador.                                                                                                           |
| [6. 🌲 Análisis Sintáctico (Parsing)](#6--análisis-sintáctico-parsing)                                                                       | Cómo los tokens se organizan en estructuras jerárquicas (AST).                                                                                                       |
| [7. 💬 Análisis Semántico: Entendiendo el Significado del Código](#7--análisis-semántico-entendiendo-el-significado-del-código)              | Es la etapa donde el compilador verifica que el código esté bien escrito, tenga sentido lógico y coherente según las reglas del lenguaje.                            |
| [8. 🛠️ Representaciones Intermedias (Intermediate Representations – IR)](#8-️-representaciones-intermedias-intermediate-representations--ir) | Explica cómo se usa una forma intermedia de código para conectar el front end y el back end, facilitando optimización y soporte multi-lenguaje y multi-arquitectura. |

<br/><hr/><br/>

## 1. ✍️ Dibujando el lenguaje en un papel

Pensemos que crear un lenguaje empieza como un **boceto**. Nada grandioso, solo una idea garabateada con entusiasmo.

![mapa del lenguaje](../recursos/tema-02/img/mapa.png)

Al principio, el programa es **solo texto crudo** —una lista de símbolos sin mucho sentido por sí mismos. Pero poco a poco, vamos **trazando líneas, conectando ideas y dándole forma**. Cada paso nos ayuda a **organizar y entender mejor** lo que el código quiere expresar.

Al final, este garabato lleno de rayones se convierte en un **mapa claro del programa**.

> Todo gran lenguaje empezó alguna vez como un garabato en un papel.

Nuestro recorrido comienza con el **texto en bruto del código fuente** del usuario.

A lo largo de la historia, hubo muchos intentos fallidos y caminos sin salida: ideas que parecían prometedoras, pero que el tiempo dejó atrás. Aun así, esos experimentos forman parte del mapa de la computación y nos recuerdan que incluso los errores ayudan a construir el conocimiento.

<br/><hr/><br/>

## 2. 🔍 Escaneo (Scanning o Lexing)

El primer paso para entender el código es el **escaneo**, también llamado **análisis léxico**.

En esta etapa, el programa deja de ser una simple secuencia de letras y símbolos y se convierte en una lista de **tokens** —las “palabras” del lenguaje.

Un **scanner** (o **lexer**) lee el texto y lo divide en partes con significado:  
números, nombres, paréntesis, operadores o cadenas.

Al mismo tiempo, ignora lo que no aporta nada al código, como los **espacios en blanco** o los **comentarios**.

El resultado es una secuencia limpia y ordenada de tokens.

<br/><hr/><br/>

## 3. 👀 ¿Qué es el escáner léxico (o lexer)?

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

<br/><hr/><br/>

## 4. 🧩 ¿Qué es un token?

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

<br/><hr/><br/>

## 5. 🔧 De texto a tokens: primer paso del compilador

El lexer es la primera etapa del proceso de compilación o interpretación:

```text
🔠 Texto crudo  →  🧮 Tokens  →  🧱 Estructura del programa
   (Scanner)        (Parser)
```

Primero, el **scanner** divide el texto en tokens.  
Después, el **parser** (analizador sintáctico) toma esos tokens y los **organiza** según las reglas del lenguaje.

Cada etapa se apoya en la anterior: el escaneo prepara el terreno, y el parser empieza a darle forma al código para que el lenguaje pueda interpretarlo o compilarlo correctamente

<br/><hr/><br/>

## 6. 🌲 Análisis Sintáctico (Parsing)

El siguiente paso después del escaneo es el **parsing**, o análisis sintáctico.  
Aquí es donde el código empieza a **tomar forma**: el parser entiende cómo juntar las piezas (tokens) para formar expresiones y sentencias más grandes.

Un **parser** toma la secuencia de tokens y la organiza en una **estructura jerárquica**, mostrando cómo las distintas partes del código se relacionan entre sí 🌳. En la práctica, esa estructura se llama **árbol de sintaxis** o **AST** (Abstract Syntax Tree).

Para nosotros, lo importante es entender que **el parser da forma y sentido al código**, y nos permite trabajar con él de manera ordenada.

### 💡 Apunte técnico

El parser **convierte la lista de tokens** en una **estructura organizada** (AST = “árbol de sintaxis abstracta” o "abstract syntax tree") que refleja la lógica y jerarquía del programa.  
Esta estructura es clave para los siguientes pasos del compilador o intérprete, como:

- Revisar que el código tenga sentido (**análisis semántico**)
- Generar código que la máquina pueda ejecutar
- Optimizar el programa para que sea más rápido o eficiente

Por lo tanto:

🎟️ Tokens → 🌳 Árbol de sintaxis → 🏗️ Estructura lógica del programa

> 💡 Sin parsing, el compilador vería solo una lista de símbolos sin sentido.  
> Con él, el código **adquiere forma, jerarquía y lógica**, listo para ser entendido y procesado.

<br/><hr/><br/>

## 7. 💬 Análisis Semántico: Entendiendo el Significado del Código

> Hasta ahora, ya tenemos nuestro código dividido en tokens (gracias al lexer) y organizado en una estructura lógica (gracias al parser). Pero… ¿el programa tiene sentido? ❓

Por ejemplo, mira este código:

```javascript
var x = "hola";
x = x + 10;
```

El parser no ve ningún problema aquí: la estructura está bien. Pero, desde el punto de vista del significado, algo está mal. ¡Estamos intentando sumar un número a una cadena de texto! Y ahí es donde entra en juego el análisis semántico.

### 🔍 **¿Qué hace el análisis semántico?**

El análisis semántico revisa que las operaciones y relaciones del programa tengan **sentido lógico**, según las reglas del lenguaje.

Algunas tareas comunes del análisis semántico son:

Tarea Descripción
| Verificación | Descripción |
| :--------------- | :------------------------------------------------------------ |
| **Tipos** | Que las operaciones sean válidas (no sumar texto con números). |
| **Nombres** | Que las variables y funciones existan antes de usarlas. |
| **Ámbito (scope)** | Qué variables son visibles dentro de cada bloque. |

Por ejemplo:

- Podemos imaginarlo como una fábrica de ideas 🏭. **Primero**, el **lexer** corta la materia prima en piezas pequeñas (los **tokens**). Después, el **parser** ensambla esas piezas en un producto con forma (el **Árbol de sintaxis AST**). Y finalmente, el **analizador semántico** revisa que todo funcione correctamente antes de salir al mundo —que las piezas encajen y el resultado tenga sentido ⚙️.

| Etapa         | Resultado esperado   |
| :------------ | :------------------- |
| **Lexer**     | Palabras correctas   |
| **Parser**    | Oraciones correctas  |
| **Semántico** | Significado correcto |

### 🧰 ¿Qué obtiene el compilador de esta etapa?

Después de este paso, el compilador tiene un programa que:

- Tiene estructura correcta (gracias al parser)
- Tiene significado válido (gracias al análisis semántico)

En otras palabras, el código no solo está bien escrito, sino que tiene lógica. Y con eso, ya está listo para pasar a las siguientes fases del viaje: la **generación de código** o la **interpretación** 🎯.

### 💬 Entonces, tenemos el siguiente camino recorrido:

| Etapa         | Qué hace                  | Resultado                    |
| :------------ | :------------------------ | :--------------------------- |
| **Lexer**     | Divide el texto en tokens | 🧩 Lista de tokens           |
| **Parser**    | Da estructura al código   | 🌳 Árbol de sintaxis (AST)   |
| **Semántico** | Verifica el significado   | ✅ Código coherente y válido |

Sin análisis semántico, podríamos tener programas “bien escritos” pero completamente absurdos.

<br/><hr/><br/>

## 8. 🛠️ Representaciones Intermedias (Intermediate Representations – IR)

Podemos imaginar el **compilador** como una tubería de trabajo donde cada etapa transforma el código del usuario en una forma más organizada y fácil de procesar 🏗️.

El **front-end** de esta tubería está ligado al lenguaje fuente (por ejemplo, Java, C o Python) 📜.

El **back-end**, en cambio, se enfoca en la arquitectura destino (como x86, ARM o RISC-V) ⚙️.

En el medio, el código pasa por una **representación intermedia (IR)**: una forma neutra que no depende del lenguaje original ni de la máquina final 🧩. Esta IR actúa como un puente entre ambos mundos, permitiendo que un compilador soporte múltiples lenguajes y plataformas con menos esfuerzo.

💡 **Ejemplo**

Supongamos que queremos crear compiladores para Pascal, C y Fortran, y que apunten a tres arquitecturas: x86, ARM y SPARC. Sin **IR**, tendrías que construir nueve compiladores completos (una combinación por cada caso) 😵‍💫.

Con una **IR compartida**, solo necesitas:
Un **front-end** por lenguaje (que genere la IR).
Un **back-end** por arquitectura (que traduzca desde la IR).

De esta forma, puedes mezclar y combinar libremente todas las combinaciones posibles.

**🔧 Tipos comunes de IR**

Existen varios estilos de representación intermedia que se usan ampliamente en compiladores modernos 📚: Control Flow Graph (CFG) 🌳 - Static Single Assignment (SSA) ✏️ - Continuation-Passing Style (CPS) 🔗 - Three-Address Code (TAC) 🧮

Por lo tanto:
📜 Lenguaje fuente → 🌳 Representación intermedia (IR) → 🖥️ Arquitectura objetivo

La **representación intermedia (IR)** desacopla el front-end del back-end, haciendo el compilador modular, extensible y reutilizable. También permite aplicar optimizaciones independientes del lenguaje o la plataforma, lo que mejora la eficiencia general del programa.

### 💡 Dato curioso: Soporte de múltiples lenguajes y arquitecturas en GCC

- GCC significa GNU Compiler Collection: Es un conjunto de compiladores de código abierto desarrollado por el proyecto GNU que permite traducir programas escritos en varios lenguajes de programación a código máquina que pueda ejecutar una computadora.

¿Alguna vez te preguntaste cómo GCC puede compilar tantos lenguajes para tantas arquitecturas distintas?

La clave está en que todos los front-ends (C, C++, Ada, etc.) generan una **IR compartida** —como **GIMPLE o RTL**.

Luego, los back-ends específicos de cada arquitectura (x86, ARM, 68k, etc.) traducen esa **IR a código nativo**.

| Parte del compilador | Función principal                  | Ejemplo      |
| :------------------- | :--------------------------------- | :----------- |
| **Front-end**        | Traduce el lenguaje fuente a IR    | C → GIMPLE   |
| **IR**               | Representación común y optimizable | GIMPLE / RTL |
| **Back-end**         | Traduce IR a código máquina        | GIMPLE → x86 |

🌳 Una **IR compartida** funciona como un puente entre los front-ends y los back-ends, permitiendo combinar muchos lenguajes y arquitecturas sin crear compiladores desde cero 🔧💡.

<br/><hr/><br/>

| [↩️ Volver al inicio del Proyecto](../README.md) | [⬆️ Ir al inicio del Capítulo](#capitulo-2-las-piezas-que-componen-un-lenguaje) | [⬅️ Ir a Capítulo 1](../docs/01-Bienvenido.md) |
| :----------------------------------------------: | :-----------------------------------------------------------------------------: | :--------------------------------------------: |
