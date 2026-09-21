#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

static int get_ascii_value(char c)
{
    return (int)(unsigned char)c;
}

static void flush_stdin(void)
{
    unsigned long guard = 0;
    int extra;

    while (guard < ULONG_MAX) {
        extra = getchar();
        if (extra == '\n' || extra == EOF) {
            break;
        }
        guard++;
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

    if (input < 0 || input > UCHAR_MAX) {
        fprintf(stderr, "Error: input out of valid character range\n");
        return EXIT_FAILURE;
    }

    if (input != '\n') {
        flush_stdin();
    }

    if (isprint((unsigned char)input)) {
        printf("The ASCII value of '%c' is %d\n", (char)input, get_ascii_value((char)input));
    } else {
        printf("The ASCII value of the entered character is %d\n", get_ascii_value((char)input));
    }

    return EXIT_SUCCESS;
}