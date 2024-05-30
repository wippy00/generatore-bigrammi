#ifndef BILIST_H
#define BILIST_H

#include <stdio.h>
#include <stdlib.h>

#include <wchar.h>

/*
* La libreria "bilist.h" implementa una lista bidirezionale in linguaggio C.
* Utilizza una struct nodo_t per rappresentare un nodo della lista.
* Il nodo contiene un campo val che contiene una stringa di caratteri wide (wchar_t) e due puntatori a nodi successivi e precedenti.
* La lista è composta da nodi che contengono una stringa di caratteri wide (wchar_t). 
* La libreria fornisce funzioni per creare un nuovo nodo, aggiungere nodi , ottenere la lunghezza, stampare la lista.
*/

typedef struct nodo_t
{
    wchar_t val[31];       // Valore del nodo
    struct nodo_t *next_p; // Puntatore al prossimo nodo
    struct nodo_t *prev_p; // Puntatore al nodo precedente
} nodo_t;

/* 
* Funzione per creare un nuovo nodo
*/
nodo_t *newNode(wchar_t val[31])
{
    // Crea il nuovo Nodo
    nodo_t *new = (nodo_t *)malloc(sizeof(nodo_t));

    // Copia il valore nel nodo
    wcscpy(new->val, val);
    // inizializa i puntatori a NULL
    new->next_p = NULL;
    new->prev_p = NULL; 
    return new;
}

/* 
* Funzione per appendere un nodo alla coda della lista
*/
void append(nodo_t **head, wchar_t val[31])
{
    nodo_t *new = newNode(val);
    // se la lista è vuota, il nuovo nodo diventa la testa
    if (*head == NULL)
    {
        *head = new;
        return;
    }
    // altrimenti scorre la lista fino alla fine e appende il nuovo nodo
    nodo_t *temp = *head;
    while (temp->next_p != NULL)
    {
        temp = temp->next_p;
    }
    temp->next_p = new; // Imposta il puntatore al nodo successivo
    new->prev_p = temp; // Imposta il puntatore al nodo precedente
}

/* 
* Funzione per inserire un nodo alla testa della lista
*/
void insert(nodo_t **head, wchar_t val[31])
{
    nodo_t *new = newNode(val);
    // se la lista è vuota, il nuovo nodo diventa la testa
    if (*head == NULL)
    {
        *head = new;
        return;
    }
    // altrimenti il nuovo nodo diventa la testa e il vecchio nodo diventa il secondo
    new->next_p = *head;
    (*head)->prev_p = new;
    *head = new;
}

/* 
* Funzione per ottenere la lunghezza della lista
*/
int len(nodo_t *head)
{
    //scorre la lista e conta i nodi
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next_p;
    }
    return count;
}

/* 
* Funzione per ottenere la coda della lista (l'ultimo nodo)
*/
nodo_t *getTail(nodo_t *head)
{
    // se la lista è vuota ritorna NULL
    if (head == NULL)
        return NULL;
    // scorre la lista fino alla fine e ritorna l'ultimo nodo
    while (head->next_p != NULL)
    {
        head = head->next_p;
    }

    return head;
}

/* 
* Funzione per stampare la lista
*/
void printList(nodo_t *head)
{
    // stampa il primo nodo
    nodo_t *temp = head;
    printf("\n [ ");
    printf("%ls", temp->val);
    temp = temp->next_p; // avanza di un nodo
    // stampa i nodi successivi
    while (temp != NULL)
    {
        printf(" -> %ls", temp->val);
        temp = temp->next_p;
    }
    printf(" ]\n");
}

/* 
* Funzione per stampare la lista dalla coda
*/
void printReverseList(nodo_t *head)
{
    // scorre la lista fino alla coda
    while (head != NULL && head->next_p != NULL)
    {
        head = head->next_p;
    }
    
    // stampa l'ultimo nodo
    nodo_t *temp = head;
    printf("\n [ ");
    printf("%ls", temp->val);
    temp = temp->prev_p; // torna indietro di un nodo
    // stampa i nodi precedenti
    while (temp != NULL)
    {
        printf(" -> %ls", temp->val);
        temp = temp->prev_p;
    }
    printf(" ]\n");
}

#endif