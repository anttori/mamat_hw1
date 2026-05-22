#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*returns 1 if line matches somewhere in line the regex
0 otherwise, uses matchhere*/
int match(char *text, char *regexp);

/*returns 1 if line matches  the regex at the start of the line
0 otherwise, uses matchstar*/
int matchhere(char *text, char *regexp);

/*returns 1 if start of the line is c*regex
0 otherwise, */
int matchstar(char *text, char c, char *regexp);


// CONTAINS BUG
/*
#define BUFSIZE 256
int main(int argc, char *argv[])
{
    FILE *f = stdin;
    char *buffer = malloc(sizeof(char) * BUFSIZE);

    if (!(argv[1][0] == '-' && argv[1][1] == '\0'))
        f = fopen(argv[1], "r");

    while (1)
    {
        buffer = fgets(buffer, BUFSIZE, f);
        if (buffer == NULL)
        {
            break;
        }
        else
        {
            for (int i=0; i < BUFSIZE; i++)
            {
                if (buffer[i] == '\n')
                {
                    buffer[i] = '\0';
                    break;
                }
            }
        }
        if (match(buffer, argv[2]))
            printf("%s\n",buffer);
    }
    if (f != stdin) fclose(f);
}
*/

// GEMINI BUG FIX
#define BUFSIZE 256

int main(int argc, char *argv[]) {
    FILE *f = stdin;
    char buffer[BUFSIZE];

    if (strcmp(argv[1], "-") != 0)
    {
        f = fopen(argv[1], "r");
    }

    while (fgets(buffer, BUFSIZE, f) != NULL)
    {
        for (int i = 0; i < BUFSIZE && buffer[i] != '\0'; i++)
        {
            if (buffer[i] == '\n')
            {
                buffer[i] = '\0';
                break;
            }
        }

        if (match(buffer, argv[2]))
        {
            printf("%s\n", buffer);
        }
    }

    if (f != stdin)
    {
        fclose(f);
    }

    return 0;
}

int match(char *text, char *regexp) {
    if (regexp[0] == '^')
        return matchhere(text,regexp+1);

    char *temp_line_pointer= text;

    // CONTAINS BUG - FIXED BY GEMINI
    /*
    while(temp_line_pointer[0]!='\0'){

        if(matchhere(temp_line_pointer,regexp))	return 1;

        temp_line_pointer++;
    }
    */

    // GEMINI BUG FIX
    do {
    	if(matchhere(temp_line_pointer, regexp)) return 1;

    } while (*temp_line_pointer++ != '\0');

    return 0;

}

int matchhere(char *text, char *regexp) {

	if(regexp[0] == '\0') return 1;

	if(regexp[0] == '$' && regexp[1] == '\0') {
		return (text[0] == '\0');
	}

	if(regexp[1] == '*') {
		return matchstar(text, regexp[0], regexp + 2);
	}

	if(text[0] != '\0' && (regexp[0] == '.' || regexp[0] == text[0]) ) {
		return matchhere(text + 1, regexp + 1);
	}

	return 0;
}

int matchstar(char *text, char c, char* regexp) {

	do {

		if(matchhere(text, regexp)) return 1;

	} while(*text != '\0' && (*text++ == c || c == '.'));

	return 0;
}
