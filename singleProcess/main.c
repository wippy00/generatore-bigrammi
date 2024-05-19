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
    fprintf(stderr, "\t-o output file\n");
    fprintf(stderr, "\t-n (only for task: gen) number of words to generate\n");
    fprintf(stderr, "\t-w (only for task: gen) (optional) starting word for generate the new text\n");
    fprintf(stderr, "\nTask Type:\n");
    fprintf(stderr, "\t'scan' for scanning scan a txt file and receive a table with the frequencies of the words in the text\n");
    fprintf(stderr, "\t'gen' for generating a text with n words randomly chosen based on their frequency from the csv file\n");
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
    char *search_word = NULL;

    while ((options = getopt(argc, argv, "t:i:o:n:w:")) != -1)
    {
        switch (options)
        {
        case 't':
            task_name = optarg;
            if (strcmp(task_name, "scan") != 0 && strcmp(task_name, "gen") != 0)
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

    if (task_name == NULL || input_file == NULL || output_file == NULL)
    {
        usage(argv[0]);
    }

    // printf("Task: %s\n", task_name);
    // printf("Input file: %s\n", input_file);
    // printf("Output file: %s\n", output_file);

    // Eseguire il compito richiesto
    if (strcmp(task_name, "scan") == 0)
    {
        main_bigrammi(input_file, output_file);
    }

    if (strcmp(task_name, "gen") == 0)
    {
        if (number_words == NULL)
        {
            fprintf(stderr, "-n (only for task: gen) number of words to generate [is required]\n");
            return;
        }
        if (search_word == NULL)
        {
            // printf("\n\n parola-nulla: %s\n\n", search_word);
            main_generatore(input_file, number_words, L"", output_file);
        }
        else
        {
            // printf("\n\n parola-non nulla: %s\n\n", search_word);
            main_generatore(input_file, number_words, search_word, output_file);
        }
    }

    return 0;
}
