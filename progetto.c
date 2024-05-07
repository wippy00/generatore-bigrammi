#include <stdio.h>
#include <string.h>
#include "./lib/list.h"

#include <ctype.h> 



/*
Error 01: Errore apertura file
Error 02:
Error 03:
*/


FILE * open_file(path){
    FILE *pointer_file = fopen("./testo.txt", "r");
    if (pointer_file == NULL)
    {
        printf("Path errata o file non corretto");
        exit(1);
    }
    
    return pointer_file;
}

Nodo * genera_lista(FILE *file){
    int ascii;
    int indice_parola = 0;
    char character;
    char parola[30];

    Nodo *lista;

    while ((ascii = fgetc(file)) != EOF)
    {
        character = tolower((char) ascii);

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
        else if(isalpha(ascii)){
            parola[indice_parola] = character;
            indice_parola ++;
        }
    }

    return lista;
}


int main() {

    char path[32] = "testo.txt";

    FILE *file = open_file(path);

    Nodo *lista = genera_lista(file);


    printList(lista);
    return 0;
}