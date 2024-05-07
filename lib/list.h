#ifndef LIST_H
#define LIST_H


#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char val[30];
    struct Nodo* next;
}Nodo;

Nodo* newNode(char val[30]){
    // Crea il nuovo Nodo
    Nodo *new = (Nodo*) malloc(sizeof(Nodo));

    strncpy(new->val, val, 30);
    new->next = NULL;
    
    return new;
}

void append(Nodo** head, char val[30]){
    Nodo* new=newNode(val);
    if(*head==NULL)
    {
        *head=new;
        return;
    }
    Nodo* temp=*head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=new;
}

void printList(Nodo *head){
    Nodo *temp = head;
    
    printf("\n [ ");

    printf("%s", temp->val);
    temp = temp->next;

    while (temp != NULL)
    {
        printf(" -> %s", temp->val);

        temp = temp->next;
    }
    printf(" ]\n");
}

#endif