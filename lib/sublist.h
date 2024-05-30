#ifndef SUBLIST_H
#define SUBLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/*
* La libreria "sublist.h" implementa una lista di sottliste in linguaggio C.
* Utilizza una struct Node_t per rappresentare un nodo della lista, e una struct SubNode_t per rappresentare un nodo della sottolista.
* Node_t contiene un campo val che contiene una stringa di caratteri wide (wchar_t) e due puntatori, uno al nodo successivo e uno al nodo della sottolista.
* SubNode_t contiene un campo val che contiene una stringa di caratteri wide (wchar_t), un campo freq che contiene un valore float e un puntatore al prossimo nodo della sottolista.
*/


typedef struct Node_t
{
    wchar_t val[31];
    struct Node_t *next_p;
    struct SubNode_t *inner_p;
} Node_t;

typedef struct SubNode_t
{
    wchar_t val[31];
    float freq;
    struct SubNode_t *next_p;
} SubNode_t;

/* 
* Funzione per creare un nuovo nodo
*/
Node_t *sb_newNode(wchar_t val[31])
{
    Node_t *new = (Node_t *)malloc(sizeof(Node_t));
    wcscpy(new->val, val);
    new->next_p = NULL;
    new->inner_p = NULL;
    return new;
}

/* 
* Funzione per creare un nuovo sottonodo
*/
SubNode_t *sb_newSubNode(wchar_t val[31])
{
    SubNode_t *new = (SubNode_t *)malloc(sizeof(SubNode_t));
    wcscpy(new->val, val);
    new->freq = 0;
    new->next_p = NULL;
    return new;
}

/* 
* Funzione per appendere un nodo alla coda della lista principale
*/
Node_t *sb_append(Node_t **head, wchar_t val[31])
{
    Node_t *new = sb_newNode(val);
    if (*head == NULL)
    {
        *head = new;
        return *head;
    }
    Node_t *temp = *head;
    while (temp->next_p != NULL)
    {
        temp = temp->next_p;
    }
    temp->next_p = new;
    return new;
}

/* 
* Funzione per aggiungere un nodo alla tesa della lista principale
*/
Node_t *sb_insert(Node_t **head, wchar_t val[31])
{
    Node_t *new = sb_newNode(val);
    new->next_p = *head;
    *head = new;
    return new;
}

/* 
* Funzione per appendere un nodo alla sottolista di un nodo specifico
*/
void sb_appendToInner(Node_t *node, wchar_t val[31])
{
    if (node == NULL)
    {
        return; // Se il nodo è nullo, non possiamo aggiungere alla sottolista
    }
    if (node->inner_p == NULL)
    {
        node->inner_p = sb_newSubNode(val);
        return;
    }
    Node_t *temp = node->inner_p;
    while (temp->next_p != NULL)
    {
        temp = temp->next_p;
    }
    temp->next_p = sb_newSubNode(val);
}

/* 
* Funzione per aggiungere un nodo alla sottolista di un nodo specifico
*/
void sb_insertToInner(Node_t *node, wchar_t val[31], float freq)
{
    if (node == NULL)
    {
        return; // Se il nodo è nullo, non possiamo aggiungere nulla
    }
    SubNode_t *new = sb_newSubNode(val); // Crea un nuovo nodo con il valore fornito
    new->next_p = node->inner_p;         // Imposta il puntatore next_p del nuovo nodo a quello che era il primo nodo della sottolista
    new->freq = freq;
    node->inner_p = new; // Ora, il nuovo nodo diventa la testa della sottolista
}

/*
* Funzione per cercare un nodo nella lista principale
*/
Node_t *sb_find(Node_t *head, wchar_t search_word[31])
{
    while (head != NULL)
    {   
        // printf("scelta: %ls ", search_word);
        // printf("%d ", wcscmp(search_word, head->val));
        // printf("corrente:%ls \n", head->val);
        
        if (wcscmp(search_word, head->val) == 0)
        {
            return head;
            // printf("%p", &head);
        }
        head = head->next_p;
    }
    return NULL;
}

/*
* Funzione per cercare un nodo nella sottolista di un nodo specifico
*/
SubNode_t *sb_subFind(SubNode_t *head, wchar_t search_word[31])
{
    while (head != NULL)
    {
        if (wcscmp(search_word, head->val) == 0)
        {
            return head;
            // printf("%p", &head);
        }
        head = head->next_p;
    }
    return NULL;
}

/*
* Funzione per cercare un nodo nella sottolista di un nodo specifico
*/
void sb_findInsert(Node_t **head_pointer, wchar_t search_word[31], wchar_t insert_word[31])
{
    Node_t *head = *head_pointer;
    SubNode_t *p = sb_find(head, search_word);
    if (p != NULL)
    {
        sb_appendToInner(p, insert_word);
    }
    else
    {
        sb_append(head_pointer, insert_word);
    }
    return;
}

/*
* Funzione per contare il numero di nodi nella lista principale
*/
int sb_len(Node_t *head)
{
    int count = 0;
    while (head != NULL)
    {
        count++;

        head = head->next_p;
    }
    return count;
}

/*
* Funzione per contare il numero di nodi nella sottolista di un nodo specifico
*/
int sb_innerlen(SubNode_t *head)
{
    int count = 0;
    while (head != NULL)
    {
        count += head->freq;

        head = head->next_p;
    }
    return count;
}


/*
* Funzione per stampare la lista principale e la relativa sottolista
*/
void printSubList(Node_t *head)
{
    printf("\n [ ");

    while (head != NULL)
    {
        printf("%ls", head->val);

        // Stampiamo la sottolista, se presente
        if (head->inner_p != NULL)
        {
            SubNode_t *sub_head = head->inner_p;
            printf(" (");
            while (sub_head != NULL)
            {
                printf("%ls %.4f", sub_head->val, sub_head->freq);
                if (sub_head->next_p != NULL)
                {
                    printf(" -> ");
                }
                sub_head = sub_head->next_p;
            }
            printf(")");
        }
        if (head->next_p != NULL)
        {
            printf(" -> ");
        }
        head = head->next_p;
    }
    printf(" ]");
}

#endif
