#include <locale.h>
#include <stdlib.h>
#include <stdio.h>

#include <wchar.h>
#include <wctype.h>

#include "../lib/list.h"
#include "../lib/sublist.h"
#include "../lib/utils.h"

/* # Test only */
#include <time.h>

/*
Error 01: Errore apertura file
Error 02:
Error 03:
*/

void custom_printSubList(Node_t *head)
{
    printf("\n\n\n");

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
            printf("\n");
        }

        head = head->next_p;
    }
    printf("\n\n");
}

/*      Funzioni Programma       */
Node_t *read_file(FILE *file)
{
    Node_t *lista_bigrammi = NULL; // DEVI INIZIALIZZARE A NULL

    int indice_parola = 0;
    wchar_t character;
    wchar_t parola[31];
    pulisci(parola, 31);

    wchar_t bigramma_parola[31];
    pulisci(bigramma_parola, 31);
    float bigramma_numero = 0;

    Node_t *head_pointer = NULL; /* Traccia la testa del nodo da dove inizia sottolista */

    while ((character = fgetwc(file)) != WEOF)
    {
        character = towlower(character);
        // se il carattere è una virgola, viene processata la parola
        if ((character == ',') && indice_parola > 0)
        {
            parola[indice_parola] = '\0';

            if (head_pointer == NULL)
            {
                head_pointer = sb_append(&lista_bigrammi, parola);
                pulisci(&parola, indice_parola);
                indice_parola = 0;
                continue;
            }
            if (bigramma_parola[0] == '\0')
            {

                wcscpy(bigramma_parola, parola);
                pulisci(&parola, indice_parola);
                indice_parola = 0;
                continue;
            }

            if (swscanf(parola, L"%f", &bigramma_numero) == 1)
            {
                // Conversione riuscita, stampa il valore float
                // printf("Valore float: %f\n", bigramma_numero);
            }
            else
            {
                // Conversione fallita
                // printf("Errore durante la conversione\n");
            }
            sb_insertToInner(head_pointer, bigramma_parola, bigramma_numero);

            pulisci(&parola, indice_parola);
            indice_parola = 0;
            bigramma_parola[0] = '\0';
        }
        else if (character == '\n')
        {
            if (swscanf(parola, L"%f", &bigramma_numero) == 1)
            {
                // Conversione riuscita, stampa il valore float
                // printf("Valore float: %f\n", bigramma_numero);
            }
            else
            {
                // Conversione fallita
                // printf("Errore durante la conversione\n");
            }
            sb_insertToInner(head_pointer, bigramma_parola, bigramma_numero);
            head_pointer = NULL;
            bigramma_parola[0] = '\0';
            pulisci(&parola, indice_parola);
            indice_parola = 0;

            // custom_printSubList(lista_bigrammi);
        }
        else
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
    // if (indice_parola > 0)
    // {
    //     parola[indice_parola] = '\0';
    //     indice_parola = 0;
    //     process(&lista, parola);
    // }

    return lista_bigrammi;
}

nodo_t *genera_parole(Node_t *lista_bigrammi, int n_parole, wchar_t parola_iniziale[31])
{
    srand(time(0));
    // srand(100);

    int random;
    Node_t *head = NULL;

    if (parola_iniziale == L"")
    {

        wchar_t caratteri_iniziali[4] = {L'.', L'?', L'!', '\0'};
        wchar_t scelta[2] = {'\0', '\0'};
        int tentativi[3] = {0, 0, 0};

        do
        {
            random = ((double)rand() / RAND_MAX) * (3 - 0) + 0;
            scelta[0] = caratteri_iniziali[random];
            head = sb_find(lista_bigrammi, scelta);
            tentativi[random] = 1;

            // printf("\nscelta: %ls\n", scelta);
            // printf("stato array: %d %d %d \n", tentativi[0],tentativi[1],tentativi[2]);

        } while (head == NULL && (tentativi[0] == 0 || tentativi[1] == 0 || tentativi[2] == 0));

        if (head == NULL)
        {
            printf("\nIl testo non contiene nessuno dei caratteri di default ( . ? ! ), fornire una parola da cui iniziare\n");
            return -1;
        }
    }
    else
    {
        head = sb_find(lista_bigrammi, parola_iniziale);
        if (head == NULL)
        {
            printf("\nLa parola: %ls non esiste\n", parola_iniziale);
            return -1;
        }
    }

    nodo_t *lista_parole = NULL;
    SubNode_t *sub_head = NULL;
    float valore = 0;

    for (int i = 0; i < n_parole; i++)
    {
        random = ((double)rand() / RAND_MAX) * (100 - 0) + 0;
        sub_head = head->inner_p;
        while (sub_head != NULL)
        {
            valore += (sub_head->freq * 100);
            if (valore >= random)
            {
                valore = 0;
                break;
            }

            sub_head = sub_head->next_p;
        }
        insert(&lista_parole, sub_head->val);

        head = sb_find(lista_bigrammi , sub_head->val);
    }

    return lista_parole;

    // printf("numero random: %d\n", caratteri_iniziali[random]);
    // printf("Stringa: %ls\n", caratteri_iniziali);
}
/*      Main       */
int main()
{
    setlocale(LC_ALL, "");
    setlocale(LC_NUMERIC, "en_US.UTF-8");

    nodo_t *lista_parole = NULL;
    Node_t *lista_bigrammi = NULL;

    clock_t begin;
    clock_t end;

    FILE *input_file = open_file("./bigrammi.csv", "r");

    begin = clock();
    lista_bigrammi = read_file(input_file);
    end = clock();
    printf("\nAnalizzare csv: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);

    // printf("\n");
    // printSubList(lista_bigrammi);
    // printf("\n");

    begin = clock();
    lista_parole = genera_parole(lista_bigrammi, 600000, L".");
    end = clock();
    printf("\nGeneratore parole: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);

    // printf("\n");
    // printList(lista_parole);
    // printf("\n");

    return 0;
}