#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int get_ascii_value(char c)
{
    return (int)(unsigned char)c;
}

static void flush_input(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        continue;
    }
}

int main(void)
{
    int input;

    printf("Enter a character: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error: failed to flush output\n");
        return EXIT_FAILURE;
    }

    input = getchar();
    if (input == EOF) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    if (input != '\n') {
        flush_input();
    }

    if (!isprint(input)) {
        fprintf(stderr, "Error: input is not a printable character\n");
        return EXIT_FAILURE;
    }

    printf("The ASCII value of '%c' is %d\n", (char)input, get_ascii_value((char)input));

    return EXIT_SUCCESS;
}