#import "./bilist.h"



int main(){
    nodo_t *testa = NULL;
    nodo_t *coda = NULL;

    
    insert(&testa, L"mario");
    insert(&testa, L"gino");
    insert(&testa, L"pino");
    insert(&testa, L"luppolo");

    coda = getTail(testa);

    printList(testa);

    printReverseList(coda);
    
    return 0;
}