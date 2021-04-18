/* MAIN.c
 *   by Nikolaus Rieder, Stefan Bittgen, Eva Grabler
 *
 * Created:
 *   4/18/2021, 7:26:45 PM
 * Last edited:
 *   4/18/2021, 7:30:21 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Main execution of the project
**/

/*--- COMMON LIBRARIES ---*/

/*--- CUSTOM LIBRARIES ---*/
#include "hospital_structures.h"
#include "persons.h"
/*--- MACROS ---*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    ListPersons_t activePersons = createListPersons();
    return 0;
}