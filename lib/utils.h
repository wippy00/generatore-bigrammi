#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

#include <wchar.h>
#include <wctype.h>

#include "./sublist.h"

void magia(Node_t **head_of_list, wchar_t search_word[31], wchar_t insert_word[31])
{
    Node_t *head = *head_of_list;
    Node_t *node_found = sb_find(head, search_word);
    if (node_found == NULL)
    {
        node_found = sb_append(head_of_list, search_word); // Perchè si così è più veloce, molto più veloce
        sb_insertToInner(node_found, insert_word, 1);
    }
    else
    {
        checkAndIncrement(node_found, insert_word);
    }
    return;
}

void checkAndIncrement(Node_t *node, wchar_t search_word[31])
{
    SubNode_t *node_found = sb_subFind(node->inner_p, search_word);
    if (node_found == NULL)
    {
        sb_insertToInner(node, search_word, 1);
    }
    else
    {
        node_found->freq++;
    }
    return;
}

FILE *open_file(char path[32], char mode[4])
{
    FILE *pointer_file = fopen(path, mode);
    if (pointer_file == NULL)
    {
        printf("Path errata o file non corretto 1\n");
        exit(1);
    }

    return pointer_file;
}

void pulisci(wchar_t *parola, int indice_parola)
{
    for (int i = 0; i < indice_parola; i++)
    {
        parola[i] = '\0';
    }
}

#endif