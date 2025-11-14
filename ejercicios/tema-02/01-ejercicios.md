# Ejercio Propuesto 1: Explorando Scanners y Parsers

| [↩️ Volver al inicio del Proyecto](../../README.md) | [↩️ Volver al Capítulo 2](../../docs/02-PiezasDeUnLenguaje.md) |
| :-------------------------------------------------: | :------------------------------------------------------------: |

<br/><hr/><br/>

- **Objetivo**: Familiarizarse con la implementación real de compiladores e intérpretes explorando código open source.

<br/><hr/><br/>

## Instrucciones:

Elige un lenguaje open source de tu preferencia. Por ejemplo, puedes usar uno de estos repositorios en GitHub:

- [CPython (Python) – El intérprete oficial de Python en C](https://github.com/python/cpython)
- [PyPy (Python JIT) – Implementación alternativa de Python con JIT](https://github.com/friendlyanon/pypy)
- [MRI (Ruby) – Implementación oficial de Ruby (Matz’s Ruby Interpreter)](https://github.com/ruby/ruby)
- [JRuby – Ruby sobre JVM](https://github.com/jruby/jruby)
- [Lua – Lenguaje ligero, famoso por embebirse en juegos](https://github.com/lua/lua) - [GHC (Glasgow Haskell Compiler) – Compilador de Haskell](https://github.com/ghc/ghc)
- [Go (golang) – Lenguaje de Google, compilador y runtime incluidos](https://github.com/golang/go)
- [V (Vlang) – Lenguaje moderno, compilador muy sencillo de explorar](https://github.com/vlang/v)
- [Crystal – Lenguaje tipo Ruby, compilado a código nativo](https://github.com/crystal-lang/crystal)
- [Nim – Lenguaje moderno, compilado a C, C++ o JavaScript](https://github.com/nim-lang/Nim)

---

**Clona o descarga el repositorio en tu máquina**: Clonando con Git
git clone https://github.com/python/cpython.git
O bien, descargando el ZIP desde la página de GitHub y descomprimiéndolo

### Respuesta:

- En mi caso vamos a explorar el repositorio de **CPython** .

<br/><hr/><br/>

## Explora la estructura de carpetas del repositorio.

Busca carpetas o archivos relacionados con:

- parser
- lexer
- scanner
- tokenizer
- Grammar.
  Ahí suele estar la magia que convierte el código fuente en tokens y AST.

---

### Respuesta:

El objetivo de este apartado es que explores el codigo, no que lo entiendas. Intentes conectar los diferentes tipos de archivos que puedes encontrate con los conceptos del capitulo 2 de nuestro tutorial.

Entonces: explorando la estructura del repositorio en CPython, los componentes que manejan el escaneo y parsing del código se encuentran principalmente en estas carpetas:

- La carpeta `Python/` contiene el código fuente principal del intérprete. Aquí se implementan muchas partes del lenguaje, incluyendo el lexer, que se encarga de dividir el código en tokens.

Se observamos con detalle la carpeta podemos destacar lo siguiente:

### Archivos de interés dentro de `Python/`

#### 1. Lexer / Tokenizer

| Archivo                                                               | Descripción                                                                                                                |
| --------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------- |
| [Python-tokenize.c](../../src/tema-02/01-ejercicio/Python-tokenize.c) | Implementa el **tokenizer** de Python, que convierte el texto en tokens antes de ser procesado por el parser.              |
| [\_warnings.c](../../src/tema-02/01-ejercicio/_warnings.c)            | No es directamente lexer/parser, pero interactúa con la ejecución y análisis del código.                                   |
| [\_contextvars.c](../../src/tema-02/01-ejercicio/_contextvars.c)      | Similar a `_warnings.c`, afecta la ejecución y el análisis del código, no implementa directamente el lexer o parser.       |
| [future.c](../../src/tema-02/01-ejercicio/future.c)                   | Gestión de declaraciones `__future__`; influye en cómo se interpreta el código, pero no es parte directa del lexer/parser. |

#### 2. AST (Abstract Syntax Tree)

| Archivo                                                             | Descripción                                                                       |
| ------------------------------------------------------------------- | --------------------------------------------------------------------------------- |
| [ast.c](../../src/tema-02/01-ejercicio/ast.c)                       | Implementación de las operaciones sobre nodos del AST.                            |
| [ast_preprocess.c](../../src/tema-02/01-ejercicio/ast_preprocess.c) | Preprocesamiento de nodos del AST antes de otras fases del compilador/intérprete. |
| [ast_unparse.c](../../src/tema-02/01-ejercicio/ast_unparse.c)       | Convierte el AST de nuevo a código fuente (útil para depuración o análisis).      |
| [Python-ast.c](../../src/tema-02/01-ejercicio/Python-ast.c)         | Definición de estructuras de datos del AST.                                       |

#### 3. Grammar / Parsing auxiliar

| Archivo                                               | Descripción                                                                             |
| ----------------------------------------------------- | --------------------------------------------------------------------------------------- |
| [asdl.c](../../src/tema-02/01-ejercicio/asdl.c)       | Manejo de estructuras de datos usadas en el AST (Abstract Syntax Description Language). |
| [compile.c](../../src/tema-02/01-ejercicio/compile.c) | Convierte el AST en código ejecutable o bytecode; interactúa con parsing y AST.         |

Además de la carpeta Python/ , podemos destacar en el github de CPython estas carpetas:

> La carpeta **Grammar/** ( [tokens](../../src/tema-02/01-ejercicio/Tokens.sql) , [python.gram](../../src/tema-02/01-ejercicio/python.gram))

    Contiene la gramática de Python en formato PEG. → Aquí vive la definición de la sintaxis del lenguaje.

> La carpeta [Parser/](../../src/tema-02/01-ejercicio/Parser/)

    Contiene el código del parser moderno (PEG parser). → Aquí empieza el camino hacia el AST.

> La carpeta [Include/](../../src/tema-02/01-ejercicio/Include/)

    Headers en C con las definiciones de estructuras internas: nodos del AST, tokens, objetos internos del runtime

<br/><hr/><br/>

## Investiga cómo se implementan:

¿Qué significan Lex y Yacc?

En el lenguaje que estás investigando, ¿existen archivos con extensión .l o .y? Eso te indicará si usan Lex/Yacc para generar el scanner y parser.

---

### Respuesta:

**Lex** → Herramienta para generar scanners/lexers. Toma una definición de expresiones regulares y genera un programa que convierte texto en tokens.

**Yacc** → Herramienta para generar parsers. Toma reglas de gramática (formato BNF) y genera un parser que construye el AST.

> **Nota:** CPython moderno ya no usa Lex/Yacc. En versiones antiguas sí se usaba Yacc, pero hoy se utiliza **PEG parser**, que está en `Parser/pegen/`.

<br/><hr/><br/>

- **Responde las siguientes preguntas:** (desarrollando ...)
  - ¿Cómo organiza el lenguaje el escaneo y parsing del código fuente?
  - ¿Qué tipo de archivos usa para definir la gramática o las reglas del lexer?
  - ¿Puedes identificar la función que recibe el texto y devuelve los tokens?
  - ¿Puedes identificar la función que construye el AST?

<br/><hr/><br/>

| [↩️ Volver al inicio del Proyecto](../../README.md) | [↩️ Volver al Capítulo 2](../../docs/02-PiezasDeUnLenguaje.md) |
| :-------------------------------------------------: | :------------------------------------------------------------: |
