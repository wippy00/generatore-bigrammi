#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

#include <wchar.h>
#include <wctype.h>

#include "./sublist.h"

/*
* La libreria "utils.h" implementa alcune comode funzioni per velocizzare la programmazione tramite linguaggio C.
* Include funzioni per la manipolazione delle stringhe, la gestione dei file e altro ancora.
*/


/*
* Questa funzione cerca una determinata parola nella sublist. 
* Se la parola viene trovata incrementa un contatore freq associato al nodo. 
* Se la parola non viene trovata, aggiunge un nuovo nodo all'elenco e inserisce la parola nel nodo.
*/
void find_or_insert_word(Node_t **head_of_list, wchar_t search_word[31], wchar_t insert_word[31])
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

/*
 * Controlla se esiste una determinata parola nella lista.
 * Se la parola viene trovata, aumenta la frequenza della frequenza di 1.
 * Se la parola non viene trovata, la inserisce nella lista con un conteggio di frequenza pari a 1.
 */
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

/*
* Funzione per aprire un file in lettura o scrittura e restiture eventuali errori.
*/

FILE *open_file(char *path, char mode[4])
{
    FILE *pointer_file = fopen(path, mode);
    if (pointer_file == NULL)
    {
        printf("Path errata o file non corretto 1\n");
        exit(1);
    }

    return pointer_file;
}


/*
* Funzione per la pulizia di una stringa.
* Data la stringa e la sua lunghezza, la funzione setta tutti i caratteri a '\0'.
*/
void pulisci(wchar_t *parola, int indice_parola)
{
    for (int i = 0; i < indice_parola; i++)
    {
        parola[i] = '\0';
    }
}

/*
* Funzione per modificare una stringa di wchar_T in modo da avere tutti i caratteri in minuscolo.
*/
void toLowerCase(wchar_t *str) {
    while (*str) {
        *str = towlower(*str);
        str++;
    }
}

#endif