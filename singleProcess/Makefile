COMPILER = gcc
CFLAGS = -Wall -Wextra -O2 -w

all:
    @echo "Specifica la versione del programma: 'make single' o 'make multi'"

single: p_singolo
p_singolo: processoSingolo.c
    $(COMPILER) $(CFLAGS) -o main_single singleProcess/main.c
    @echo "Compilato singleProcess/main.c come main_single"


multi: p_multi
p_multi: processoMultiplo.c
    $(COMPILER) $(CFLAGS) -o main_multi multiProcess/main.c
    @echo "Compilato multiProcess/main.c come main_multi"