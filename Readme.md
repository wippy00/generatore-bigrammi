# Bigrammi
## Introduzione

Questo progetto è uno strumento per l'analisi del testo. È progettato per elaborare del testo ed eseguire operazioni come l'analisi della frequenza delle parole e la generazione casuale di testo in base alle frequenze delle parole

## Compilazione

Utilizzare il Makefile e inserire "single" per compilare la versione con il processo singolo oppure "multi" pre la versione multiprocesso


## Utilizzo

Questo progetto include diverse attività che possono essere eseguite dalla riga di comando:

### Scan

L'attività "Scan" esegue la scansione di un file txt e genera una tabella con le frequenze delle parole nel testo. Per eseguire questa attività, utilizzare il comando seguente:

```sh
main -t scan -i input.txt [opzionale] -o output.csv
```
### Gen
L'attività 'gen' genera un testo con n parole scelte casualmente in base alla loro frequenza dal file CSV. Per eseguire questa attività, utilizzare il comando seguente:

```sh
main -t gen -i input.csv -n 100 [opzionale] -o output.txt [opzionale] -w parola
```

### Craft
L'attività "craft" combina "gen" e "scan" per creare una tabella di frequenza e un testo casuale. Per eseguire questa attività, utilizzare il comando seguente:

```sh
main -t craft -i input.txt -n 100  [opzionale] -o output.txt [opzionale] -w parola
```