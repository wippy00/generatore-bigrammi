#include <locale.h>
#include <stdlib.h>
#include <stdio.h>

#include <wchar.h>
#include <wctype.h>

#include "../lib/list.h"
#include "../lib/sublist.h"
#include "../lib/utils.h"

/* # Test only */
#include <time.h>

/*
Error 01: Errore apertura file
Error 02:
Error 03:
*/


/*      Funzioni Programma       */

{
    SubNode_t *sub_head = NULL;
    float freq = 0;
    int len = 0;

    while (head != NULL)
    {
        fprintf(file, "%ls", head->val);

        // Stampiamo la sottolista, se presente
        if (head->inner_p != NULL)
        {
            SubNode_t *sub_head = head->inner_p;
            // fprintf(file, "  (");
            fprintf(file, ",");
            len = sb_innerlen(sub_head);
            while (sub_head != NULL)
            {
                if (len > 1)
                {
                    freq = (float) sub_head->freq / len;
                }
                else
                {
                    freq = 1;
                }

                fprintf(file, "%ls,%.4g", sub_head->val, freq);
                // fprintf(file, "%ls,%.0f", sub_head->val, sub_head->freq);
                if (sub_head->next_p != NULL)
                {
                    // fprintf(file, " - ");
                    fprintf(file, ",");
                }
            
                sub_head = sub_head->next_p;
            }

            // fprintf(file, ")\n");
            fprintf(file, "\n");
        }
        head = head->next_p;
    }
}

/*      Programma       */

int main()
{
    setlocale(LC_ALL, "");
    setlocale(LC_NUMERIC, "en_US.UTF-8");
    return 0;
}