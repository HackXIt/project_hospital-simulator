/* TEST.c
 *   by Nikolaus Rieder
 *
 * Created:
 *   4/18/2021, 3:08:47 PM
 * Last edited:
 *   4/18/2021, 3:29:13 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Test file for build-process & makefile
**/

/*--- COMMON LIBRARIES ---*/
#include <stdio.h>
#include <stdlib.h>
/*--- CUSTOM LIBRARIES ---*/
#include "test.h"
/*--- MACROS ---*/
#define DEBUG

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
        case WORD:
            printf("A word ");
            break;
        case VERB:
            printf("has a verb ");
            break;
        case ABC:
            printf("and object ABC ");
            break;
        case DEF:
            printf("and maybe object DEF.\n");
            break;
        default:
            printf("\nThere is nothing to say.");
            break;
        }
    }
    return EXIT_SUCCESS;
}
