# Bienvenido al proyecto Interprete-Brea 🧩

<p align="center">
  <img src="recursos/banner.png" alt="Tutorial ABAP Cloud" width="1280"/>
</p>

Este proyecto nace de mi **curiosidad y motivación por entender profundamente cómo funciona un lenguaje de programación**, y de la convicción de que **la mejor manera de aprender es enseñando**.

Aquí no solo seguirás un tutorial, sino que **exploraremos juntos los fundamentos, paso a paso**, construyendo un **intérprete en Java** y un lenguaje propio, llamado **Brea** (aunque puedes llamarlo como quieras), mientras explico cada decisión y concepto desde mi perspectiva de aprendizaje.

> Este curso está **inspirado en el libro _Crafting Interpreters_ de Robert Nystrom**, así como en distintos **recursos que iremos investigando en Internet**, adaptando los conceptos a mi propio aprendizaje.

---

## Índice de capítulos 📖

### 📘 [1. Introducción del proyecto Brea](docs/01-Bienvenido.md)

```text
        - [🧩 Introducción]
        - [🤔 Por qué aprender a construir un intérprete]
        - [☕ Nuestro primer intérprete: jBrea en Java]
        - [⚙️ Segunda fase: cBrea en C]
        - [🧪 El aprendizaje práctico]
        - [🔑 Conceptos clave a dominar]
        - [💡 Por qué es un gran ejercicio]
        - [🧭 Resumen del capítulo]
        - [✏️ Ejercicios propuestos]
```

### 📘 [2. Las Piezas que componen un lenguaje](docs/02-PiezasDeUnLenguaje.md)

```text
        - [✍️ Dibujando el lenguaje en un papel]
        - [🔍 Escaneo (Scanning o Lexing)]
        - [👇 Qué es el escáner léxico (o lexer)]
        - [🧩 Qué es un token]
        - [🔧 De texto a tokens: primer paso del compilador]
        - [🌲 Análisis Sintáctico (Parsing)]
        - [💬 Análisis Semántico: Entendiendo el Significado del Código]
        - [🛠️ Representaciones Intermedias (Intermediate Representations – IR)]
        - [⚡ Optimización (Optimization)]
        - [💻 Generación de Código (Code Generation)]
        - [🖥️ Máquina Virtual (Virtual Machine – VM)]
        - [⏱️ Tiempo de Ejecución (Runtime)]
        - [🛣️ Atajos y rutas alternativas]
        - [🌳 Intérpretes de recorrido de árbol (Tree-walk interpreters)]
        - [🔄 Transpilador (Transpiler)]
        - [✨ Compilación Just-in-Time (JIT)]
        - [📚 Compiladores e Intérpretes (Compilers and Interpreters)]
        - [📝 Ejercicio Propuesto]
```

### 📘 [3. El inicio del Interprete (Scanning) ](docs/03-ElInicioDelInterprete.md)

```text
        -[ 🛠️ ... (desarrollando) ]
```

<br/><hr/><br/>

## ¿Qué aprenderemos? 💻

El objetivo de este proyecto es que **comprendas cómo funciona un lenguaje desde cero**, incluyendo:

- Qué es un **lenguaje de programación** y cómo procesa el código internamente.
- Qué es un **intérprete** y en qué se diferencia de un compilador.
- Conceptos clave como **tipado, variables, alcance, funciones, closures, clases, objetos y manejo de memoria**.
- Cómo se transforma el código fuente en **acciones ejecutables por la máquina**.

> Todo esto será explicado con ejemplos claros y ejercicios prácticos, mostrando no solo _qué hacer_, sino _por qué funciona así_.

<br/><hr/><br/>

## Enseñar para aprender 🎓

Una de las mejores maneras de **afianzar conocimientos** es explicarlos a otros. Por eso este proyecto está estructurado **como un tutorial personal**, donde comparto:

- Mis pasos de aprendizaje y descubrimientos.
- Errores comunes y cómo solucionarlos.
- Explicaciones desde mi punto de vista, facilitando que alguien más pueda **aprender siguiendo mi camino**.

De esta manera, no solo construimos un intérprete funcional, sino que **creamos un recurso educativo** que refleja el aprendizaje práctico de la programación de lenguajes.

<br/><hr/><br/>

## Estructura inicial de carpetas 📂

```text
brea-interpreter/
├── README.md                  ← Este archivo
├── docs/
│   ├── 01-bienvenido.md       ← Capítulo por capitulos en docs
│   └── ...
├── src/                       ← Código
├── ejercicios/                ← Ejercicios y mini-proyectos resueltos por tema
└── recursos/                  ← recursos del tutorial (imagenes, pdf, ...)
```

<br/><hr/><br/>

## Recursos y referencias 📚

- Libro _Crafting Interpreters_ de Robert Nystrom – guía principal para el diseño de intérpretes.
- Artículos y tutoriales en línea sobre Java, compiladores y diseño de lenguajes.
- Documentación oficial de Java y herramientas relacionadas.
- Recursos visuales y diagramas para entender la teoría de intérpretes.

<br/><hr/><br/>

## Próximo paso: Capítulo 2 (desarrollando) ✨

En el Capítulo 2 exploraremos el fascinante viaje que realizan todos los lenguajes de programación —desde su código base hasta llegar al intérprete que les da vida.

Analizaremos cada una de las posibles rutas que puede tomar un lenguaje en su fase de creación, comprendiendo cómo las decisiones de diseño, compilación e interpretación moldean su identidad y comportamiento.

<br/><hr/><br/>

> Este es solo el comienzo. Cada capítulo siguiente incorporará **teoría y práctica**, y poco a poco construiremos un lenguaje completo y funcional, Brea.
