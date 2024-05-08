#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
// #include <string.h>
#include <wchar.h>

#include "./lib/list.h"

#include <wctype.h>



/*
Error 01: Errore apertura file
Error 02:
Error 03:
*/


FILE * open_file(char path[32]){
    FILE *pointer_file = fopen("./testo.txt", "r");
    if (pointer_file == NULL)
    {
        printf("Path errata o file non corretto");
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
        if (character == ' '){
            parola[indice_parola] = '\0';

            append(&lista, parola);
            
            for (int i = 0; i < indice_parola; i++){
                parola[i] = '\0';
            }

            indice_parola = 0;
        }
        // appende come parola i caratteri di punteggiatura
        else if (character == '.' || character == '?' || character == '!'){
            parola[indice_parola] = '\0';

            append(&lista, parola);
            
            parola[0] = character;
            parola[1] = '\0';

            append(&lista, parola);
            
            for (int i = 0; i < indice_parola; i++){
                parola[i] = '\0';
            }

            indice_parola = 0;
            
        }
        // altrimenti appendi la lettera alla parola
        else if(iswalnum(character) || character == '\''){
            parola[indice_parola] = character;
            indice_parola ++;
        }
    }

    return lista;
}


int main() {
    setlocale(LC_ALL, "");
    
    char path[32] = "testo.txt";

    FILE *file = open_file(path);

    nodo_t *lista = genera_lista(file);


    printList(lista);
    return 0;
}