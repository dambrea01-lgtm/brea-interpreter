/*
    Problema:
        - Define una lista doblemente enlazada de strings en el heap, 
          con funciones de inserción, búsqueda y eliminación.
*/


#include <stdio.h> //para printf, scanf y manejo de entrada/salida
#include <stdlib.h> //para malloc, free y manejo de memoria dinámica
#include <string.h> //para stdrup y strcmp, manejo de cadena

/*

    Un nodo es una unidad básica que contiene información y referencias a otros nodos.
    Cada nodo tiene 3 cosas principales:
    - Datos (data): lo que quieres almacenar, por ejemplo un texto "Hola" 📝.
    - Puntero al nodo anterior (prev): indica quién está justo antes en la lista ⬅️.
    - Puntero al nodo siguiente (next): indica quién está justo después en la lista ➡️

*/

typedef struct Node{

    char *data; //el dato que guardamos, en este caso un string
    struct Node *prev; //puntero al nodo anterior
    struct Node *next; //puntero al nodo siguiente

} Node;

/*
    data → almacena el valor del nodo, por ejemplo "Hola".
    prev → permite ir hacia el nodo anterior ⬅️.
    next → permite ir hacia el siguiente nodo ➡️

    💡 Piensa en los nodos como vagones de un tren, donde cada vagón sabe 
       quién está delante y detrás.
*/

// ##########  Crear un nodo  ################

/*
    Hacemos una función que reserva memoria en el heap y prepara un nodo vacío

    Explico conceptos IMPORTANTES que debemos de empezar a entender.
    ¿qué es un Heap? 

    1️⃣ Memoria en C
       Cuando programas en C, tu programa usa dos áreas principales de memoria:

        -Stack (pila) 🗂️
          * Es una memoria temporal para variables locales y llamadas a funciones.
          * Se gestiona automáticamente: cuando una función termina, su memoria desaparece.
          * Tienen un tamaño limitado, rápido de acceder.

        -Heap (montículo) 🏗️
          * Es una memoria dinámica, que tú controlas.
          * Necesaria cuando no sabes de antemano cuánta memoria necesitarás.
          * Se reserva usando malloc, calloc o realloc.
          * Debes liberarla manualmente con free para evitar fugas de memoria.

    2️⃣ ¿Por qué usamos heap en el ejercicio?
        En la lista doblemente enlazada:
        Cada nodo se crea dinámicamente con:

            Node *node = malloc(sizeof(Node));
            node->data = strdup(str);

        malloc → reserva memoria para el nodo en el heap.
        strdup → reserva memoria para la copia del string en el heap.

    💡 Esto permite que la lista pueda crecer mientras el programa se ejecuta, 
       sin depender de variables locales que desaparecerían al salir de la función.


    3️⃣ Entonces para afianzar conceptos: Diferencias clave entre stack y heap
       Característica	        Stack 🗂️	            Heap 🏗️
        -Gestión	            Automática	            Manual (malloc/free)
        -Vida de la variable	Temporal (función)	    Hasta que se libera
        -Tamaño	                Limitado	            Grande, flexible
        -Velocidad de acceso	Muy rápido	            Más lento
        -Uso típico	            Variables locales	    Listas, árboles, nodos, buffers dinámicos

*/

Node* createNode(const char *str){

    Node *node = malloc(sizeof(Node)); // Reserva memoria para el nodo
    node->data = strdup(str);   // Copiar el string a memoria nueva
    node->prev = NULL;  // Inicialmente no hay anterior
    node->next = NULL;  // Inicialmente no hay posterior 
    return node;
}

// ##########   Insertar un Nodo     ################

void insert(Node **head, const char *str){

    Node *node = createNode(str);
    node->next = *head; // Apunta al antiguo primer nodo
    if(*head) (*head)->prev = node; // El antiguo nodo ahora apunta hacia atrás
    *head = node; // Actualiza el head de la lista
}

