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
| [7. 🧯 Manejo de errores en el intérprete](#7--manejo-de-errores-en-el-intérprete)                                                          | Explicamos la importancia de los errores, cómo reportarlos con `error()` y `report()`, la bandera `hadError`, y cómo se integra en `runFile()` y `runPrompt()` para evitar ejecutar código roto.           |
| [8. 🔍 Léxicos y Tokens](#8--léxicos-y-tokens)                                                                                              | Introducimos el análisis léxico, explicamos qué son **lexemas** y **tokens**, cómo se representan en Java con `TokenType` y `Token`, y cómo el scanner procesa los caracteres del código fuente.           |

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

## [7. 🧯 Manejo de errores en el intérprete](#-índice-del-capitulo-3)

Cuando estamos construyendo un **intérprete**, es muy fácil concentrarse solo en “que funcione” y dejar los errores para más adelante. A mí también me pasó al principio. Sin embargo, el manejo de errores es una parte clave del lenguaje, incluso aunque no lo parezca.

Si queremos que **Brea** sea un lenguaje que se pueda usar de verdad, entonces mostrar buenos errores es obligatorio.

<br/>

### 🤔 ¿Por qué los errores son tan importantes?

Piénsalo desde el punto de vista del usuario: Cuando su código funciona bien, no piensa en el lenguaje. Está concentrado en su programa, en la lógica, en resolver su problema.

El **intérprete** es **invisible**.

Pero cuando aparece un error… ahí sí el **intérprete** entra en escena. En ese momento, el usuario depende totalmente de nosotros para entender: qué hizo mal, dónde está el error, cómo arreglarlo ...

Si el **mensaje de error** es confuso, el usuario se frustra. En cambio si es claro, aprende más rápido y sigue adelante. Por eso se dice que los **mensajes de error** son parte de la interfaz del lenguaje.

🚨 El **mínimo indispensable** en un interprete es: decir qué pasó y en qué línea

Para empezar, vamos a implementar lo mínimo necesario para poder decir que **Brea** tiene **manejo de errores**:

👉 indicar que ocurrió un error
👉 mostrar en qué línea del código ocurrió

No es perfecto, pero es mucho mejor que no decir nada.

Vamos a centralizar este comportamiento en la **clase principal Brea**, para que cualquier parte del **intérprete** pueda reportar errores de la misma forma.

<br/>

### 🧩 Funciones básicas de reporte de errores

Dentro de **Brea**, después del **método run()** descrita en el apartado anterior, agregamos estas funciones:

<br/>

```java
  /**
   * Función pública y estática para reportar errores en el intérprete.
   *
   * Esta es la función que usaremos desde otras partes del código
   * (scanner, parser, etc.) cuando detectemos un error.
   *
   * ¿Por qué es static?
   * - Porque pertenece al intérprete en general, no a una instancia concreta.
   * - Nos permite llamarla fácilmente como: Brea.error(...)
   *
   * @param line    Número de línea donde ocurrió el error.
   * @param message Mensaje que explica qué salió mal.
   */
  static void error(int line, String message) {

      // No imprimimos el error directamente aquí.
      // En su lugar, delegamos el trabajo a la función report().
      //
      // El segundo parámetro ("where") se deja vacío por ahora.
      // Más adelante podría servir para indicar información extra
      // sobre la posición exacta del error.
      report(line, "", message);
  }

  /**
   * Función interna que se encarga de mostrar el error al usuario.
   *
   * Es privada porque solo debe ser usada dentro de esta clase.
   * El resto del intérprete nunca debería llamarla directamente.
   *
   * @param line    Línea del código fuente donde ocurrió el error.
   * @param where   Información adicional sobre la ubicación del error
   *                (por ahora no la usamos, pero queda preparada).
   * @param message Descripción clara del error.
   */
  private static void report(int line, String where, String message) {

      // Usamos System.err en lugar de System.out porque:
      // - System.out se usa para la salida normal del programa
      // - System.err se usa específicamente para mensajes de error
      //
      // Esto es una buena práctica en aplicaciones de consola.
      System.err.println(

          // Construimos el mensaje de error con el siguiente formato:
          //
          // [line X] Error: mensaje
          //
          // Ejemplo:
          // [line 10] Error: Unexpected ',' in argument list.
          "[line " + line + "] Error" + where + ": " + message
      );

      // Marcamos que ocurrió un error durante la ejecución.
      //
      // Esta variable (hadError) se usa más adelante para:
      // - evitar ejecutar código con errores
      // - decidir si el programa debe finalizar
      // - controlar el comportamiento del REPL
      hadError = true;
  }
```

<br/>

**¿Qué está pasando aquí?**

Tenemos la función **error(...)** que usaremos desde otras partes del intérprete. La función **error** como parámetro: el **número de línea** donde ocurrió el error y un **mensaje** que explique qué pasó.

Esta función no imprime nada directamente. En su lugar, llama a la función **report(...)**.

**🔧 ¿Por qué dos funciones y no una sola?**

La función **report(...)** es la función que realmente imprime el mensaje. La separamos porque más adelante podríamos querer: agregar más contexto, cambiar el formato del error o reutilizar la lógica.

Por ahora, **where** está vacío, pero dejamos el diseño preparado para el futuro. Donde podemos mejorar nuestro interprete, una vez en funcionamiento.

**📌 ¿Qué imprime el error?**

Un mensaje como este: [line 15] Error: Unexpected "," in argument list.

Esto ya es suficiente para que el usuario: sepa que hubo un error y vaya directo a la línea correcta.

**😖 Ejemplo de un mal mensaje de error**

Supongamos que el usuario escribe algo así en Brea:

```java
  var x = 10
  print(x
```

En este caso, olvidó cerrar el paréntesis en la función print. Si nuestro intérprete fuera muy básico, podría mostrar algo como esto:

```text
  Error: Algo salió mal. Revisa tu código.
```

Este tipo de mensaje es malo porque no dice la línea donde ocurrió el error. Tampoco dice qué parte del código provocó el error, no sabemos si el error está en var x = 10 o en print(x.

Por lo tanto, este tipo de mensajes no ayuda a corregir nuestros errores: el mensaje es genérico, no orienta al usuario a cómo arreglarlo. En resumen, es frustrante y confunde más que ayuda.

**🌟 Ejemplo de un error más útil (aunque aún simple)**

Un mensaje de error mucho más comprensible podría ser así:

```text
  [línea 2] Error: Se esperaba ')' después de los argumentos.
  2 | print(x
          ^-- Aquí
```

Este tipo de mensaje se indica la línea exacta (line 2) donde se cometió el error. También se explica qué pasó (Expected ')' after arguments). Además se señala la posición en el código con una flecha (^-- Aquí)

Ahora el usuario sabe exactamente dónde mirar y qué corregir: simplemente agregar un paréntesis al final de print(x).

Esto es increíblemente útil… pero también requiere mucho código extra, especialmente para manipular strings y posiciones de caracteres. Para este tutorial, no vale la pena complicarnos tanto. Nos quedamos con el número de línea, que ya aporta muchísimo valor.

<br />

### 🚦 La bandera hadError: evitando ejecutar código roto

Ahora viene una parte muy importante. Dentro de la **clase Brea**, definimos esta variable:

```java
  static boolean hadError = false;
```

Esta bandera nos permite saber si ocurrió algún error en el proceso. Cada vez que se llama a **report(...)**, la marcamos como **true**.

**🛑 ¿Para qué sirve esto?**

Sirve para evitar ejecutar código que sabemos que está mal. Por ejemplo, cuando ejecutamos un archivo completo:

```java
  // Llamamos a la función run() y le pasamos todo el contenido del archivo.
  // bytes contiene los datos del archivo leídos como un arreglo de bytes.
  // Con `new String(bytes, Charset.defaultCharset())` convertimos esos bytes
  // en un String usando el charset por defecto del sistema (UTF-8 en la mayoría de casos).
  // Esto nos da el contenido completo del archivo como texto, listo para que
  // el intérprete lo procese.
  run(new String(bytes, Charset.defaultCharset()));

  // Revisamos si ocurrió algún error durante la ejecución de run().
  // La variable hadError se pone a true dentro de las funciones de manejo de errores
  // (como report()) cada vez que detectamos un problema.
  // Si hubo algún error, salimos inmediatamente del programa con un código de salida distinto de cero.
  // En este caso, usamos System.exit(65), siguiendo la convención de códigos de error de Unix.
  // Esto evita que el intérprete intente ejecutar un código que sabemos que está incorrecto.
  if (hadError) System.exit(65);
```

Si hubo errores: no seguimos ejecutando y salimos del programa con un código distinto de cero. De esta forma, nos comportamos como un buen programa de línea de comandos.

Por lo tanto, debemos agregar una condición en nuestra función **runFile** para que, en caso de que ocurra un error, el programa termine de manera segura con un código de salida distinto de cero. La función quedaría de la siguiente manera:

```java
  private static void runFile(String path) throws IOException{

        // Leemos todos los bytes del archivo especificado por "path"
        byte[] bytes = Files.readAllBytes(Paths.get(path));

        // Convertimos los bytes a un String usando el charset por defecto del sistema
        String source = new String(bytes, Charset.defaultCharset());

        // Ejecutamos el contenido del archivo
        run(source);

        // Si ocurrió algún error durante la ejecución, salimos del programa
        // con un código de salida 65 para indicar que hubo un fallo
        if (hadError) System.exit(65);
    }
```

**🔄 ¿Y qué pasa en el modo interactivo (REPL)?**

En el REPL no queremos que un error mate toda la sesión. Por eso, después de ejecutar cada línea, reiniciamos la bandera:

```java
  // Ejecutamos la línea de código que el usuario acaba de escribir en el REPL.
  // `line` es un String que contiene exactamente lo que el usuario escribió.
  // La función run() se encargará de procesarla: pasarla al scanner, generar tokens,
  // y, eventualmente, evaluar o ejecutar la instrucción.
  run(line);

  // Reiniciamos la bandera hadError después de ejecutar la línea.
  // Esto es importante porque estamos en modo interactivo (REPL):
  // - Si el usuario cometió un error en esta línea, ya se mostró el mensaje correspondiente.
  // - Pero no queremos que ese error bloquee las siguientes líneas que escriba.
  // Por eso ponemos hadError = false, para que el intérprete siga funcionando
  // y pueda procesar nuevas líneas aunque la anterior tuviera errores.
  hadError = false;

```

De esta forma: el usuario comete un error, se muestra el mensaje y puede seguir escribiendo código sin reiniciar el intérprete.

Entonces para el **modo interactivo (REPL)** también debemos considerar el manejo de errores. Como cada línea que el usuario escribe se ejecuta de manera independiente, es importante reiniciar la bandera **hadError** después de procesar cada línea. Esto garantiza que un **error** en una línea no bloquee la ejecución de las siguientes. La función **runPrompt** con la integración de **hadError** quedaría así:

```java
  private static void runPrompt() throws IOException {

      // Creamos un lector que recoge lo que el usuario escribe en la consola
      InputStreamReader input = new InputStreamReader(System.in);
      BufferedReader reader = new BufferedReader(input);

      // Ciclo infinito para mantener activo el REPL hasta que el usuario decida salir
      for (;;) {

          // Mostramos un prompt visual para que el usuario escriba su línea de código
          System.out.print("~> ");

          // Leemos la línea que el usuario escribió
          String line = reader.readLine();

          // Si el usuario envía EOF (Ctrl+D o Ctrl+Z + ENTER), salimos del REPL
          if (line == null) break;

          // Ejecutamos la línea usando run()
          run(line);

          // Reiniciamos la bandera hadError para que el REPL pueda continuar
          // aun si hubo un error en la línea anterior
          hadError = false;
      }
  }
```

<br/>

### 🧱 Separar quién detecta errores y quién los muestra

El **manejo de errores** en un **intérprete** debe estar bien organizado. El **scanner**, el **parser** y otras fases pueden **detectar errores**, pero no es su responsabilidad decidir cómo **mostrar esos errores**. Mostrar errores es una tarea separada, que depende del **entorno o la interfaz de usuario**.

Por ejemplo, en un proyecto más grande, los errores pueden mostrarse en la consola, en un IDE, o incluso guardarse en un archivo de registro (log).

Para evitar que el código del scanner o del parser se complique con detalles de presentación, es recomendable separar la **lógica de detección de errores** de la **lógica de presentación**.

En este caso, aunque no se implementa una solución tan avanzada como una interfaz **ErrorReporter**, al menos centralizamos el **reporte de errores** en la **clase principal Brea**, lo que simplifica el mantenimiento y mejora la organización del código.

Esto ayuda a que el sistema sea más **flexible y modular**, lo que es clave cuando el proyecto crece.

<br/><hr/><br/>

## [8. 🔍 Léxicos y Tokens](#-índice-del-capitulo-3)

Cuando nuestro **intérprete** recibe un código, lo primero que hace es entender qué significan las letras y símbolos. Esto se llama **análisis léxico.**

Imagina esta línea en Brea:

```java
  var name = "brea";
```

Aquí podemos lo siguiente:

- **var** es una palabra clave que indica que estamos declarando una variable.
- **"name"** es el nombre de la variable.
- **"="** es el operador de asignación.
- **"brea"** es una cadena literal.
- **";"** marca el final de la instrucción.

El **scanner** lee carácter por carácter y agrupa las letras en bloques que tengan significado. A cada uno de estos bloques lo llamamos **lexema**. En este ejemplo, los **lexemas** serían:

```text
  var
  name
  =
  "brea"
  ;
```

> 💡 **Tip:** Si sacas caracteres al azar, como "a-m-e" de name, eso no tendría significado. El **análisis léxico** se trata de dar sentido a los caracteres, no solo leerlos.

<br/>

### 🔑 Tokens: cuando los lexemas se vuelven útiles

Un **lexema** es solo la subcadena del código fuente, pero para que nuestro **intérprete** pueda trabajar con él, necesitamos agregar información extra, como:

- **Tipo de token** (VAR, IDENTIFIER, STRING, PLUS, etc.)
- **Valor literal** (para números o strings)
- **Línea donde apareció** (para reportar errores)

Cuando combinamos un **lexema** con esta información, obtenemos un **token**.

Esto permite que el **parser** no tenga que comparar strings cada vez. Por ejemplo, cuando el **parser** ve un token VAR, sabe que es la palabra clave para declarar variables, sin tener que revisar si el lexema es "var".

<br />

### 📝 Enum TokenType

Para que el **intérprete** reconozca qué tipo de **token** es cada **lexema**, definimos un **enumerado en Java**. Cada tipo de token corresponde a algo que el lenguaje Brea reconoce:

- Palabras clave: VAR, IF, WHILE, etc.
- Operadores: PLUS, MINUS, EQUAL, etc.
- Literales: STRING, NUMBER
- Signos de puntuación: SEMICOLON, COMMA, LEFT_PAREN, etc.

Creamos un archivo **TokenType.java** dentro de tu paquete principal lenguaje.brea junta a la clase principal:

<br/>

```java
  package lenguaje.brea;

  /**
   * Enum que lista todos los tipos de tokens que nuestro intérprete reconoce.
   * Cada constante indica qué tipo de lexema representa.
   */
  public enum TokenType {

      // Tokens de un solo carácter
      LEFT_PAREN,    // '(' paréntesis izquierdo
      RIGHT_PAREN,   // ')' paréntesis derecho
      LEFT_BRACE,    // '{' llave izquierda
      RIGHT_BRACE,   // '}' llave derecha
      COMMA,         // ',' coma
      DOT,           // '.' punto
      MINUS,         // '-' signo menos
      PLUS,          // '+' signo más
      SEMICOLON,     // ';' punto y coma
      SLASH,         // '/' barra
      STAR,          // '*' asterisco

      // Tokens de uno o dos caracteres
      BANG,          // '!' signo de exclamación
      BANG_EQUAL,    // '!=' diferente
      EQUAL,         // '=' igual
      EQUAL_EQUAL,   // '==' igual a
      GREATER,       // '>' mayor que
      GREATER_EQUAL, // '>=' mayor o igual
      LESS,          // '<' menor que
      LESS_EQUAL,    // '<=' menor o igual

      // Literales
      IDENTIFIER,    // nombres de variables o funciones
      STRING,        // literales de texto entre comillas
      NUMBER,        // literales numéricos

      // Palabras clave
      AND, IF, ELSE, OR,    // operadores lógicos y condicionales
      CLASS, FUN, RETURN,   // definiciones y retorno de funciones/clases
      TRUE, FALSE, NIL,     // valores booleanos y nulos
      FOR, WHILE,           // bucles
      VAR,                  // declaración de variables
      PRINT,                // imprimir en consola
      SUPER, THIS,          // referencias a objetos y herencia

      // Fin de archivo
      EOF                   // indica que no hay más tokens en el código fuente
  }

```

<br/>

💡 Explicación rápida: Cada tipo corresponde a algo que el lenguaje reconoce. Por ejemplo:

- VAR → palabra clave para declarar variables.
- PLUS → el símbolo +.
- STRING → cualquier literal de texto entre comillas.

Esto permite que el **parser** no tenga que comparar cadenas cada vez, lo que sería lento. Cuando el **scanner** reconoce un **lexema**, ya sabe qué **tipo de token** es.

<br/>

### 📝 Clase Token

Luego, para agrupar toda la información de un **token** (tipo, lexema, valor literal y línea), creamos una clase Token:

<br/>

```java
  package lenguaje.brea;

  /**
   * Representa un token en Brea.
   * Contiene información útil para el parser y para mostrar errores.
   */
  public class Token {

      final TokenType type;   // Tipo del token (palabra clave, operador, literal, etc.)
      final String lexeme;    // La subcadena exacta del código fuente
      final Object literal;   // Valor literal (para números, strings, etc.)
      final int line;         // Línea en la que aparece este token

      /**
       * Constructor de Token
       * @param type Tipo de token
       * @param lexeme Subcadena del código fuente
       * @param literal Valor literal, si aplica
       * @param line Línea donde aparece el token
       */
      public Token(TokenType type, String lexeme, Object literal, int line) {
          this.type = type;
          this.lexeme = lexeme;
          this.literal = literal;
          this.line = line;
      }

      /**
       * Representación en texto del token
       * Útil para depuración mientras construimos el intérprete
       */
      @Override
      public String toString() {
          return type + " " + lexeme + " " + literal;
      }
  }

```

<br/>

**💡 Cómo funciona esto:** Cuando el **scanner** encuentra un **lexema**, crea un **token**. El **token** guarda la siguiente información:

- Tipo de token (por ejemplo VAR o IDENTIFIER)
- Lexema (la cadena real "var" o "language")
- Literal (el valor real si aplica, como "brea")
- Línea donde apareció

<br/>

### 📝 Optimización de posición

Cuando el **scanner** analiza el código fuente, lee carácter por carácter para formar **lexemas**. Algunos **intérpretes** guardan dos datos extra para cada **token**:

1. **Offset (desplazamiento)**: la posición en el archivo donde empieza el lexema. Por ejemplo, si tu archivo empieza así:

```java
  var name = "brea";
```

y el scanner está leyendo "name", el **offset** sería 4, porque "n" es el quinto carácter del archivo (contando desde 0).

2. **Longitud del lexema:** cuántos caracteres ocupa el lexema. En el ejemplo, "name" tiene 4 caracteres, así que la longitud es 4.

Con estos dos valores, más tarde podemos calcular fácilmente en qué línea y columna está el lexema, contando los saltos de línea anteriores. Esto es útil si queremos mostrar mensajes de error como:

```java
  [line 1, col 5] Error: Unexpected token
```

> 💡 Importante: Guardar **offset y longitud** no añade mucho trabajo porque el scanner ya recorre todos los caracteres. Solo necesitamos convertir **offset → línea/columna** cuando realmente queremos mostrar un **error**. La mayoría de los tokens nunca aparecen en mensajes de error, así que no tiene sentido calcular su posición exacta por adelantado; sería una pérdida de tiempo.

<br/>

### 🌟 ¡Sigamos avanzando!

Cada **token** que identificamos y cada **lexema** que agrupamos son pasos esenciales para construir nuestro **intérprete Brea**. Puede parecer solo un análisis de texto, pero poco a poco estamos formando las piezas que más adelante permitirán ejecutar programas completos. Paso a paso, línea a línea, nuestro **intérprete** va tomando forma: lo que ahora son **tokens** será pronto **código vivo** que podremos **ejecutar y probar**.

<br/><hr/><br/>

> 🛠️🛠️🛠️ desarrollando más secciones ...

<br/><hr/><br/>

| [↩️ Volver al inicio del Proyecto](../README.md) | [⬆️ Ir al inicio del Capítulo](#capítulo-3-el-inicio-del-interprete-scanning) | [⬅️ Ir a Capítulo 2](../docs/02-PiezasDeUnLenguaje.md) |
| :----------------------------------------------: | :---------------------------------------------------------------------------: | :----------------------------------------------------: |
