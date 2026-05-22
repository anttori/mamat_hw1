/* Welcome to Mamat, 044101
 *
 * Use this project as a template for other C/C++ projects.
 * To copy this project, right-click on the project name "hello-world"
 * in the "project explorer" tab (left), then "copy" and finally "paste".
 *
 * To compile the project use "gcc" within the terminal.
 * To debug the project use "gdb" within the terminal.
 *
 * The red vertical line (right) represents the code width limit (80 chars).
 * Make sure not to cross it. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy(FILE *input, FILE *output);
void error();

int main(int argc, char **argv) {
	FILE *input, *output;

	if (argc == 1) {
		input = stdin;
		output = stdout;
	} else {
		if(!strcmp("-", argv[1])) input = stdin;
		else input = fopen(argv[1], "r");
		if(!input) error();		// open input error

		if(argc < 3 || !strcmp("-", argv[2])) output = stdout;
		else output = fopen(argv[2], "w");
		if(!output) error();	// open output error
	}

	copy(input, output);

	// close opened files
	if(input != stdin) fclose(input);
	if(output != stdout) fclose(output);

	return 0;
}

void error() {
	fprintf(stderr, "Error occurred");
	exit(1);
}

void copy(FILE *input, FILE *output) {
	int current_char;

	while(1) {
		current_char = fgetc(input);
		if(current_char == EOF) {
			break; 	// finished
		}
		
		if( fputc(current_char, output) == EOF) error();		// write error
	}	

	if(ferror(input)) error();		// read error
}