/*

    Explico esta función que hemos creado ahora para insertar un Nodo:

    1️⃣ La firma de la función
        
        void insert(Node **head, const char *str)

        - Node **head -> puntero al puntero del primer nodo.
            En C, los punteros permiten modificar el valor de otra variable fuera de la función.
            Aquí queremos cambiar el head de la lista cuando agregamos un nuevo nodo al inicio.
            Si pasáramos solo Node *head, estaríamos modificando una copia local, y el head 
            original no cambiaría fuera de la función.

        - const char *str -> el string que queremos guardar en el nuevo nodo.

    2️⃣ Crear un nodo nuevo
    
        Node *node = createNode(str);

        Llama a la función createNode, que hemos creado anteriormente para:
            -Reserva memoria en el heap.
            -Copia el string str al nodo.
            -Inicializa prev y next en NULL.
        Ahora tenemos un nodo independiente, listo para insertarlo en la lista.

    3️⃣ Conectar el nuevo nodo al antiguo head
        
        node->next = *head;

        *head → el puntero actual al primer nodo de la lista.
        node->next = *head -> hace que nuestro nuevo nodo apunte al antiguo primer nodo.

        Ejemplo visual:

        Antes:
            head -> [A | prev=NULL, next=NULL]
        Después de node->next = *head:
            node -> [B | prev=NULL, next=A]
            head -> [A | prev=NULL, next=NULL]  // todavía head apunta al viejo nodo

    4️⃣ Ajustar el puntero prev del antiguo primer nodo
    
        if (*head) (*head)->prev = node;

        Si la lista no estaba vacía, el antiguo primer nodo (*head) ahora apunta hacia 
        atrás al nuevo nodo.

        Continuando el ejemplo visual:

        Nuevo estado:
            node -> [B | prev=NULL, next=A]
            A    -> [A | prev=B, next=NULL]

    5️⃣ Actualizar el head de la lista

        *head = node;

        Ahora el head de la lista apunta al nuevo nodo.

        Visualmente:

            head -> [B | prev=NULL, next=A] -> [A | prev=B, next=NULL]
        
    Con esto, siempre que llames insert, el nodo se agrega al inicio de la lista.

    ✅ Resumen
        -Creamos un nodo nuevo en el heap.
        -Hacemos que node->next apunte al antiguo primer nodo.
        -Ajustamos prev del antiguo primer nodo para que apunte hacia atrás.
        -Actualizamos el head de la lista para que apunte al nuevo nodo.

    💡 Idea clave: Node **head nos permite modificar el puntero del head real, 
                   no solo una copia local dentro de la función.

*/



// #####################   Buscar Node    ##########################


Node* find(Node *head, const char *str){
    Node *curr = head;
    while(curr){
        if(strcmp(curr->data, str)==0) return curr; // encontrado
        curr = curr->next;                          // pasar al siguiente
    }
    return NULL; // no encontrado
}

/*
    Esta función recorre la lista desde el head hasta el final. 
    strcmp compara strings. Devuelve 0 si son iguales.

    Analicemos la función: 
    1️ La firma de la función:  
    
        void insert(Node **head, const char *str)
    
        Node **head -> puntero al puntero del primer nodo.
        - En C, los punteros permiten modificar el valor de otra variable fuera de la función.
        - Aquí queremos cambiar el head de la lista cuando agregamos un nuevo nodo al inicio.
        - Si pasáramos solo Node *head, estaríamos modificando una copia local, y el head 
          original no cambiaría fuera de la función.

        const char *str -> el string que queremos guardar en el nuevo nodo.

    2️⃣ Crear un nodo nuevo
    
        Node *node = createNode(str);

        Llama a la función createNode, que creamos antes, recuerde:
            - Reserva memoria en el heap.
            - Copia el string str al nodo.
            - Inicializa prev y next en NULL.

        Ahora tenemos un nodo independiente, listo para insertarlo en la lista.

    3️⃣ Conectar el nuevo nodo al antiguo head

        node->next = *head;

        *head -> el puntero actual al primer nodo de la lista.
        node->next = *head , hace que nuestro nuevo nodo apunte al antiguo primer nodo.
    
        Ejemplo visual:
            Antes: 
                head -> [A | prev=NULL, next=NULL]
            
            Después de node->next = *head:
                node -> [B | prev=NULL, next=A]
                head -> [A | prev=NULL, next=NULL]  // todavía head apunta al viejo nodo

    4️⃣ Ajustar el puntero prev del antiguo primer nodo
        
        if (*head) (*head)->prev = node;
    
        Si la lista no estaba vacía, el antiguo primer nodo (*head) ahora apunta hacia atrás 
        al nuevo nodo.
        Continuando con el ejemplo visual:
        Nuevo estado:
            node -> [B | prev=NULL, next=A]
            A    -> [A | prev=B, next=NULL]

    5️⃣ Actualizar el head de la lista

        *head = node;
    
        Ahora el head de la lista apunta al nuevo nodo.
        Visualmente:
            head -> [B | prev=NULL, next=A] -> [A | prev=B, next=NULL]
        Con esto, siempre que llames insert, el nodo se agrega al inicio de la lista.

    ✅ Resumen
        1. Creamos un nodo nuevo en el heap.
        2. Hacemos que node->next apunte al antiguo primer nodo.
        3. Ajustamos prev del antiguo primer nodo para que apunte hacia atrás.
        4. Actualizamos el head de la lista para que apunte al nuevo nodo.

    💡 Idea clave: Node **head nos permite modificar el puntero del head real, 
                   no solo una copia local dentro de la función.

*/


