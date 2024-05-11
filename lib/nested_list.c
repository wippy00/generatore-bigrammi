// #ifndef NESTED_LIST
// #define NESTED_LIST


#include <stdio.h>
#include <stdlib.h>

#include <wchar.h>

typedef struct nodoNest_t{
    wchar_t val[31];
    struct nodoNest_t* next_p;
    struct nodoNest_t* inner_p;

}nodoNest_t;

nodoNest_t* newNode(wchar_t val[31]){
    // Crea il nuovo Nodo
    nodoNest_t *new = (nodoNest_t*) malloc(sizeof(nodoNest_t));

    wcscpy(new->val, val);
    // wprintf(L"gino: %ls\n", val);
    new->next_p = NULL;
    new->inner_p = NULL;
    
    return new;
}

void append(nodoNest_t** head, wchar_t val[31]){
    nodoNest_t* new=newNode(val);
    if(*head==NULL)
    {
        *head=new;
        return;
    }
    nodoNest_t* temp=*head;
    while(temp->next_p!=NULL)
    {
        temp=temp->next_p;
    }
    temp->next_p=new;
}

void inner_append(nodoNest_t** head, wchar_t search[31], wchar_t val[31]){
    nodoNest_t* new=newNode(val);
    if(*head==NULL)
    {
        *head=new;
        return;
    }
    nodoNest_t* temp=*head;
    while(temp->next_p!=NULL && temp->val == search)
    {
        temp=temp->next_p;
    }
    temp->inner_p=new;
}

void printList(nodoNest_t *head){
    nodoNest_t *temp = head;
    
    // printf("\n [ ");

    // printf("%ls ", temp->val);
    // printf("%p ", temp->next_p);
    // printf("%p", temp->next_p);
    // temp = temp->next_p;

    while (temp != NULL)
    {
        printf(" -> %ls ", temp->val);
        printf("%p ", temp->next_p);
        printf("%p", temp->inner_p);

        temp = temp->next_p;
    }
    printf("\n");
}

void printInnerList(nodoNest_t *headP){
    nodoNest_t *tempP = NULL;
    nodoNest_t *listaDentro = NULL;
    
    // headP = headP->next_p;

    while (headP != NULL){

        printf(" %ls ", headP->val);
        
        
        
        if(headP->inner_p != NULL){
            listaDentro = headP->inner_p;

            while(listaDentro != NULL){

                printf(" %ls ", listaDentro->val);
                listaDentro = listaDentro->next_p;
            }
        }

        printf("\n");

        headP = headP->next_p;
        

        

        // while (innerP != NULL){
        //     printf(" %ls ", innerP->val);
        //     innerP = innerP->next_p;
        // }
        
    }
    printf("\n");
}

int main(){
    nodoNest_t *listaNest = NULL;
    
    wchar_t parola_1[10] = L"mario";
    append(&listaNest, parola_1);

    wchar_t parola_2[10] = L"gino";
    append(&listaNest, parola_2);

    wchar_t parola_3[10] = L"pino";
    append(&listaNest, parola_3);

    inner_append(&listaNest, parola_3, parola_2);

    // printList(listaNest);
    printInnerList(listaNest);
    
    return 0;
}

// #endif