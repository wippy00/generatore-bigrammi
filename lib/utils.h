#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

#include <wchar.h>
#include <wctype.h>

#include "./list.h"
#include "./sublist.h"


/**
 * @brief Performs a magical operation on a linked list.
 *
 * This function searches for a given word in the linked list. If the word is found,
 * it increments a counter associated with the node. If the word is not found, a new
 * node is appended to the list with the given word, and an inner node is inserted
 * with the insert word.
 *
 * @param head_of_list A pointer to the head of the linked list.
 * @param search_word The word to search for in the linked list.
 * @param insert_word The word to insert into the linked list if the search word is not found.
 */
void magia(Node_t **head_of_list, wchar_t search_word[31], wchar_t insert_word[31])
{
    Node_t *head = *head_of_list;
    Node_t *node_found = sb_find(head, search_word);
    if (node_found == NULL)
    {
        node_found = sb_append(head_of_list, search_word); // Perchè si così è più veloce, molto più veloce
        sb_insertToInner(node_found, insert_word);
    }
    else
    {
        checkAndIncrement(node_found, insert_word);
    }
    return;
}

/**
 * Checks if a given word exists in the inner_p of a Node_t structure.
 * If the word is found, increments its frequency by 1. If not found, inserts the word into the inner_p.
 *
 * @param node The Node_t structure to search in.
 * @param search_word The word to search for.
 */
void checkAndIncrement(Node_t *node, wchar_t search_word[31])
{
    SubNode_t *node_found = sb_subFind(node->inner_p, search_word);
    if (node_found == NULL)
    {
        sb_insertToInner(node, search_word);
    }
    else
    {
        node_found->freq++;
    }
    return;
}

/**
 * Opens a file with the specified path and mode.
 *
 * @param path The path of the file to be opened.
 * @param mode The mode in which the file should be opened.
 * @return A pointer to the opened file.
 * @throws An error message and exits the program if the file cannot be opened.
 */
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

/**
 * Clears the given string by setting all characters to null.
 * 
 * @param parola(wchar_t) The string to be cleared.
 * @param indice_parola(int) The length of the string.
 */
void pulisci(wchar_t *parola, int indice_parola)
{
    for (int i = 0; i < indice_parola; i++)
    {
        parola[i] = '\0';
    }
}

#endif