// ##################  eliminar un nodo  ###################

void delete(Node **head, const char *str){
    Node *node = find(*head, str);
    if (!node) return; // si no existe, no hace nada

    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    if (*head == node) *head = node->next; // si eliminamos el head

    free(node->data); // liberar string
    free(node);       // liberar nodo
}


/*
    Importante la función tiene que ajustar los punteros vecinos para mantener la lista conectada.
    Libera la memoria para evitar fugas (memory leaks).

    Explico paso a paso para que se entienda bien:

    1️⃣ La firma de la función
        
        void delete(Node **head, const char *str)
    
        Node **head -> puntero al puntero del primer nodo (necesario si eliminamos el primer nodo y 
                       necesitamos actualizar el head).
        const char *str -> el string del nodo que queremos eliminar.

        💡 Igual que en insert, usamos Node **head porque podemos modificar el head original de la 
           lista desde la función.

    2️⃣ Buscar el nodo a eliminar

        Node *node = find(*head, str);

        if (!node) return; // si no existe, no hace nada
        
        Llamamos a la función find para localizar el nodo que contiene el string.
        Si no se encuentra (NULL), terminamos la función y no hacemos nada.

    3️⃣ Ajustar los punteros de los vecinos, para mantener la lista conectada 
        
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
    
        Explicación:
        1- node->prev , el nodo anterior del nodo que vamos a eliminar.
            - Si existe, cambiamos su next para que apunte al nodo siguiente.

        2- node->next , el nodo siguiente del nodo que vamos a eliminar.
            - Si existe, cambiamos su prev para que apunte al nodo anterior.
    
        Esto mantiene la lista conectada, “saltando” el nodo eliminado.

    4️⃣ Actualizar el head si es necesario
    
        if (*head == node) *head = node->next; // si eliminamos el head
    
        Si el nodo que eliminamos es el primer nodo, actualizamos el head para que apunte 
        al siguiente nodo.

    5️⃣ Liberar memoria
    
        free(node->data); // liberar string
        free(node);       // liberar nodo

        free(node->data) , liberamos la memoria del string que se había creado con strdup.
        free(node) , liberamos la memoria del nodo mismo (malloc al crear).

    💡 Esto es fundamental en C para evitar fugas de memoria (memory leaks).

    6️⃣ Ejemplo visual con 3 nodos
        
        Lista inicial:
            head -> [A] <-> [B] <-> [C] -> NULL
        
        Queremos eliminar "B":
            
            1. Encontramos nodo B (node = [B]).
            2. Ajustamos punteros de vecinos:
                - A->next = C
                - C->prev = A
            3. Liberamos la memoria de B (data y node).
        
        Lista final:
            head -> [A] <-> [C] -> NULL
        
        ✅ Lista conectada y sin fugas de memoria.

*/


// ######################## Ejemplo de uso #######################

