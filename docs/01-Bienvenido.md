# Capítulo 1: Introducción al proyecto Brea 🧩

| [↩️ Volver al inicio del Proyecto](../README.md) | [➡️ Capítulo 2](../docs/02-PiezasDeUnLenguaje.md) |
| :----------------------------------------------: | :-----------------------------------------------: |

<br/><hr/><br/>

Bienvenido al mundo de Brea. Este capítulo es la **puerta de entrada para comprender cómo funciona un lenguaje de programación desde cero** y cómo se construye un intérprete funcional en Java. Nuestro enfoque es **aprender haciendo**, entendiendo la teoría mientras desarrollamos código real.

<br/><hr/><br/>

# 📚 Índice del Capítulo

| Sección                                                                                                        | Descripción                                                                             |
| :------------------------------------------------------------------------------------------------------------- | :-------------------------------------------------------------------------------------- |
| [1. 🧩 Introducción](#1--introducción)                                                                         | Qué aprenderás en esta primera etapa y cuál es el objetivo.                             |
| [2. 🤔 Por qué aprender a construir un intérprete](#2--por-qué-aprender-a-construir-un-intérprete)             | Razones para crear tu propio lenguaje e intérprete.                                     |
| [3. ☕ Nuestro primer intérprete: jBrea en Java](#3--nuestro-primer-intérprete-jbrea-en-java)                  | Primera versión del intérprete escrita en Java.                                         |
| [4. ⚙️ Segunda fase: cBrea en C](#4-️-segunda-fase-cbrea-en-c)                                                 | Versión en C para comprender la ejecución a bajo nivel.                                 |
| [5. 🧪 El aprendizaje práctico](#5--el-aprendizaje-práctico)                                                   | Cómo combinaremos teoría, práctica y desafíos.                                          |
| [6. 🔑 Conceptos clave a dominar](#6--conceptos-clave-a-dominar)                                               | Diferencias entre intérprete y compilador, lexing, parsing y runtime.                   |
| [7. 💻 Primer vistazo al lenguaje Brea y tipos de datos](#7--primer-vistazo-al-lenguaje-brea-y-tipos-de-datos) | Introducción al lenguaje Brea, tipado dinámico y tipos de datos básicos.                |
| [8. ⚡ Expresiones, operadores y control de flujo](#8--expresiones-operadores-y-control-de-flujo)              | Cómo combinar variables y operadores, estructuras de control y bloques.                 |
| [9. 🛠️ Funciones, closures y clases](#9️-funciones-closures-y-clases)                                          | Creación de funciones, closures, clases y herencia con `<`.                             |
| [10. 💡 Lo que aprenderás creando un lenguaje](#10--lo-que-aprenderás-creando-un-lenguaje)                     | Qué habilidades y conocimientos profundos adquirirás al implementar un lenguaje propio. |
| [11. ✏️ Ejercicios propuestos](#11-️-ejercicios-propuestos)                                                    | Actividades y desafíos prácticos para reforzar lo aprendido en este capítulo.           |

<br/><hr/><br/>

## 1. [🧩 Introducción](#-índice-del-capítulo)

En esta primera etapa vamos a:

- Conocer los **conceptos fundamentales de los lenguajes de programación**.
- Comprender la arquitectura básica de un intérprete.
- Prepararnos para implementar Brea, un lenguaje sencillo pero completo.

El objetivo es que al final es que tengamos **una visión clara de cómo un lenguaje vive y respira**, y que estés listo para empezar a programar tu propio intérprete.

<br/><hr/><br/>

## 2. [🤔 Por qué aprender a construir un intérprete](#-índice-del-capítulo)

Crear un lenguaje puede parecer intimidante, pero pienso que es un **ejercicio extremadamente valioso** para cualquier programador, te enumero algunos motivos:

1. **Profundiza tu comprensión de estructuras de datos**: árboles sintácticos, grafos y tablas hash se vuelven conceptos que realmente entiendes al implementarlos.
2. **Refuerza tus habilidades en algoritmos**: análisis léxico, análisis sintáctico, recursión y manejo de memoria son fundamentales.
3. **Mejora tu diseño de software**: al organizar el código en clases, métodos y módulos claros, aprendes buenas prácticas de arquitectura.
   (...)

Incluso si no planeas crear un lenguaje de propósito general, los **lenguajes de dominio específico** están en todas partes: scripts de automatización, motores de plantillas, formatos de configuración y archivos de datos. Comprender cómo funcionan te permitirá **adaptarte y crear soluciones personalizadas cuando sea necesario**.

<br/><hr/><br/>

## 3. [☕ Nuestro primer intérprete: jBrea en Java](#-índice-del-capítulo)

Para empezar, construiremos **jBrea**, un intérprete simple en Java. La elección de Java tiene varias ventajas:

- Es **tipado y explícito**, lo que permite ver claramente la estructura de los datos que usamos.
- Es lo suficientemente **alto nivel** como para concentrarnos en la lógica sin perdernos en detalles de bajo nivel.
- Permite **programación orientada a objetos**, organizando el código en clases y métodos, lo que facilita la modularidad y reutilización.

Nuestro objetivo inicial será un intérprete **correcto y comprensible**, dejando la optimización de rendimiento para etapas posteriores. Nos enfocaremos en:

1. **Lexing (análisis léxico)**: convertir el código fuente en una serie de tokens.
2. **Parsing (análisis sintáctico)**: transformar los tokens en una estructura que represente la lógica del programa.
3. **Evaluación y runtime**: ejecutar instrucciones según la semántica de Brea.

Este enfoque nos permitirá **ver claramente cómo cada parte del intérprete interactúa con las demás**, y cómo las decisiones de diseño afectan el comportamiento del lenguaje.

<br/><hr/><br/>

## 4. [⚙️ Segunda fase cBrea en C](#-índice-del-capítulo)

Más adelante construiremos **cBrea**, la versión en C, con el objetivo de:

- Entender **cómo se gestionan los datos a nivel de memoria y CPU**.
- Implementar estructuras dinámicas y tablas hash desde cero.
- Construir un **recolector de basura** y un compilador de bytecode eficiente.

Mientras jBrea nos enseña la lógica y la claridad conceptual, cBrea nos permitirá **profundizar en eficiencia y control de ejecución**, mostrando cómo las máquinas realmente interpretan nuestro lenguaje.

<br/><hr/><br/>

## 5. [🧪 El aprendizaje práctico](#-índice-del-capítulo)

La mejor manera de entender un lenguaje es **interactuar con él**:

- Cada sección de mi tutorial combinará **teoría con práctica**.
- Incluiré **ejemplos claros y fragmentos de código** para que puedas ejecutar y experimentar.
- Pondré **desafíos opcionales**, donde aplicaremos lo aprendido y exploraremos soluciones por nuestra cuenta.

Esta metodología asegura que **la comprensión no sea solo teórica**, sino basada en experiencias prácticas que nos preparan para proyectos más complejos.

<br/><hr/><br/>

## 6. [🔑 Conceptos clave a dominar](#-índice-del-capítulo)

Antes de comenzar a programar, es importante familiarizarse con algunos conceptos esenciales:

### Intérprete y compilador

- **Intérprete:** ejecuta directamente el código fuente, línea por línea, permitiendo **experimentación rápida y depuración sencilla**.
- **Compilador:** traduce el código a otro lenguaje o a un formato ejecutable, generalmente más eficiente.

> 💻 Un compilador es un programa que lee archivos en un lenguaje, los traduce 🔄 y genera archivos en otro lenguaje 📄➡️📄. Puedes implementar un compilador en cualquier lenguaje —incluso en el mismo lenguaje que compila! 🔁. Esto se llama **self-hosting** .
>
> **Bootstrapping 🥾:** al principio necesitas otro compilador para compilar tu compilador. Una vez compilado, tu compilador puede **compilar futuras versiones de sí mismo**, descartando el compilador original. Este proceso se llama **bootstrapping**.
>
> **Lexing (Análisis léxico)**: convertir el código fuente en tokens identificables por el intérprete.
> **Parsing (Análisis sintáctico)**: organizar los tokens en una estructura que represente correctamente la lógica y reglas del lenguaje.
> **Runtime / Evaluación**: ejecutar las instrucciones del lenguaje siguiendo su semántica y reglas de alcance, variables, funciones y control de flujo.

> Estos conceptos son muy importante para que construyamos nuestro proyecto paso a paso.

<br/><hr/><br/>

## 7. [💻 Primer vistazo al lenguaje Brea y tipos de datos](#-índice-del-capítulo)

Vamos a explorar un poco el **lenguaje Brea** en sí y sus elementos fundamentales. Esta sección te ayudará a sentirte cómodo con los bloques de construcción de **Brea** antes de empezar a escribir tu intérprete.

<br/>

### Tipado dinámico en Brea

**Brea** es un lenguaje **dinámicamente tipado**, lo que significa que no necesitas declarar el tipo de tus variables, y puedes **cambiar el tipo de dato** de una variable **durante la ejecución**. Esto hace que programar sea más ágil y menos rígido:

```javascript
var miVariable = 88; // empieza como número
miVariable = "Ahora he cambiado y soy un texto"; // ahora es cadena
```

Esto es genial para aprender rápido y experimentar, pero recuerda que ⚠️ **los errores de tipo** solo aparecerán en **tiempo de ejecución**, no mientras escribes el código.

<br/>

### Tipos de datos básicos

En **Brea**, los tipos de datos incorporados son pocos y simples. ¡Perfectos para comenzar a construir nuestro lenguaje sin complicaciones! 🎯:

- **Booleanos: true y false**. Representan decisiones lógicas y control de flujo.

```javascript
var esEstudiante = true;
var tieneExamen = false;
```

- **Números**: Todos son de **punto flotante de doble precisión**, así que no tienes que preocuparte por enteros, hexadecimales o notaciones raras.

```javascript
var edad = 21;
var promedio = 12.5;
```

- **Cadenas (Strings)**: Textos entre comillas dobles. Pueden contener cualquier carácter.

```javascript
var nombre = "Brea";
var mensaje = "Hola, " + nombre;
```

- **nulo**: Representa "ningún valor", algo así como **null** en otros lenguajes.

```javascript
var indefinido;
print indefinido; // nulo
```

En Brea, **nulo** siempre aparece cuando no hay un valor asignado. Esto evita errores de punteros nulos al estilo C, pero ten cuidado de no asumir que una variable contiene un valor válido.

<br/><hr/><br/>

## 8. [⚡ Expresiones, operadores y control de flujo](#-índice-del-capítulo)

Una vez que entendemos los tipos de datos, podemos combinarlos en expresiones para realizar cálculos y decisiones lógicas.

<br/>

### Operadores básicos

- **Aritmética**: + - \* /

```javascript
   var a = 6;
   var b = 2;
   print a + b;  // 8
   print a - b;  // 4
   print a * b;  // 12
   print a / b;  // 3.0
```

- **Negación**: - también funciona como prefijo para negar valores.

```javascript
   var negativo = -10;
   print negativo; // -10
```

- **Concatenación de cadenas**: +

```javascript
var saludo = "Hola, " + "mundo!";
print saludo; // "Hola, mundo!"
```

- **Comparación y lógica**: < <= > >= == != ! and or. Decir que and y or usan short-circuit, evaluando solo lo necesario para no entrar en asuntos complejos:

```javascript
   true and false;  // false
   false or true;   // true
```

### Sentencias y bloques

Mientras que las expresiones devuelven valores, las sentencias producen efectos: muestran información, cambian variables, o controlan el flujo.

```javascript
   print "¡Hola, estudiante!";
   var x = 5;
   x = x + 1;
```

Para agrupar varias sentencias usamos bloques:

```javascript
   {
      print "Primera sentencia dentro de un bloque";
      print "Segunda sentencia dentro de un bloque";
   }
```

Los **bloques** también definen **alcance local** para las **variables**, algo muy importante cuando manejamos funciones y objetos.

### Control de flujo

**Brea** tiene estructuras de control típicas que ya conoces de C o Java:

```javascript
   // If-else
   if(x > 0){
      print "Positivo";
   }else{
      print "Cero o negativo";
   }

   // While
   var contador = 0;
   while(contador < 3){
      print contador;
      contador = contador + 1;
   }

   // For
   for(var i = 0; i < 3; i = i + 1){
      print i;
   }
```

Si solo tuviéramos and, or y recursión, podríamos hacer todo el control de flujo, pero los bucles y el if hacen la vida mucho más fácil.

<br/><hr/><br/>

## 9.[🛠️ Funciones, closures y clases](#-índice-del-capítulo)

Ahora viene la parte más divertida: **funciones y objetos**. Estas son las piezas que hacen que **Brea** sea más que un simple lenguaje de scripting.

### Funciones y closures

En **Brea**, las **funciones** son valores de **primera clase**, lo que significa que podemos:

- Guardarlas en variables.
- Pasarlas como argumentos.
- Devolverlas desde otras funciones.

```javascript
   fun sumar(a, b){
      return a + b;
   }

   fun usarFuncion(f){
      print f(2, 3);
   }

   usarFuncion(sumar); // imprime 5
```

Si declaramos **funciones dentro de otras funciones**, creamos **closures** que "capturan" variables del entorno externo:

```javascript
   fun crearSaludo(nombre){
      fun saludar(){
         print "Hola, " + nombre + "!";
      }
      return saludar;
   }

   var fn = crearSaludo("Estudiante");
   fn(); // "Hola, Estudiante!"
```

### Clases en Brea

**Brea** es **orientado a objetos**, con clases simples y comprensibles:

```javascript
   class Desayuno {
      init(comida){
         this.comida = comida;
      }

      servir(quien){
         print "Disfruta tu " + this.comida + ", " + quien;
      }
   }

   var desayuno = Desayuno("tostadas");
   desayuno.servir("amigo"); // "Disfruta tu tostadas, amigo"
```

**init** es el constructor que inicializa la instancia.
**this** hace referencia al objeto actual.

Las **clases** son valores de **primera clase**, igual que las funciones.

<br/>

### Herencia en Brea: usando <

En **Brea**, las clases pueden **heredar** de otras clases usando el **símbolo <**. Esto significa que una subclase toma todos los métodos y propiedades de su superclase, y además puede agregar o modificar su propio comportamiento.

Ejemplo básico:

```javascript
   class Comida {
      init(nombre){
         this.nombre = nombre;
      }

      servir(){
         print "Disfruta tu " + this.nombre;
      }
   }

   class Almuerzo < Comida{
      init(nombre, bebida){
         // Llamamos al constructor de la superclase
         super.init(nombre);
         this.bebida = bebida;
      }

      servir(){
         // Podemos extender el método de la superclase
         super.servir();
         print "con " + this.bebida;
      }
   }

   var miAlmuerzo = Almuerzo("sopa", "agua");
   miAlmuerzo.servir(); // "Disfruta tu sopa con agua"
```

Explicación paso a paso

- **< indica herencia**: class Almuerzo < Comida significa que Almuerzo hereda de Comida. Todo lo que Comida puede hacer, Almuerzo también puede hacerlo, a menos que lo sobrescriba.

- **Llamada a super.init()**: Cuando sobrescribimos el constructor (init) de la subclase, usamos super.init(...) para invocar el constructor de la superclase y asegurarnos de inicializar correctamente las propiedades heredadas.

- **Sobrescribir métodos**: En la subclase podemos redefinir métodos. Si queremos mantener el comportamiento de la superclase y añadir algo extra, usamos super.metodo() dentro de nuestro método sobrescrito.

- **Agregar nuevas propiedades o métodos**: La subclase puede añadir propiedades nuevas (como bebida) o métodos nuevos, que no existen en la superclase.

```javascript
class Almuerzo < Comida{
  init(nombre, bebida){
    super.init(nombre);
    this.bebida = bebida;
  }

  acompañamiento(){
    print "Hoy tienes pan con tu " + this.nombre;
  }
}
```

Piensa en **Brea** como un juego de LEGO:

- La superclase es una base: ya tiene algunas piezas.
- La subclase toma esa base y puede añadir nuevas piezas o modificar las que ya vienen.
- **<** es el símbolo que dice: "quiero usar esta base y ampliarla". 🧱

<br/><hr/><br/>

## 10. [💡 Lo que aprenderás creando un lenguaje](#-índice-del-capítulo)

Implementar un lenguaje te obliga a:

- Comprender en profundidad las estructuras de datos que normalmente usamos sin pensar.
- Entender cómo los algoritmos interactúan con la memoria y los datos.
- Diseñar un sistema complejo de manera modular y comprensible.

A medida que avancemos, notaremos que el desafío no está solo en escribir código, sino en tomar decisiones de diseño consciente, equilibrando claridad, eficiencia y escalabilidad.

Comenzaremos creando **jBrea** en Java, enfocándonos en claridad y comprensión.

Después construiremos **cBrea** en C, para aprender sobre eficiencia y control a bajo nivel.

Cada sección incluirá teoría, ejemplos y ejercicios prácticos, permitiéndote aprender haciendo.

<br/><hr/><br/>

## 11. [✏️ Ejercicios propuestos](#-índice-del-capítulo)

- [**Ejercicio Propuesto 1**](../ejercicios/tema-01/01-ejercicios.md)

> 💬 Define qué es un lenguaje específico de dominio (DSL - Domain Specific Language) y menciona al menos cinco ejemplos.

- [**Ejercicio Propuesto 2 (Dasafio)**](../ejercicios/tema-01/02-ejercicios.md)

> 💬 Para practicar con punteros, define una lista doblemente enlazada de cadenas en el heap. Escribe funciones para insertar, buscar y eliminar elementos de la lista.

<br/><hr/><br/>

| [↩️ Volver al inicio del Proyecto](../README.md) | [⬆️ Ir al inicio del Capítulo](#capítulo-1-introducción-al-proyecto-brea-) | [➡️ Capítulo 2](../docs/02-PiezasDeUnLenguaje.md) |
| :----------------------------------------------: | :------------------------------------------------------------------------: | :-----------------------------------------------: |
