#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <wchar.h>

#include "bigrammi.c"
#include "generatore.c"

void usage(const char *progname)
{
    fprintf(stderr, "Usage: main -t task [options]\n");
    fprintf(stderr, "\nBreve descrizione\n");
    fprintf(stderr, "\nCommands:\n");
    fprintf(stderr, "\t-t task\n");
    fprintf(stderr, "\t-i input file\n");
    fprintf(stderr, "\t-o [optional] output file; WARNING if omitted overwrites out.csv and/or text.txt\n");
    fprintf(stderr, "\t-n (for task: gen & craft) number of words to generate\n");
    fprintf(stderr, "\t-w [optional] (for task: gen & craft) starting word for generate the new text\n");
    fprintf(stderr, "\nTask Type:\n");
    fprintf(stderr, "\t'scan' for scanning scan a txt file and receive a table with the frequencies of the words in the text\n");
    fprintf(stderr, "\t'gen' for generating a text with n words randomly chosen based on their frequency from the csv file\n");
    fprintf(stderr, "\t'craft' combine gen and scan to create a frequency table and random text\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv[])
{
    int options;
    char *task_name = NULL;
    char *input_file = NULL;
    char *output_file = NULL;
    char *number_words = NULL;
    // wchar_t *search_word = NULL;
    wchar_t *search_word = NULL;

    while ((options = getopt(argc, argv, "t:i:o:n:w:")) != -1)
    {
        switch (options)
        {
        case 't':
            task_name = optarg;
            if (strcmp(task_name, "scan") != 0 && strcmp(task_name, "gen") != 0 && strcmp(task_name, "craft") != 0)
            {
                fprintf(stderr, "Invalid task name: %s\n", task_name);
                usage(argv[0]);
            }
            break;
        case 'i':
            input_file = optarg;
            break;
        case 'o':
            output_file = optarg;
            break;
        case 'n':
            number_words = optarg;
            break;
        case 'w':
            search_word = optarg;
            break;

        default:
            usage(argv[0]);
        }
    }

    if (task_name == NULL || input_file == NULL)
    {
        usage(argv[0]);
    }

    // printf("Task: %s\n", task_name);
    // printf("Input file: %s\n", input_file);
    // printf("Output file: %s\n", output_file);

    // Eseguire il compito richiesto
    if (strcmp(task_name, "scan") == 0)
    {
        /* se non viene fornito un nome del file di output verrà generato/sovrascritto il file out.csv */
        if (output_file == NULL)
        {
            char string[10];
            strcpy(string, "out.csv");
            output_file = &string;
        }
        main_bigrammi(input_file, output_file);
    }
    else if (strcmp(task_name, "gen") == 0)
    {
        if (number_words == NULL)
        {
            fprintf(stderr, "-n (for task: gen & craft) number of words to generate [is required]\n");
            return;
        }
        
        /* se non viene fornito un nome del file di output verrà generato/sovrascritto il file text.txt */
        if (output_file == NULL)
        {
            char string[10];
            strcpy(string, "text.txt");
            output_file = &string;
        }

        if (search_word == NULL)
        {
            // printf("\n\n parola-nulla: %s\n\n", search_word);
            main_generatore(input_file, number_words, L"", output_file);
            return;
        }
        else
        {
            wchar_t wchar[31];
            swprintf(wchar, 31, L"%hs", search_word);
            main_generatore(input_file, number_words, wchar, output_file);
            return;
        }
    }
    else if (strcmp(task_name, "craft") == 0)
    {
        
        if (number_words == NULL)
        {
            fprintf(stderr, "-n (for task: gen & craft) number of words to generate [is required]\n");
            return;
        }
        if (output_file == NULL)
        {
            char string[10];
            strcpy(string, "text.txt");
            output_file = &string;
        }
        
        main_bigrammi(input_file, "out.csv");
        
        if (search_word == NULL)
        {
            // printf("\n\n parola-nulla: %s\n\n", search_word);
            main_generatore("out.csv", number_words, L"", output_file);
            return;
        }
        else
        {
            wchar_t wchar[31];
            swprintf(wchar, 31, L"%hs", search_word);
            main_generatore("out.csv", number_words, wchar, output_file);
            return;
        }
    }

    return 0;
}
