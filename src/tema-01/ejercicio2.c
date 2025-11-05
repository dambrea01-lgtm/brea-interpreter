/*
    Problema:
        - Define una lista doblemente enlazada de strings en el heap, 
          con funciones de inserción, búsqueda y eliminación.
*/


#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

typedef struct Node{

    char *data; 
    struct Node *prev; 
    struct Node *next; 

} Node;

Node* createNode(const char *str){

    Node *node = malloc(sizeof(Node)); 
    node->data = strdup(str);   
    node->prev = NULL;  
    node->next = NULL; 
    return node;
}


void insert(Node **head, const char *str){

    Node *node = createNode(str);
    node->next = *head; 
    if(*head) (*head)->prev = node; 
    *head = node; 
}

Node* find(Node *head, const char *str){
    Node *curr = head;
    while(curr){
        if(strcmp(curr->data, str)==0) return curr; 
        curr = curr->next;                         
    }
    return NULL; 
}

void delete(Node **head, const char *str){
    Node *node = find(*head, str);
    if (!node) return;

    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    if (*head == node) *head = node->next; 

    free(node->data); 
    free(node);       
}

int main() {
    
    Node *frutas = NULL; 

    insert(&frutas, "Manzana");
    insert(&frutas, "Banana");
    insert(&frutas, "Uva");

    printf("\n--- Lista inicial ---\n");
    printList(frutas);

    Node *f = find(frutas, "Banana");
    if (f)
        printf("✅ Fruta encontrada: %s\n", f->data);
    else
        printf("❌ Fruta no encontrada\n");

    printf("\nEliminando 'Banana'...\n");
    delete(&frutas, "Banana");

    printf("\n--- Lista después de eliminar ---\n");
    printList(frutas);

    freeList(&frutas);

    printf("\n✅ Memoria liberada correctamente.\n");
    
    return 0;
}