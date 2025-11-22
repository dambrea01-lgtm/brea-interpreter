# Capítulo 3: El inicio del Interprete (Scanning)

| [↩️ Volver al inicio del Proyecto](../README.md) | [⬅️ Ir a Capítulo 2](../docs/02-PiezasDeUnLenguaje.md) |
| :----------------------------------------------: | :----------------------------------------------------: |

<br/><hr/><br/>

> El primer paso para que **Brea** entienda nuestro código es convertir el texto en algo que el intérprete pueda procesar. En este capítulo trabajaremos con **jBrea**, la versión en Java. Más adelante construiremos **cBrea** en C, pero por ahora nos enfocamos en Java.

> El **scanner** lee cada carácter y los agrupa en **tokens**, que son como los bloques de construcción del lenguaje. 🧩 Al final, tendremos un pequeño **“traductor”** que convierte nuestro código en información clara para el **parser**, listo para analizar la lógica del programa.

<br/><hr/><br/>

## Índice del capitulo 3

| [1. 🛠️ Entendiendo el framework del intérprete jBrea](#1-️-entendiendo-el-framework-del-intérprete-jbrea) | Explicamos la estructura básica de jBrea, cómo se inicia, cómo procesa archivos y entrada interactiva, y la función central run() que prepara el código para el escáner. |

<br/><hr/><br/>

## [1. 🛠️ Entendiendo el framework del intérprete jBrea](#índice-del-capitulo-3)

Vamos a ver cómo construir nuestro **intérprete jBrea**, que ejecutará programas escritos en **Brea**. Piensa en esto como preparar los cimientos de una casa: todavía no vamos a hacer magia con el código, solo vamos a organizar la estructura básica para que todo funcione.

<br>

### 1️⃣ ¿Qué es un intérprete?

Antes de meternos en código, vamos a entender qué estamos construyendo. Un **intérprete** es un programa que **lee código** escrito en un lenguaje y lo **ejecuta directamente**, sin compilarlo antes a binario. 📝➡️💻

En nuestro caso, **Brea** es un lenguaje de scripting, así que nuestro **intérprete jBrea** va a leer las instrucciones que escribamos y ejecutarlas al momento.

<br>

### 2️⃣ La clase principal: jBrea.java

En Java, todas las aplicaciones empiezan con una clase y un método main(), que es el punto de entrada. Para jBrea, nuestra clase principal se ve así:

```java
    package com.lenguaje.brea;

    import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStreamReader;
    import java.nio.charset.Charset;
    import java.nio.file.Files;
    import java.nio.file.Paths;
    import java.util.List;

    public class Brea {
        public static void main(String[] args) throws IOException{
            if (args.length > 1){
                System.out.println("Uso: jBrea [script]");
                System.exit(64);
            }else if (args.length == 1){
                runFile(args[0]);
            }else{
                runPrompt();
            }
        }
    }
```

🔹 ¿Qué hace cada parte?:

- **main(String[] args)** es el punto de entrada.

- Control de argumentos:
  - Si pasas más de un archivo, muestra un error y termina con código de salida 64 ⚠️ (siguiendo las convenciones UNIX “sysexits.h”).
  - Si pasas un archivo, se ejecuta runFile(path) 📂.
  - Si no pasas nada, se ejecuta runPrompt() 🖊️💬, el modo interactivo.

<br>

### 3️⃣ Ejecutar un archivo de Brea con jBrea

Si tienes un archivo **.brea** y quieres correrlo completo, usamos:

```java
    private static void runFile(String path) throws IOException{
        byte[] bytes = Files.readAllBytes(Paths.get(path));
        run(new String(bytes, Charset.defaultCharset()));
    }
```

- 🔹 Explicación rápida:
  - Leemos todo el contenido del archivo 📂
  - Lo convertimos a una cadena de texto 📝
  - Lo pasamos a nuestra función central run(), que hará el trabajo de procesarlo ⚡

> 💡 Piensa en **runFile** como decirle a **jBrea**: "Aquí está mi programa **Brea**, hazlo tuyo"

### 4️⃣ Ejecutar Brea de forma interactiva (REPL)

Si solo quieres probar cosas rápidas, sin crear un archivo, usamos el modo interactivo:

```java
  private static void runPrompt() throws IOException{
    InputStreamReader input = new InputStreamReader(System.in);
    BufferedReader reader = new BufferedReader(input);
    for (;;){
        System.out.print("> ");
        String line = reader.readLine();
        if (line == null) break;
        run(line);
    }
  }
```

- 🔹 **Cómo funciona**:
  - Creamos un **lector** de la línea de comandos 🖥️
  - Mostramos un **prompt** > para que escribas código 🖊️
  - Leemos lo que escribes con **readLine()**
  - Si presionas **Control-D** ⌨️❌, significa “fin de archivo” y salimos 🔄🚪
  - En cualquier otro caso, enviamos la línea a **run()** ⚡

💡 Esto es básicamente un ciclo leer → ejecutar → mostrar resultado → repetir, que es la base de cualquier **REPL (Read-Eval-Print Loop)**.

### 5️⃣ La función central run()

Esta función es donde empezamos a procesar el código Brea:

```java
    private static void run(String source){
        Scanner scanner = new Scanner(source);
        List<Token> tokens = scanner.scanTokens();
        // Por ahora, solo imprime los tokens.
        for (Token token : tokens) {
            System.out.println(token);
        }
    }
```

- 🔹 **Qué hace ahora**:
  - Crea un scanner, que divide el código en tokens 🔍
  - Por ahora, solo imprime esos tokens 🖨️
  - Esto nos permite ver si nuestro escáner funciona, aunque todavía no interpretemos nada 🎯

> 💡 Recuerda: cada paso cuenta. Ahora no ejecuta programas completos, pero estamos construyendo la base de jBrea 👣

<br>

### 6️⃣ Resumen del flujo de jBrea

Antes de ver el diagrama, conviene entender qué ocurre desde que le pasamos un programa a jBrea hasta que vemos los resultados:

- Primero, **jBrea** recibe entrada, que puede ser un archivo **.brea** o una línea que escribes en el prompt interactivo.

- Luego decide cómo procesar esa entrada: si es un archivo, llama a **runFile()**, y si es interactiva, llama a **runPrompt()**.

- En ambos casos, la entrada termina en la función **run()**, que es donde empieza a desglosarse el código.

- **run()** usa un **scanner** para dividir el texto en **tokens**, que son las piezas más pequeñas del lenguaje: palabras clave, números, símbolos, etc.

- Por ahora, **jBrea** solo imprime esos **tokens** para que podamos comprobar que todo se está leyendo correctamente.

Ahora sí, el diagrama visual del flujo sería:

```bash
Archivo o línea de comando
          ↓
      runFile() / runPrompt()
          ↓
        run(source)
          ↓
   Scanner → Lista de tokens
          ↓
   (Por ahora) imprimir tokens
```

> 🔑 La idea: antes de ejecutar instrucciones complejas, primero necesitamos leer y reconocer las piezas básicas del lenguaje.

<br/><hr/><br/>

| [↩️ Volver al inicio del Proyecto](../README.md) | [⬆️ Ir al inicio del Capítulo](#capítulo-3-el-inicio-del-interprete-scanning) | [⬅️ Ir a Capítulo 2](../docs/02-PiezasDeUnLenguaje.md) |
| :----------------------------------------------: | :---------------------------------------------------------------------------: | :----------------------------------------------------: |