int main() {
    
    Node *frutas = NULL; // creamos una lista vacia de nodos

    // ###### Insertamos tres frutas 🍎🍌🍇 ######
    insert(&frutas, "Manzana");
    insert(&frutas, "Banana");
    insert(&frutas, "Uva");

    /*
        Estado inicial
            
            Node *frutas = NULL;

            La lista está vacía:

            frutas -> NULL

        🍎 1️⃣ Insertamos "Manzana"
        
            insert(&frutas, "Manzana");

            Creamos un nodo con "Manzana" y como la lista está vacía, ese nodo 
            se convierte en el primero.

            frutas -> [ "Manzana" | prev=NULL | next=NULL ]

            Visualmente:

                NULL ← [ "Manzana" ] → NULL

        🍌 2️⃣ Insertamos "Banana"
        
            insert(&frutas, "Banana");

            La función insert() coloca "Banana" al inicio.
            Por lo tanto:

                "Banana".next → "Manzana"
                "Manzana".prev → "Banana"

                frutas ─> [ "Banana" ] ⇄ [ "Manzana" ]

            Visualmente:

                NULL ← [ "Banana" ] ⇄ [ "Manzana" ] → NULL

        🍇 3️⃣ Insertamos "Uva"
        
            insert(&frutas, "Uva");

            De nuevo, se inserta al inicio, así que:

                "Uva".next → "Banana"
                "Banana".prev → "Uva"

                frutas ─> [ "Uva" ] ⇄ [ "Banana" ] ⇄ [ "Manzana" ]

            Visualmente:

                NULL ← [ "Uva" ] ⇄ [ "Banana" ] ⇄ [ "Manzana" ] → NULL
    
    */



    printf("\n--- Lista inicial ---\n");
    printList(frutas);

    // ####### Buscar una fruta ########
    Node *f = find(frutas, "Banana");
    if (f)
        printf("✅ Fruta encontrada: %s\n", f->data);
    else
        printf("❌ Fruta no encontrada\n");

    /*
    
        Partimos de la lista después de insertar las tres frutas:

        NULL ← [ "Uva" ] ⇄ [ "Banana" ] ⇄ [ "Manzana" ] → NULL
                  ↑
                frutas (head)

        🕵️ Buscar "Banana"
        
            Node *f = find(frutas, "Banana");

            La función find() recorre la lista desde el inicio (head) hasta el final, 
            comparando cada nodo con el string buscado:

            Paso	Nodo actual	¿Coincide con "Banana"?
                1	"Uva"	    ❌ No
                2	"Banana"	✅ Sí

            Cuando llega al nodo "Banana", lo encuentra y devuelve el puntero f a ese nodo.

            📍 Estado en memoria:
            NULL ← [ "Uva" ] ⇄ [ "Banana" ] ⇄ [ "Manzana" ] → NULL
                        ↑           ↑
                    frutas       f (nodo encontrado)


            Y la consola imprime:

                ✅ Fruta encontrada: Banana
    
    */

    

    //###### Eliminar una fruta #######
    printf("\nEliminando 'Banana'...\n");
    delete(&frutas, "Banana");

    printf("\n--- Lista después de eliminar ---\n");
    printList(frutas);

    /*
    
        🗑️ Eliminar "Banana"
        
            delete(&frutas, "Banana");

        La función hace lo siguiente internamente:

            1️⃣ Busca el nodo "Banana" -> ya lo tiene.
            2️⃣ Ajusta los punteros vecinos para saltar ese nodo.

            El nodo anterior ("Uva") ahora apunta al siguiente de "Banana", o sea "Manzana".

                Uva->next = Manzana

            El nodo siguiente ("Manzana") ahora apunta al anterior de "Banana", o sea "Uva".

                Manzana->prev = Uva

            Libera la memoria del nodo "Banana". 💾❌

        📉 Estado después de eliminar:
        
            NULL ← [ "Uva" ] ⇄ [ "Manzana" ] → NULL
                        ↑
                    frutas (head)

            El nodo "Banana" ya no existe en memoria.


    */
    

    // #### Liberar memoria #####
    freeList(&frutas);

    printf("\n✅ Memoria liberada correctamente.\n");

    /*
    
        🖨️ Mostrar lista final

            printList(frutas);

        Salida:
        --- Lista después de eliminar ---
            
            Uva <-> Manzana <-> NULL
    
    */

    return 0;
}

