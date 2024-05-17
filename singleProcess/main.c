#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "bigrammi.c"
#include "generatore.c"

void usage(const char *progname)
{
    fprintf(stderr, "Usage: -t task -i input -o output -n (only for task: gen) number of words to generate\n");
    fprintf(stderr, "Task: 'scan' for scanning scan a txt file and receive a table with the frequencies of the words in the text\n");
    fprintf(stderr, "Task: 'gen' for generating a text with n words randomly chosen based on their frequency from the csv file\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int options;
    char *task_name = NULL;
    char *input_file = NULL;
    char *output_file = NULL;
    char *number_words = NULL;
    char *search_words = NULL;


    while ((options = getopt(argc, argv, "t:i:o:n")) != -1)
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
        default:
            usage(argv[0]);
        }
    }

    if (task_name == NULL || input_file == NULL || output_file == NULL)
    {
        usage(argv[0]);
    }

    printf("Task: %s\n", task_name);
    printf("Input file: %s\n", input_file);
    printf("Output file: %s\n", output_file);

    // Eseguire il compito richiesto
    if (strcmp(task_name, "scan") == 0)
    {
        main_bigrammi(input_file, output_file);
    }
    else if (strcmp(task_name, "gen") == 0)
    {
        main_generatore(input_file, number_words, output_file);
    }

    return 0;
}
