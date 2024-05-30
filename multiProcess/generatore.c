#include <locale.h>
#include <stdlib.h>
#include <stdio.h>

#include <wchar.h>
#include <wctype.h>

#include <math.h>

#include "../lib/bilist.h"
#include "../lib/sublist.h"
#include "../lib/utils.h"

/* # Test only */
#include <time.h>

// void printSubList_csv(Node_t *head)
// {
//     printf("\n\n\n");

//     while (head != NULL)
//     {
//         printf("%ls", head->val);

//         // Stampiamo la sottolista, se presente
//         if (head->inner_p != NULL)
//         {
//             SubNode_t *sub_head = head->inner_p;
//             printf(" (");
//             while (sub_head != NULL)
//             {
//                 printf("%ls %.4f", sub_head->val, sub_head->freq);
//                 if (sub_head->next_p != NULL)
//                 {
//                     printf(" -> ");
//                 }

//                 sub_head = sub_head->next_p;
//             }

//             printf(")");
//         }

//         if (head->next_p != NULL)
//         {
//             printf("\n");
//         }

//         head = head->next_p;
//     }
//     printf("\n\n");
// }



/*      Funzioni Programma       */

/*
 * Legge un file e estrae i bigrammi da esso.
 */
Node_t *read_file(FILE *file)
{
    Node_t *lista_bigrammi = NULL;

    int indice_parola = 0; /* Traccia della lunghezza della parola  */
    wchar_t character;     /* carattere corrente */
    wchar_t parola[31];    /* buffer per la parola */
    pulisci(parola, 31);

    wchar_t bigramma_parola[31]; /* buffer per la parola del bigramma */
    pulisci(bigramma_parola, 31);
    float bigramma_numero = 0; /* buffer per il numero del bigramma */

    float sub_counter = 0;

    Node_t *head_pointer = NULL; /* Traccia la testa del nodo da dove inizia sottolista */

    while ((character = fgetwc(file)) != WEOF)
    {
        character = towlower(character);

        /* se il carattere è una virgola, viene processata la parola */
        if ((character == ',') && indice_parola > 0)
        {
            parola[indice_parola] = '\0';

            if (head_pointer == NULL)
            {
                head_pointer = sb_append(&lista_bigrammi, parola);

                sub_counter = 0;

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

            sub_counter += bigramma_numero;

            pulisci(&parola, indice_parola);
            indice_parola = 0;
            bigramma_parola[0] = '\0';
        }
        /* se il carattere è un a capo, viene inserita la coppia parola-valore e vengono resettate le variabili */
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

            sub_counter += bigramma_numero;

            if (sub_counter > 1.000334 || sub_counter < 0.999673 )
            {
                printf("\nErrore: File csv malformato; La somma delle frequenze è diversa da 1 : %f\n", sub_counter);
                // return lista_bigrammi;
            }

            head_pointer = NULL;
            bigramma_parola[0] = '\0';
            pulisci(&parola, indice_parola);
            indice_parola = 0;

            // printSubList_csv(lista_bigrammi);
        }

        /* per qualsiasi altro caso viene aggiunto il carattere al buffer */
        else
        {
            /* se c'è una parola maggiore di 30 caratteri la tronca */
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

/**
 * Genera una lista di parole in base ai bigrammi presenti nella lista dei bigrammi fornita.
 * Data una parola da cui iniziare, la generazione delle parole comincerà da lì, altrimenti verrà scelta una parola iniziale casuale tra '.', '?', '!'.
 */
nodo_t *genera_parole(Node_t *lista_bigrammi, int n_parole, wchar_t *parola_iniziale)
{
    // srand(time(0));
    srand(0);

    int random;
    Node_t *head = NULL;
    nodo_t *lista_parole = NULL;

    if (wcslen(parola_iniziale) <= 0)
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
            printf("\nErrore: Il testo non contiene nessuno dei caratteri di default ( . ? ! ), fornire una parola da cui iniziare\n");
            exit(-1);
            return NULL;
        }
    }
    else
    {   
        toLowerCase(parola_iniziale);

        head = sb_find(lista_bigrammi, parola_iniziale);
        if (head == NULL)
        {
            printf("\nErrore: La parola/carattere '%ls' non è presente nel testo\n", parola_iniziale);
            exit(-1);
            return -1;
        }
    }

    SubNode_t *sub_head = NULL;
    float valore = 0;

    for (int i = 0; i < n_parole; i++)
    {
        random = ((double)rand() / RAND_MAX) * (100000 - 0) + 0;
        sub_head = head->inner_p;
        while (sub_head != NULL)
        {
            valore += (sub_head->freq * 100000);
            if (valore >= random)
            {
                valore = 0;
                break;
            }

            sub_head = sub_head->next_p;
            if (sub_head == NULL)
            {
                printf("\n Round error");
                return;
            }
        }
        insert(&lista_parole, sub_head->val);

        head = sb_find(lista_bigrammi, sub_head->val);

        if (head == NULL)
        {
            head = lista_bigrammi;
            // printf("\nErrore: Lista malformata; Data la parola: %ls non è possibile generarne un'altra\n", parola_iniziale);
            // exit(-1);
            // return lista_parole;
        }
    }

    return lista_parole;

    // printf("numero random: %d\n", caratteri_iniziali[random]);
    // printf("Stringa: %ls\n", caratteri_iniziali);
}

/*
 * Funzione per generare un file di testo a partire da una lista di bigrammi.
 *
 * La funzione prende in input un puntatore a un file e un puntatore al nodo di testa della lista.
 * Scorre la lista e stampa le parole nel file, con alcune regole specifiche:
 * - La prima lettera della prima parola viene convertita in maiuscolo e stampata nel file.
 * - Se una parola è seguita da un carattere di punteggiatura (. ? !), la parola viene stampata nel file,
 *   seguita dal carattere di punteggiatura e una nuova riga.
 *   Successivamente, la parola successiva viene convertita in maiuscolo e stampata nel file.
 * - Altrimenti, la parola viene semplicemente stampata nel file.
 *
 */
void genera_file_generatore(FILE *file, nodo_t *head)
{
    short unsigned maiusc_flag = 0;
    nodo_t *next = NULL;

    nodo_t *tail = NULL;
    head = getTail(head);

    head->val[0] = towupper(head->val[0]);
    fprintf(file, "%ls", head->val);
    head = head->prev_p;

    while (head != NULL)
    {
        if (head->prev_p != NULL)
            next = head->prev_p;

        if (next->val[0] == L'.' || next->val[0] == L'?' || next->val[0] == L'!')
        {
            /* stampa la parola prima del carattere di punteggiatura */
            fprintf(file, " %ls", head->val);

            /* avanza al carattere di punteggiatura e lo stampa */
            if (head->prev_p != NULL)
                head = head->prev_p;
            else
                break;
            // fprintf (file, "%ls", head->val);
            fprintf(file, "%ls\n", head->val);

            /* avanza alla parola dopo, mette la maiuscola e stampa la parola */
            if (head->prev_p != NULL)
                head = head->prev_p;
            else
                break;
            head->val[0] = towupper(head->val[0]);
            // fprintf(file, " %ls", head->val);
            fprintf(file, "%ls", head->val);
            head = head->prev_p;
            continue;
        }

        fprintf(file, " %ls", head->val);
        head = head->prev_p;
    }
}

/*      Main       */
void main_generatore(char *input_path, char *n_words, wchar_t *search_word, char *output_path)
{
    setlocale(LC_ALL, "");
    setlocale(LC_NUMERIC, "en_US.UTF-8");

    int pid1 = -1;
    int pid2 = -1;

    nodo_t *lista_parole = NULL;
    Node_t *lista_bigrammi = NULL;

    clock_t begin;
    clock_t end;

    FILE *input_file = open_file(input_path, "r");

    begin = clock();
    lista_bigrammi = read_file(input_file);
    end = clock();
    printf("\nAnalizzare csv: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    pid1 = fork();

    // printf("pid1: %d\n ",pid1);

    if (pid1 == 0)
    {
        int n_words_int = atoi(n_words);

        begin = clock();
        lista_parole = genera_parole(lista_bigrammi, n_words_int, search_word);
        end = clock();
        printf("Generatore parole: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);

        pid2 = fork();
        if (pid2 == 0)
        {
            FILE *output_file = open_file(output_path, "w");

            begin = clock();
            genera_file_generatore(output_file, lista_parole);
            end = clock();
            
            fclose(output_file);

            printf("Generatore file: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);
            printf("\nDone\n");
            exit(0);
        }
        else
        {
            wait(NULL);
        }
        exit(0);
    }
    else
    {
        wait(NULL);
    }
}
 
// int main()
// {
//     main_generatore("out.csv", "100", L"Hitaghi","out.txt");
//     return 0;
// }