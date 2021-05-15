/* MAIN.c
 *   by Nikolaus Rieder, Stefan Bittgen, Eva Grabler
 * Description:
 *   Main execution of the project
**/

/*--- COMMON LIBRARIES ---*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // getopt(3)
/*--- CUSTOM LIBRARIES ---*/
#include "hospital_structures.h"
#include "seat_rows.h"
/*--- MACROS ---*/

void print_help();
int main(int argc, char const *argv[])
{
	if (argc == 1) // Program is executed normally in GUI-Mode (no parameters given)
	{
		// NOTE GTK-Main-Function is executed here
	}
	else if (argc > 1) // Program is executed in CLI-Mode (parameters exist)
	{
		int opt;
		char *valid_options = "b:hp:t:"; // NOTE Please retain the order of the options alphabetically
		/* NOTE Valid options for CLI-Execution:
		b = binary | Read from provided binary to export it into output-file
		h = help | Print help message for program execution
		p = patients | List of patients to be used in automatic execution
		t = test | Test program execution with given testcase automatically (requires option 'p')
		*/
		bool p_given = FALSE;
		bool t_given = FALSE;
		while ((opt = getopt(argc, argv, valid_options))) // Parse parameters
		{
			switch (opt) // NOTE Please retain the order of this switch-statement alphabetically
			{
			case 'b':
				// TODO Parse argument of b
				break;
			case 'h':
				print_help(argv[0]);
				break;
			case 'p':
				p_given = TRUE;
				// TODO Parse argument of p
				break;
			case 't':
				t_given = TRUE;
				// TODO Parse argument of t
				break;
			default:
				fprintf(stderr, "Non-valid option given.\n");
				break;
			}
		}
	}

	// Possible example of Person-List-creation: ListPersons_t activePersons = createListPersons();
	// ^ Will be executed 2 times to generate an active Persons-List and an inactive Persons-List
	// Possible example of Row-List-creation: ListRows_t row1 = createListRow();
	// ^ Will be executed 5 times to generate 5 rows.

	return EXIT_SUCCESS;
}

void print_help(char *const argzero)
{
	// TODO proper help message, currently just placeholer
	printf("%s [OPTIONS]... [WORDS]...\n", argzero);
	printf("Hello World!\n");
}