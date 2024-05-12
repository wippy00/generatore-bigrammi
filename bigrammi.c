#include <locale.h>
#include <stdlib.h>
#include <stdio.h>

#include <wchar.h>
#include <wctype.h>

#include "./lib/list.h"
#include "./lib/sublist.h"

/* # Test only */
#include <time.h>

/*
Error 01: Errore apertura file
Error 02:
Error 03:
*/

/*      Funzioni Utili     */
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

/*      Funzioni Programma       */

nodo_t *genera_lista(FILE *file)
{
    int indice_parola = 0;
    wchar_t character;
    wchar_t parola[31];

    pulisci(parola, 31);

    nodo_t *lista = NULL; // DEVI INIZIALIZZARE A NULL

    insert(&lista, L".");

    while ((character = fgetwc(file)) != WEOF)
    {
        character = towlower(character);
        // se il carattere è uno spazio o si va a capo, viene aggiunta la parola alla lista
        if ((character == ' ' || character == '\n') && indice_parola > 0)
        {
            parola[indice_parola] = '\0';

            insert(&lista, parola);

            pulisci(&parola, indice_parola);

            indice_parola = 0;
        }
        // aggiunge come parola i caratteri di punteggiatura
        else if (character == '.' || character == '?' || character == '!')
        {
            parola[indice_parola] = '\0';

            insert(&lista, parola);

            parola[0] = character;
            parola[1] = '\0';

            insert(&lista, parola);

            pulisci(&parola, indice_parola);

            indice_parola = 0;
        }
        // aggiunge alla parola l'apostrofo e termina la parola
        else if(character == '\'')
        {
            parola[indice_parola] = character;
            indice_parola++;
            parola[indice_parola] = '\0';
            insert(&lista, parola);
            pulisci(&parola, indice_parola);
            indice_parola = 0;
        }
        // altrimenti aggiunge la lettera alla parola
        else if (iswalnum(character))
        {
            // se c'è una parola maggiore di 30 caratteri troncala
            if (indice_parola > 30)
            {
                indice_parola = 0;
                printf("%ls \n", parola);
            }

            parola[indice_parola] = character;
            indice_parola++;
        }
    }
    // se rimane una parola nel buffer la aggiunge
    if (indice_parola > 0)
    {
        parola[indice_parola] = '\0';
        indice_parola = 0;
        insert(&lista, parola);
    }

    return lista;
}

Node_t *genera_bigrammi(nodo_t *lista_parole)
{
    Node_t *lista_bigrammi = NULL;

    wchar_t buffer[31];
    pulisci(buffer, 31);

    while (lista_parole != NULL)
    {
        if (buffer[0] == '\0')
        {
            wcscpy(buffer, lista_parole->val);
            lista_parole = lista_parole->next_p;
            continue;
        }
        magia(&lista_bigrammi, lista_parole->val, buffer);
        wcscpy(buffer, lista_parole->val);
        lista_parole = lista_parole->next_p;
    }
    return lista_bigrammi;
    // printf("%ls %ls \n", lista_parole->val, buffer);
}

void genera_file(FILE *file, Node_t *head)
{
    SubNode_t *sub_head = NULL;
    float freq = 0;
    int len = 0;

    while (head != NULL)
    {
        fprintf(file, "%ls", head->val);

        // Stampiamo la sottolista, se presente
        if (head->inner_p != NULL)
        {
            SubNode_t *sub_head = head->inner_p;
            // fprintf(file, "  (");
            fprintf(file, ",");
            len = sb_innerlen(sub_head);
            while (sub_head != NULL)
            {
                if (len > 1)
                {
                    freq = (float) sub_head->freq / len;
                }
                else
                {
                    freq = 1;
                }

                fprintf(file, "%ls,%.4g", sub_head->val, freq);
                // fprintf(file, "%ls,%.0f", sub_head->val, sub_head->freq);
                if (sub_head->next_p != NULL)
                {
                    // fprintf(file, " - ");
                    fprintf(file, ",");
                }
            
                sub_head = sub_head->next_p;
            }

            // fprintf(file, ")\n");
            fprintf(file, "\n");
        }
        head = head->next_p;
    }
}

/*      Programma       */

int main()
{
    setlocale(LC_ALL, "");
    setlocale(LC_NUMERIC, "en_US.UTF-8");

    nodo_t *lista_parole = NULL;
    Node_t *lista_bigrammi = NULL;

    FILE *input_file = open_file("./test/lotr.txt", "r");

    clock_t begin;
    clock_t end;

    clock_t master_begin;
    clock_t master_end;

    master_begin = clock();

    begin = clock();
    lista_parole = genera_lista(input_file);
    end = clock();
    printf("\nGenera Lista: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);

    printf("\n");
    printf("len lista: %d parole", len(lista_parole));
    printf("\n");

    // printf("\n");
    // printList(lista_parole);
    // printf("\n");

    begin = clock();
    lista_bigrammi = genera_bigrammi(lista_parole);
    end = clock();
    printf("\nGenera bigrammi: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);

    // printf("\n");
    // printSubList(lista_bigrammi);
    // printf("\n");
    // Node_t conta_occorrenze(lista_bigrammi);

    FILE *output_file = open_file("./bigrammi.csv", "w");

    begin = clock();
    genera_file(output_file, lista_bigrammi);
    end = clock();
    printf("\nGenera file: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);

    master_end = clock();
    printf("\nTutto impiega: %fs\n", (double)(master_end - master_begin) / CLOCKS_PER_SEC);
    return 0;
}