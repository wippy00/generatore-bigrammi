#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

#include <wchar.h>
#include <wctype.h>

#include "../lib/bilist.h"
#include "../lib/sublist.h"
#include "../lib/utils.h"

/* # Test only */
#include <time.h>


/*
 * Rimuove gli zeri non significativi da una stringa.
 */
void removeZero(char *str)
{
    if (str[0] == '1' && str[1] == '.' && str[2] == '0')
    {
        strcpy(str, "1");
        return;
    }
    for (int i = 7; i >= 3; i--)
    {
        char lettera = str[i];
        int ascii_char = (int)lettera;

        if (ascii_char == 48 || ascii_char == 0)
        {
            str[i] = '\0';
        }
        else
        {
            break;
        }
    }

    return;
}

/*      Funzioni Programma       */


/*
 * Genera una lista di parole da un file.
 *
 * Questa funzione legge i caratteri dal file e le inserisce nella lista.
 * Ogni parola termina con uno spazio, un carattere di nuova riga o un segno di punteggiatura (!, ? , .).
 */

nodo_t *genera_lista(FILE *file)
{
    int indice_parola = 0;
    wchar_t character;
    wchar_t parola[31];

    pulisci(parola, 31);

    nodo_t *lista = NULL; // DEVI INIZIALIZZARE A NULL

    // insert(&lista, L".");

    wchar_t prima_parola[31];
    pulisci(prima_parola, 31);

    while ((character = fgetwc(file)) != WEOF)
    {
        character = towlower(character);
        // se il carattere è uno spazio o si va a capo, viene aggiunta la parola alla lista
        if ((character == ' ' || character == '\n') && indice_parola > 0)
        {
            parola[indice_parola] = '\0';

            insert(&lista, parola);
            if (prima_parola[0] == '\0')
            {
                wcscpy(prima_parola, parola);
            }

            pulisci(&parola, indice_parola);

            indice_parola = 0;
        }
        // aggiunge come parola i caratteri di punteggiatura
        else if (character == '.' || character == '?' || character == '!')
        {
            parola[indice_parola] = '\0';

            insert(&lista, parola);
            if (prima_parola[0] == '\0')
            {
                wcscpy(prima_parola, parola);
            }

            parola[0] = character;
            parola[1] = '\0';

            insert(&lista, parola);
            if (prima_parola[0] == '\0')
            {
                wcscpy(prima_parola, parola);
            }

            pulisci(&parola, indice_parola);

            indice_parola = 0;
        }
        // aggiunge alla parola l'apostrofo e termina la parola
        else if (character == '\'')
        {
            parola[indice_parola] = character;
            indice_parola++;
            parola[indice_parola] = '\0';
            insert(&lista, parola);
            if (prima_parola[0] == '\0')
            {
                wcscpy(prima_parola, parola);
            }
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

    insert(&lista, prima_parola);

    return lista;
}


/*
 * Genera una lista di bigrammi data una lista di parole.
 *
 * Per ogni parola della lista controlla se questa è presente nella lista dei bigrammi.
 * Se la parola non è presente, aggiunge la parola nella lista.
 * Se la parola è già presente, cerca dov'è la parola nella lista e la aggiunge alla sottolista.
 */
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
        find_or_insert_word(&lista_bigrammi, lista_parole->val, buffer);
        wcscpy(buffer, lista_parole->val);
        lista_parole = lista_parole->next_p;
    }
    return lista_bigrammi;
    // printf("%ls %ls \n", lista_parole->val, buffer);
}
/*
 * Genera un file con il contenuto della lista dei bigrammi.
 * Ogni nodo nella lista di bigrammi rappresenta una parola e ogni nodo può avere un elenco di altre parole interne con la loro frequenza
 * La funzione conta quanti nodi sono presenti nella sotto lista e calcola la frequenza di ogni parola dividendo la frequenza totale (della parola)  il numero di nodi.
 */
void genera_file(FILE *file, Node_t *head)
{
    SubNode_t *sub_head = NULL;
    float freq = 0;
    int len = 0;

    while (head != NULL)
    {
        fprintf(file, "%ls", head->val);

        // Stampiamo la sottolista, se presente
        if (head->inner_p == NULL)
        {
            continue;
        }
        SubNode_t *sub_head = head->inner_p;
        // fprintf(file, "  (");
        fprintf(file, ",");
        len = sb_innerlen(sub_head);
        while (sub_head != NULL)
        {
            if (len > 1)
            {
                freq = (float)sub_head->freq / len;
            }
            else
            {
                freq = 1;
            }

            char str[8];
            sprintf(str, "%.6f", freq);
            removeZero(str);
            fprintf(file, "%ls,%s", sub_head->val, str);

            if (sub_head->next_p != NULL)
            {
                fprintf(file, ",");
            }

            sub_head = sub_head->next_p;
        }
        // fprintf(file, ")\n");
        fprintf(file, "\n");

        head = head->next_p;
    }
}

/*      Programma       */

void main_bigrammi(char *input_path, char *output_path)
{
    setlocale(LC_ALL, "");
    setlocale(LC_NUMERIC, "en_US.UTF-8");

    int pid1;
    int pid2;

    clock_t begin;
    clock_t end;

    nodo_t *lista_parole = NULL;
    Node_t *lista_bigrammi = NULL;

    FILE *input_file = open_file(input_path, "r");

    begin = clock();
    lista_parole = genera_lista(input_file);
    end = clock();
    printf("Genera Lista: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);
    printf("\nlen lista: %d parole\n", len(lista_parole));

    pid1 = fork();

    if (pid1 == 0)
    {
        begin = clock();
        lista_bigrammi = genera_bigrammi(lista_parole);
        end = clock();
        printf("Genera bigrammi: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);
        
        pid2 = fork();
        if (pid2 == 0)
        {
            FILE *output_file = open_file(output_path, "w+");
            begin = clock();
            genera_file(output_file, lista_bigrammi);
            end = clock();

            fclose(output_file);

            printf("Genera file: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);
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
//     main_bigrammi("../test/lotr.txt", "bigrammi.csv");
//     return 0;
// }