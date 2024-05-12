#ifndef SUBLIST_H
#define SUBLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

typedef struct SubNode_t
{
    wchar_t val[31];
    struct SubNode_t *next_p;
    struct SubNode_t *inner_p;
} SubNode_t;

// Funzione per creare un nuovo nodo
SubNode_t *sb_newNode(wchar_t val[31])
{
    SubNode_t *new = (SubNode_t *)malloc(sizeof(SubNode_t));
    wcscpy(new->val, val);
    new->next_p = NULL;
    new->inner_p = NULL;
    return new;
}

// Funzione per aggiungere un nodo alla fine della lista principale
SubNode_t *sb_append(SubNode_t **head, wchar_t val[31])
{
    SubNode_t *new = sb_newNode(val);
    if (*head == NULL)
    {
        *head = new;
        return *head;
    }
    SubNode_t *temp = *head;
    while (temp->next_p != NULL)
    {
        temp = temp->next_p;
    }
    temp->next_p = new;
    return new;
}

// Funzione per aggiungere un nodo alla sottolista di un nodo specifico
void sb_appendToInner(SubNode_t *node, wchar_t val[31])
{
    if (node == NULL)
    {
        return; // Se il nodo è nullo, non possiamo aggiungere alla sottolista
    }
    if (node->inner_p == NULL)
    {
        node->inner_p = sb_newNode(val);
        return;
    }
    SubNode_t *temp = node->inner_p;
    while (temp->next_p != NULL)
    {
        temp = temp->next_p;
    }
    temp->next_p = sb_newNode(val);
}

SubNode_t *sb_find(SubNode_t *head, wchar_t search_word[31])
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

void sb_findInsert(SubNode_t **head_pointer, wchar_t search_word[31], wchar_t insert_word[31])
{
    SubNode_t *head = *head_pointer;
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

void sb_magia(SubNode_t **head_of_list, wchar_t search_word[31], wchar_t insert_word[31])
{
    SubNode_t *head = *head_of_list;
    SubNode_t *p = sb_find(head, search_word);
    if (p != NULL)
    {
        sb_appendToInner(p, insert_word);
    }
    else
    {
        SubNode_t *sub_head = sb_append(head_of_list, search_word);
        sb_appendToInner(sub_head, insert_word);
    }
    return;
}

// Funzione per stampare la lista principale e le relative sottoliste ricorsivamente
void printSubListRec(SubNode_t *head)
{
    SubNode_t *temp = head;
    printf("\n [ ");

    while (temp != NULL)
    {
        printf("%ls", temp->val);

        // Stampiamo la sottolista, se presente
        if (temp->inner_p != NULL)
        {
            printf(" (");
            printSubListRec(temp->inner_p);
            printf(")");
        }

        if (temp->next_p != NULL)
        {
            printf(" -> ");
        }

        temp = temp->next_p;
    }
    printf(" ]");
}

// Funzione per stampare la lista principale e la relativa sottolista
void printSubList(SubNode_t *head)
{
    SubNode_t *temp = head;
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
                printf("%ls", sub_head->val);
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
