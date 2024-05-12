#ifndef LIST_H
#define LIST_H


#include <stdio.h>
#include <stdlib.h>

#include <wchar.h>

typedef struct nodo_t{
    wchar_t val[31];
    struct nodo_t* next_p;
}nodo_t;

nodo_t* newNode(wchar_t val[31]){
    // Crea il nuovo Nodo
    nodo_t *new = (nodo_t*) malloc(sizeof(nodo_t));

    wcscpy(new->val, val);
    // wprintf(L"gino: %ls\n", val);
    new->next_p = NULL;
    
    return new;
}

void append(nodo_t** head, wchar_t val[31]){
    // appende dalla coda
    nodo_t* new=newNode(val);
    if(*head==NULL)
    {
        *head=new;
        return;
    }
    nodo_t* temp=*head;
    while(temp->next_p!=NULL)
    {
        temp=temp->next_p;
    }
    temp->next_p=new;
}

// appende dalla testa
void insert(nodo_t** head, wchar_t val[31]){
    nodo_t* new = newNode(val);
    
    new->next_p = *head;
    *head = new;
    return;
}

int len(nodo_t *head){
    
    int count=0;
    while (head != NULL)
    {
        count++;

        head = head->next_p;
    }
    return count;
}

void printList(nodo_t *head){
    nodo_t *temp = head;
    
    printf("\n [ ");

    printf("%ls", temp->val);
    temp = temp->next_p;

    while (temp != NULL)
    {
        printf(" -> %ls", temp->val);

        temp = temp->next_p;
    }
    printf(" ]\n");
}

#endif