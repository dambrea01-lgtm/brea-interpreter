# Capítulo 3: El inicio del Interprete (Scanning)

| [↩️ Volver al inicio del Proyecto](../README.md) | [⬅️ Ir a Capítulo 2](../docs/02-PiezasDeUnLenguaje.md) |
| :----------------------------------------------: | :----------------------------------------------------: |

<br/><hr/><br/>

> El primer paso para que **Brea** entienda nuestro código es convertir el texto en algo que el intérprete pueda procesar. En este capítulo trabajaremos con **jBrea**, la versión en Java. Más adelante construiremos **cBrea** en C, pero por ahora nos enfocamos en Java.

> El **scanner** lee cada carácter y los agrupa en **tokens**, que son como los bloques de construcción del lenguaje. Al final, tendremos un pequeño **“traductor”** que convierte nuestro código en información clara para el **parser**, listo para analizar la lógica del programa.

<br/><hr/><br/>

## 📚 Índice del capitulo 3

| Sección                                                                                                                                     | Descripción                                                                                                                                                                                                |
| ------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [1. 🛠️ Entendiendo el framework del intérprete jBrea](#1-️-entendiendo-el-framework-del-intérprete-jbrea)                                   | Vemos la estructura mínima de jBrea, cómo se inicia y cómo se prepara para procesar código. Es la base sobre la que construiremos el scanner y el REPL.                                                    |
| [2. 💓 La clase principal: el corazón del intérprete](#2--la-clase-principal-el-corazón-del-intérprete)                                     | Explicamos la clase `Brea.java` y el método `main()`. Aquí decidimos si el usuario ejecuta un archivo o entra al modo interactivo (REPL). También abordamos qué son los argumentos y cómo se controlan.    |
| [3. 🏃‍♂️ Ejecutar un archivo de Brea con el intérprete jBrea](#3-️-ejecutar-un-archivo-de-brea-con-el-interprete-jbrea)                       | Mostramos cómo leer un archivo `.brea` completo, convertir su contenido en texto y enviarlo a `run()`, que lo preparará para el scanner.                                                                   |
| [4. ⌨️ Ejecutar Brea de forma interactiva (REPL)](#4-️-ejecutar-brea-de-forma-interactiva-repl)                                             | Explicamos el modo interactivo: leer línea por línea, procesar el texto con `run()`, mostrar resultados y cómo salir usando EOF (Ctrl+D en Linux/macOS, Ctrl+Z + ENTER en Windows).                        |
| [5. ⚡ La función de nuestro intérprete más importante por ahora: run()](#5--la-función-de-nuestro-interprete-más-importante-por-ahora-run) | Detallamos la función `run()`, que toma el código fuente y lo envía al scanner para generar tokens. Por ahora solo los imprimimos, pero es la base del procesamiento futuro del lenguaje.                  |
| [6. 🌀 Del código al scanner: el flujo del intérprete jBrea](#6--del-código-al-scanner-el-flujo-del-interprete-jbrea)                       | Resumimos todo el flujo desde que jBrea recibe un archivo o entrada interactiva hasta que el scanner genera la lista de tokens. Esta visión completa muestra cómo se organiza el procesamiento del código. |

<br/><hr/><br/>

## [1. 🛠️ Entendiendo el framework del intérprete jBrea](#-índice-del-capitulo-3)

Vamos a armar la estructura mínima necesaria para que nuestro intérprete funcione. Todavía no vamos a ejecutar código Brea real, pero estamos sentando los cimientos de todo.

Una buena forma de verlo: si este capítulo fuera una casa, estaríamos construyendo las paredes, las puertas y dónde va cada habitación, para después llenarlo todo con lógica del lenguaje.

<br>

### ¿Qué es un intérprete?

Antes de tocar código, vale la pena dejar súper claro qué estamos construyendo.

- Un **intérprete** es un programa cuyo trabajo es:
  1. Leer **código fuente** (un archivo o lo que escribe el usuario)
  2. Entenderlo (analizarlo paso a paso)
  3. Ejecutarlo **directamente**

A diferencia de un **compilador**, que traduce todo a un **archivo ejecutable**, el **intérprete** trabaja “en vivo”: lee → interpreta → ejecuta.

En nuestro caso:

- **Brea** es un **lenguaje de scripting** ligero
- **jBrea** es su implementación en **Java**

Más adelante haremos **cBrea** en c, pero Java nos ayuda a entender el diseño de forma más sencilla

<br><hr/><br/>

## [2. 💓 La clase principal: el corazón del intérprete](#-índice-del-capitulo-3)

En Java, todas las aplicaciones empiezan con una **clase** y un método **main()**, que es el punto de entrada. Para nuestro **interprete jBrea**, nuestra clase principal se ve así:

```java
    package com.lenguaje.brea;

    // Importamos las clases necesarias para leer archivos y entrada por consola
    import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStreamReader;
    import java.nio.charset.Charset;
    import java.nio.file.Files;
    import java.nio.file.Paths;
    import java.util.List;

    /**
     * Esta es la clase principal del intérprete jBrea.
     * Aquí es donde arranca todo el programa cuando lo ejecutas.
    */
    public class Brea{

        /**
         * El método main() es el punto de entrada de cualquier programa Java.
         * Aquí decidimos si el usuario quiere:
         *  - ejecutar un archivo .brea
         *  - abrir el modo interactivo (REPL)
         *  - o si escribió mal los argumentos.
         */

        public static void main(String[] args) throws IOException{

            // Si el usuario pasa más de un argumento, significa que está usando mal el programa.
            // Mostramos un mensaje explicando el uso correcto y salimos con código de error 64.
            // (Este código está basado en los estándares de Unix "sysexits.h").

            if (args.length > 1){

                System.out.println("Uso: jBrea [script]");
                System.exit(64);

            // Si el usuario pasó exactamente UN argumento,
            // interpretamos que es la ruta a un archivo .brea.
            }else if (args.length == 1){

                runFile(args[0]); // Ejecuta el archivo pasado por parámetro.

            // Si no pasó ningún argumento,
            // significa que quiere usar el intérprete de forma interactiva (REPL).
            }else{

                runPrompt(); // Abre el prompt interactivo

            }
        }
    }
```

🧱 **¿Qué significa todo esto?**

Vamos parte por parte:

- **public static void main(String[] args)**: Es el punto de inicio del programa, donde Java comienza a ejecutar todo.

- **Control de argumentos (if-else):** Nuestro intérprete se puede usar de dos formas
  - **Ejecutando un archivo**: jBrea programa.brea
  - **Modo interactivo (REPL) sin archivo**: jBrea

❌ **Si pasas más de un argumento**: Mostramos un mensaje de uso y salimos con código 64, que es un estándar de errores de uso según sysexits.h en Unix. (No es obligatorio usar 64, pero hacerlo nos enseña buenas prácticas).

<br/>

### 🧩 **¿Qué son exactamente los “argumentos” en main(String[] args)?**

Esto es algo que muchas personas que empiezan a aprender Java (o cualquier lenguaje) no entienden al principio, así que vamos a explicarlo clarísimo con ejemplos.

> Cuando ejecutas un programa desde la **terminal**, puedes escribir “palabras” o **valores** extra junto al comando. Esos **valores** extra se llaman **argumentos**.

El método **main(String[] args)** recibe esos argumentos dentro del arreglo o vector args.

<br/>

**👉 Pongamos un ejemplo sencillo**

Imagina que ejecutas esto en tu terminal:

```cmd
  jBrea hola.brea
```

Entonces tendremos lo siguiente:

```java
  args[0] = "hola.brea" //se le asigna a la posicion 0 del vector el string hola.brea
  args.length = 1  //si comprobamos la longitud de nuestro vector será igual a 1
```

En este ejemplo sencillo estamos pasando un argumento, que es el nombre del archivo ("hola.brea").

<br/>

**🧪 ¿Qué pasa si no pasas nada?**

Si ejecutas:

```cmd
  jBrea
```

Entonces tendremos:

```java
  args.length = 0  //si a nuestro vector comprobamos su longitud, vemos que es igual 0
```

Si nadie pasó argumentos → el programa lo sabe, y por eso nuestro interprete lo vamos a configurar para que entre en un **modo interactivo (REPL)**

<br/>

**⚠️ ¿Y si pasas demasiados argumentos?**

Si alguien ejecuta:

```cmd
  jBrea archivo1.brea archivo2.brea
```

Entonces tendremos:

```java
  args.length = 2 // el vector args tendra un tamaño de 2
```

Esto significa que el usuario pasó más de lo permitido. Por eso nuestro programa mostrará un mensaje de error para estos casos. Tal como:

```text
  Uso: jBrea [script]
  Y sale con un código de error estandarizado.
```

<br/>

**🎯 ¿Por qué controlamos los argumentos?**

Porque dependiendo de cuántos argumentos reciba el programa, jBrea debe comportarse de forma distinta:

👉 **Caso 1:** 0 argumentos ➡️ Abrimos el REPL (modo interactivo)

```cmd
  jBrea
```

👉 **Caso 2:** 1 argumento ➡️ Interpretamos un archivo .brea

```cmd
  jBrea mi_programa.brea
```

👉 **Caso 3:** +1 argumentos ➡️ El usuario usó mal el comando → mostramos un error

```cmd
  jBrea archivo1.brea archivo2.brea
```

Por eso hemos usamos la siguiente estructura if-else if-else:

```java
  if (args.length > 1) {
      // Demasiados argumentos → error
  } else if (args.length == 1) {
      // Un argumento → ejecutar un archivo
  } else {
      // Ningún argumento → modo interactivo
  }
```

💡 Resumiendo, piensa en los **argumentos** como las “palabras extra” que le dices al programa cuando lo ejecutas.

- Sin argumentos solo ejecutas el programa → entra al **modo interactivo**
- Si le das el nombre de un archivo → lo **interpreta**
- Si le das dos nombres de archivos → se confunde, te marca **error**

<br><hr/><br/>

## [3. 🏃‍♂️ Ejecutar un archivo de Brea con el interprete jBrea](#-índice-del-capitulo-3)

Cuando el usuario pasa un archivo, entramos en el método **runFile()**:

```java
    /**
     * Esta función se encarga de ejecutar un archivo .brea completo.
     *
     * Recibe un argumento llamado "path", que es simplemente la ruta del archivo
     * que el usuario escribió al ejecutar el programa desde la terminal.
     *
     * Ejemplo:
     *    jBrea miArchivo.brea
     *
     * En ese caso:
     *    path = "miArchivo.brea"
     */
    private static void runFile(String path) throws IOException{

        // 1. Leemos TODOS los bytes del archivo ubicado en la ruta "path".
        //    Si el archivo es "miArchivo.brea", entonces aquí estamos abriendo ese archivo.
        byte[] bytes = Files.readAllBytes(Paths.get(path));

        // 2. Convertimos esos bytes en una cadena de texto usando el charset del sistema.
        //    Ahora "source" es un String que contiene todo el programa escrito en Brea.
        String source = new String(bytes, Charset.defaultCharset());

        // 3. Le pasamos ese texto a la función run(), que será la que se encargue
        //    de enviarlo al scanner para convertir el código en tokens.
        run(source);
    }
```

**¿Qué hace exactamente?**

1. Lee todo el archivo en un arreglo de bytes
2. Convierte los bytes a una cadena con el charset del sistema
3. Llama a run(), que es quien procesará el contenido

Es decir, lo que realmente hacemos es **leer** todo el **contenido del archivo** 📂 que le pasamos por la terminal. Luego lo **convertimos a una cadena de texto** y finalmente lo pasamos a nuestra función central **run()**, que hará el trabajo de **procesarlo** ⚡

> 💡 Piensa en esto como: “¡Hey jBrea! Aquí tienes un archivo completo. Léelo y conviértelo en tokens.”

<br/><hr/><br/>

## [4. ⌨️ Ejecutar Brea de forma interactiva (REPL)](#-índice-del-capitulo-3)

El **modo interactivo** es súper útil cuando quieres probar ideas sin crear archivos. Es como una calculadora para el lenguaje. Vamos a crear un método que lo llamaremos **runPrompt()**:

```java
  /**
   * Esta función inicia el modo interactivo del intérprete,
   * también conocido como REPL:
   *
   *     R → Read  (leer)
   *     E → Eval  (evaluar)
   *     P → Print (imprimir)
   *     L → Loop  (repetir)
   *
   * Cuando el usuario ejecuta simplemente:
   *
   *      jBrea
   *
   * sin pasar ningún archivo como argumento, se activa este modo.
   * El objetivo es permitirle al usuario escribir código línea por línea
   * e ir viendo los resultados inmediatamente.
   */
  private static void runPrompt() throws IOException {

      /**
       * Primero creamos un lector que recoge lo que el usuario escribe en la consola.
       * System.in representa la entrada estándar (el teclado).
       * InputStreamReader convierte esos bytes en caracteres.
       */
      InputStreamReader input = new InputStreamReader(System.in);

      /**
       * BufferedReader permite leer texto de forma más cómoda y eficiente.
       * Se usa muy a menudo para leer del teclado, porque permite usar readLine().
       */
      BufferedReader reader = new BufferedReader(input);

      /**
       * Este es un ciclo infinito. Se escribe así: for (;;)
       *
       * En Java, for(;;) es equivalente a while(true).
       * Usamos un ciclo infinito porque queremos que el intérprete
       * siga funcionando hasta que el usuario decida terminar (Ctrl + D).
       */
      for(;;){

          // Mostramos el prompt en pantalla.
          // Esto es simplemente un indicador visual para el usuario.
          // Igual que Python usa ">>>", aquí podemos usar "> ". Como si quieres ponerle esto ~>
          // de hecho lo vamos a poner con ~>
          System.out.print("~> ");

          /**
           * Leemos una línea completa que el usuario escribe.
           * reader.readLine() espera hasta que el usuario presione ENTER.
           *
           * - Si el usuario escribe algo → devuelve ese texto.
           * - Si el usuario presiona Ctrl + D → devuelve null (fin de entrada).
           */
          String line = reader.readLine();

          /**
           * Esta condición detecta cuando line == null.
           * Esto significa que el usuario presionó Ctrl + D
           * (o Ctrl + Z en Windows, dependiendo del sistema),
           * indicando que ya no quiere seguir usando el intérprete.
           *
           * En ese caso, salimos del ciclo usando break.
           */
          if (line == null) break;

          /**
           * Si la línea NO es null, significa que el usuario escribió algo.
           * Entonces llamamos a run(line), que se encargará de enviar esa línea
           * al scanner y, por ahora, simplemente imprimir los tokens.
           *
           * Más adelante, run() también evaluará expresiones y ejecutará código real.
           */
          run(line);
      }
  }

```

**¿Qué está pasando aquí?**

- Creamos un **lector** que lee desde el teclado.
- Mostramos un **~>** cada vez para indicar que estamos listos a la espera que el usario escriba algo.
- Si el usuario escribe algo, lo pasamos a **run()**.
- Si presiona Ctrl + D (fin de archivo), salimos del REPL.

> Realizamos como un **ciclo**, gracias al bucle de nuestro código, es como si fuese: Leer → Procesar → Mostrar → Repetir. Hasta que el usuario quiera salir del REPL.

> 💡 **Nota sobre EOF (fin de archivo)**: Para salir del modo interactivo (REPL), necesitas enviar una señal de fin de entrada a la terminal. Dependiendo del sistema operativo, esta combinación de teclas cambia. **Linux / macOS**: usa Ctrl + D ; **Windows (cmd / PowerShell):** usa Ctrl + Z y luego presiona ENTER. Estas teclas le dicen a Java que ya no hay más texto para leer, por lo que readLine() devuelve null y el REPL se cierra.

<br/><hr/><br/>

## [5. ⚡ La función de nuestro interprete más importante por ahora: run()](#-índice-del-capitulo-3)

Esta función es el puente entre el **texto crudo** y los **tokens procesados**.

```java
    /**
     * La función run() es el centro del flujo del intérprete.
     *
     * Su trabajo es tomar el código fuente (source), enviarlo al scanner,
     * obtener la lista de tokens, y —por ahora— imprimirlos.
     *
     * Más adelante, esta función será mucho más importante porque:
     *   - enviará los tokens al parser
     *   - ejecutará expresiones
     *   - manejará errores
     *   - ejecutará instrucciones del lenguaje
     *
     * Pero en este momento, run() es simplemente el "puente" inicial
     * entre el texto que el usuario escribe y el análisis del lenguaje.
     */
    private static void run(String source){

        /**
         * 1- Creamos un nuevo scanner.
         *
         * El scanner es un objeto encargado de leer la cadena "source"
         * carácter por carácter. Su misión es dividir el texto en piezas
         * reconocibles llamadas *tokens*.
         *
         * Un token es básicamente:
         *   - una palabra clave (if, var, print…)
         *   - un identificador (nombre de variable)
         *   - un número
         *   - un símbolo ( = , ; , + , ( , { , etc.)
         *
         * El scanner no interpreta nada: solo "recorta" el código
         * en estas piezas pequeñas.
         */
        Scanner scanner = new Scanner(source);

        /**
         * 2- Le pedimos al scanner que convierta el texto en una lista completa de tokens.
         *
         * La función scanTokens() recorre el código entero, analiza carácter por carácter,
         * y genera una lista de objetos Token.
         *
         * Ejemplo: si el usuario escribe:
         *     var x = 5;
         *
         * Los tokens serían algo así como:
         *     TOKEN_VAR
         *     TOKEN_IDENTIFIER("x")
         *     TOKEN_EQUAL
         *     TOKEN_NUMBER(5)
         *     TOKEN_SEMICOLON
         *     TOKEN_EOF
         *
         * (TOKEN_EOF es un token especial para marcar el final del archivo)
         */
        List<Token> tokens = scanner.scanTokens();

        /**
         * 3- Por ahora, lo único que hacemos con los tokens es imprimirlos.
         *
         * Esto es súper útil en esta etapa del proyecto, porque:
         *   - podemos ver si el scanner está funcionando
         *   - podemos verificar si reconoce correctamente números, símbolos, identificadores, etc.
         *
         * Más adelante, esta impresión se eliminará y los tokens se pasarán al parser.
         */
        for (Token token : tokens) {

            // Imprimimos cada token en la consola.
            // La clase Token debe tener un método toString() que describa el token.
            System.out.println(token);
        }
    }

```

**¿Qué hace exactamente?**

- Creamos una **instancia del scanner**.
- Le pedimos que convierta todo el texto en una **lista de tokens**.
- Imprimimos esos **tokens** para verificar que el scanner funciona correctamente.

En este punto todavía no interpretamos nada. Solo estamos comprobando que somos capaces de leer código y dividirlo en piezas reconocibles.

Es decir, para concluir tenemos que **run()** recibe el código que escribió el usuario. Luego **crea un Scanner** para partir ese código en tokens. Pide al scanner que genere todos los tokens con scanTokens(). Finalmente imprime esos tokens para depurar y ver si el scanner funciona bien.

En el futuro, aquí se conectará el **parser → evaluador → ejecución del programa**.

> 💡 Piensa en esto como: Antes de cocinar una receta, primero debes preparar todos los ingredientes. El scanner se encarga de cortar, separar y etiquetar todo.

<br><hr/><br/>

## [6. 🌀 Del código al scanner: el flujo del interprete jBrea](#-índice-del-capitulo-3)

Cuando ejecutamos **jBrea**, ya sea pasando un archivo o simplemente abriendo el intérprete interactivo, la clase principal se encarga de decidir cómo procesar la entrada.

Si se proporciona un archivo, se llama a **runFile()**, y si no se pasa nada, se inicia el modo interactivo con **runPrompt()**.

En ambos casos, la entrada termina llegando a la función **run()**, que es la encargada de enviar todo el texto o código fuente al **scanner**.

El **scanner** analiza el código, lo divide en piezas más pequeñas llamadas **tokens**, y por ahora simplemente los imprime para que podamos ver que está funcionando correctamente.

Este **flujo** es la base de **jBrea**, porque antes de interpretar cualquier instrucción, necesitamos leer y reconocer todas las piezas del lenguaje.

```text
Entrada del usuario (archivo o consola)
                  ↓
      runFile()      runPrompt()
                  ↓
                run()
                  ↓
       Scanner analiza el texto
                  ↓
        Genera una lista de tokens
                  ↓
       (Temporalmente) los imprimimos

```

> 🔑 **Idea clave**: Antes de interpretar expresiones, funciones o variables, primero debemos ser capaces de reconocer los símbolos que las componen. El **scanner** es la primera etapa real de comprensión del lenguaje.

<br/><hr/><br/>

> 🛠️🛠️🛠️ desarrollando más secciones ...

<br/><hr/><br/>

| [↩️ Volver al inicio del Proyecto](../README.md) | [⬆️ Ir al inicio del Capítulo](#capítulo-3-el-inicio-del-interprete-scanning) | [⬅️ Ir a Capítulo 2](../docs/02-PiezasDeUnLenguaje.md) |
| :----------------------------------------------: | :---------------------------------------------------------------------------: | :----------------------------------------------------: |
