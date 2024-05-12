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

#define WORD_SIZE 31;

FILE *open_file(char path[32])
{
    FILE *pointer_file = fopen(path, "r");
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
        // altrimenti aggiunge la lettera alla parola
        else if (iswalnum(character) || character == '\'')
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

SubNode_t *genera_bigrammi(nodo_t *lista_parole)
{
    SubNode_t *lista_bigrammi = NULL;

    wchar_t parola_1[31];
    pulisci(parola_1, 31);
    wchar_t parola_2[31];
    pulisci(parola_2, 31);

    while (lista_parole != NULL)
    {
        if (parola_1[0] == '\0')
        {
            wcscpy(parola_1, lista_parole->val);
            lista_parole = lista_parole->next_p;
            continue;
        }
        sb_magia(&lista_bigrammi, parola_1, lista_parole->val);
        wcscpy(parola_1, lista_parole->val);
        lista_parole = lista_parole->next_p;
    }
    return lista_bigrammi;
    // printf("%ls %ls \n", lista_parole->val, parola_1);
}

void genera_file(SubNode_t *head)
{
    while (head != NULL)
    {
        if (head->inner_p != NULL)
        {
            SubNode_t *sub_head = head->inner_p;
            while (sub_head != NULL)
            {
                if (sub_head->next_p != NULL)
                {
                }
                sub_head = sub_head->next_p;
            }
        }
        head = head->next_p;
    }
}

int main()
{
    setlocale(LC_ALL, "");
    setlocale(LC_NUMERIC, "en_US.UTF-8");

    nodo_t *lista_parole = NULL;
    SubNode_t *lista_bigrammi = NULL;

    FILE *file = open_file("./test/2k.txt");

    clock_t begin;
    clock_t end;

    begin = clock();
    lista_parole = genera_lista(file);
    end = clock();
    printf("\nGenera Lista: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);

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

    begin = clock();
    genera_file(lista_bigrammi);
    end = clock();
    printf("\nGenera bigrammi: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);


    return 0;
}