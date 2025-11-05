# Capítulo 1: Introducción al proyecto Brea 🧩

| [↩️ Volver al inicio del Proyecto](../README.md) |
| :----------------------------------------------: |

---

Bienvenido al mundo de Brea. Este capítulo es la **puerta de entrada para comprender cómo funciona un lenguaje de programación desde cero** y cómo se construye un intérprete funcional en Java. Nuestro enfoque es **aprender haciendo**, entendiendo la teoría mientras desarrollamos código real.

---

# 📚 Índice del Capítulo

| Sección                                                                                       | Descripción                                                     |
| :-------------------------------------------------------------------------------------------- | :-------------------------------------------------------------- |
| [🧩 Introducción](#-introducción)                                                             | Qué aprenderás en esta primera etapa y cuál es el objetivo.     |
| [🤔 Por qué aprender a construir un intérprete](#-por-qué-aprender-a-construir-un-intérprete) | Razones para crear tu propio lenguaje e intérprete.             |
| [☕ Nuestro primer intérprete: jBrea en Java](#-nuestro-primer-intérprete-jbrea-en-java)      | Primera versión del intérprete escrita en Java.                 |
| [⚙️ Segunda fase: cBrea en C](#-segunda-fase-cbrea-en-c)                                      | Versión en C para comprender la ejecución a bajo nivel.         |
| [🧪 El aprendizaje práctico](#-el-aprendizaje-práctico)                                       | Cómo combinaremos teoría, práctica y desafíos.                  |
| [🔑 Conceptos clave a dominar](#-conceptos-clave-a-dominar)                                   | Diferencias entre intérprete y compilador, y conceptos básicos. |
| [💡 Por qué es un gran ejercicio](#-por-qué-es-un-gran-ejercicio)                             | Qué habilidades ganarás al implementar un lenguaje.             |
| [🧭 Resumen del capítulo](#resumen-del-capítulo)                                              | Puntos más importantes que cubrimos.                            |
| [✏️Ejercicios propuestos](#ejercicios-propuestos)                                             | Enlaces a los ejercicios prácticos del capítulo.                |

---

## 🧩 Introducción

En esta primera etapa vamos a:

- Conocer los **conceptos fundamentales de los lenguajes de programación**.
- Comprender la arquitectura básica de un intérprete.
- Prepararnos para implementar Brea, un lenguaje sencillo pero completo.

El objetivo es que al final es que tengamos **una visión clara de cómo un lenguaje vive y respira**, y que estés listo para empezar a programar tu propio intérprete.

---

## 🤔 Por qué aprender a construir un intérprete

Crear un lenguaje puede parecer intimidante, pero pienso que es un **ejercicio extremadamente valioso** para cualquier programador, te enumero algunos motivos:

1. **Profundiza tu comprensión de estructuras de datos**: árboles sintácticos, grafos y tablas hash se vuelven conceptos que realmente entiendes al implementarlos.
2. **Refuerza tus habilidades en algoritmos**: análisis léxico, análisis sintáctico, recursión y manejo de memoria son fundamentales.
3. **Mejora tu diseño de software**: al organizar el código en clases, métodos y módulos claros, aprendes buenas prácticas de arquitectura.
   (...)

Incluso si no planeas crear un lenguaje de propósito general, los **lenguajes de dominio específico** están en todas partes: scripts de automatización, motores de plantillas, formatos de configuración y archivos de datos. Comprender cómo funcionan te permitirá **adaptarte y crear soluciones personalizadas cuando sea necesario**.

---

## ☕ Nuestro primer intérprete: jBrea en Java

Para empezar, construiremos **jBrea**, un intérprete simple en Java. La elección de Java tiene varias ventajas:

- Es **tipado y explícito**, lo que permite ver claramente la estructura de los datos que usamos.
- Es lo suficientemente **alto nivel** como para concentrarnos en la lógica sin perdernos en detalles de bajo nivel.
- Permite **programación orientada a objetos**, organizando el código en clases y métodos, lo que facilita la modularidad y reutilización.

Nuestro objetivo inicial será un intérprete **correcto y comprensible**, dejando la optimización de rendimiento para etapas posteriores. Nos enfocaremos en:

1. **Lexing (análisis léxico)**: convertir el código fuente en una serie de tokens.
2. **Parsing (análisis sintáctico)**: transformar los tokens en una estructura que represente la lógica del programa.
3. **Evaluación y runtime**: ejecutar instrucciones según la semántica de Brea.

Este enfoque nos permitirá **ver claramente cómo cada parte del intérprete interactúa con las demás**, y cómo las decisiones de diseño afectan el comportamiento del lenguaje.

---

## ⚙️ Segunda fase cBrea en C

Más adelante construiremos **cBrea**, la versión en C, con el objetivo de:

- Entender **cómo se gestionan los datos a nivel de memoria y CPU**.
- Implementar estructuras dinámicas y tablas hash desde cero.
- Construir un **recolector de basura** y un compilador de bytecode eficiente.

Mientras jBrea nos enseña la lógica y la claridad conceptual, cBrea nos permitirá **profundizar en eficiencia y control de ejecución**, mostrando cómo las máquinas realmente interpretan nuestro lenguaje.

---

## 🧪 El aprendizaje práctico

La mejor manera de entender un lenguaje es **interactuar con él**:

- Cada sección de mi tutorial combinará **teoría con práctica**.
- Incluiré **ejemplos claros y fragmentos de código** para que puedas ejecutar y experimentar.
- Pondré **desafíos opcionales**, donde aplicaremos lo aprendido y exploraremos soluciones por nuestra cuenta.

Esta metodología asegura que **la comprensión no sea solo teórica**, sino basada en experiencias prácticas que nos preparan para proyectos más complejos.

---

## 🔑 Conceptos clave a dominar

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

---

## 💡 Por qué es un gran ejercicio

Implementar un lenguaje te obliga a:

- Comprender **en profundidad las estructuras de datos** que normalmente usamos sin pensar.
- Entender cómo **los algoritmos interactúan con la memoria y los datos**.
- Diseñar un sistema complejo de manera modular y comprensible.

A medida que avancemos, notaremos que el desafío **no está solo en escribir código**, sino en **tomar decisiones de diseño consciente**, equilibrando claridad, eficiencia y escalabilidad.

---

## 🧭 Resumen del capítulo

- Comenzamos con **jBrea en Java**, centrándonos en claridad y comprensión.
- Después construiremos **cBrea en C**, para aprender sobre eficiencia y control a nivel bajo.
- Cada sección incluiré teoría, ejemplos y ejercicios prácticos, permitiéndote **aprender haciendo**.

---

## ✏️Ejercicios propuestos

- [**Ejercicio Propuesto 1**](../ejercicios/tema-01/01-ejercicios.md)

> 💬 Define qué es un lenguaje específico de dominio (DSL - Domain Specific Language) y menciona al menos cinco ejemplos.

- [**Ejercicio Propuesto 2 (Dasafio)**](../ejercicios/tema-01/02-ejercicios.md)

> 💬 Para practicar con punteros, define una lista doblemente enlazada de cadenas en el heap. Escribe funciones para insertar, buscar y eliminar elementos de la lista.

---

> ¡Felicidades! 🎉 Has completado tu primer vistazo a Brea.  
> Antes de escribir código, exploraremos un **mapa del lenguaje** que todo lenguaje de programación debe recorrer: va desde el **código fuente**, pasando por **símbolos (tokens)**, el **árbol sintáctico (syntax tree)**, ... hasta llegar a nuestro **código de máquina o bytecode**.  
> 🌟 No entraremos en detalle todavía, eso lo exploraremos paso a paso en la siguiente sección.

---

| [↩️ Volver al inicio del Proyecto](../README.md) |
| :----------------------------------------------: |
