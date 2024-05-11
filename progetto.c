#include <locale.h>
#include <stdlib.h>
#include <stdio.h>

#include <wchar.h>
#include <wctype.h>

#include "./lib/list.h"

/* # Test only */
#include <time.h>



/*
Error 01: Errore apertura file
Error 02:
Error 03:
*/


FILE * open_file(char path[32]){
    FILE *pointer_file = fopen(path, "r");
    if (pointer_file == NULL)
    {
        printf("Path errata o file non corretto 1\n");
        exit(1);
    }
    
    return pointer_file;
}

nodo_t * genera_lista(FILE *file){
    int indice_parola = 0;
    wchar_t character;
    wchar_t parola[31];
    for (int i = 0; i < 31; i++){
        parola[i] = '\0';
    }


    nodo_t *lista = NULL;   //DEVI INIZIALIZZARE A NULL


    while ((character = fgetwc(file)) != WEOF)
    {
        character = towlower(character);
        // se il carattere è uno spazio appendi la parola alla lista
        if ((character == ' ' || character == '\n') && indice_parola > 0){
            parola[indice_parola] = '\0';

            lavoratore_parole(parola);
            
            for (int i = 0; i < indice_parola; i++){
                parola[i] = '\0';
            }

            indice_parola = 0;
        }
        // appende come parola i caratteri di punteggiatura
        else if (character == '.' || character == '?' || character == '!'){
            parola[indice_parola] = '\0';

            lavoratore_parole(parola);
            
            parola[0] = character;
            parola[1] = '\0';

            lavoratore_parole(parola);
            
            for (int i = 0; i < indice_parola; i++){
                parola[i] = '\0';
            }

            indice_parola = 0;
            
        }
        // altrimenti appendi la lettera alla parola
        else if(iswalnum(character) || character == '\''){
           
            // se c'è una parola maggiore di 30 caratteri troncala
            if (indice_parola > 30){
                
                indice_parola = 0;                
                printf("%ls \n", parola);
            }

            parola[indice_parola] = character;
            indice_parola ++;
        }
    }
    // se rimane una parola nel buffer lo appende
    if (indice_parola > 0){
        
        parola[indice_parola] = '\0';
        indice_parola = 0;
        lavoratore_parole(parola);
    }

    return lista;
}


wchar_t temp[31];

nodo_t *LISTA = NULL;   //DEVI INIZIALIZZARE A NULL


void init(){
    for (int i = 0; i < 31; i++)
    {
        temp[i] = '\0';
    }
}

void lavoratore_parole(wchar_t parola[31])
{
    // if (temp[0] == '\0')
    // {
    //     wcscpy(temp, parola);
    //     return;
    // }

    // printf("%ls %ls \n", temp, parola);
    // temp[0] = '\0';
    // return;


    insert(&LISTA, parola);
    // printf("%ls \n", parola);
}



int main() {
    setlocale(LC_ALL, "");
    setlocale(LC_NUMERIC, "en_US.UTF-8");

    FILE *file = open_file("./test/10k.txt");

    clock_t begin = clock();

    nodo_t *lista = genera_lista(file);
    
    clock_t end = clock();
    printf("Elapsed: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);

    // printList(LISTA);
    return 0;
}