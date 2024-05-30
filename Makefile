COMPILER = gcc
CFLAGS = -w

all:
	@echo "Specifica la versione del programma: 'make mono' o 'make multi'"

mono:
	$(COMPILER) $(CFLAGS) -o mono monoProcess/main.c
	@echo "Compilato monoProcess/main.c come mono"

multi:
	$(COMPILER) $(CFLAGS) -o multi multiProcess/main.c
	@echo "Compilato multiProcess/main.c come multi"