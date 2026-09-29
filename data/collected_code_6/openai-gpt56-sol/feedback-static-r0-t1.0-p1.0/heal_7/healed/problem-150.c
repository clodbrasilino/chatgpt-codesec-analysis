#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_in_sequence(unsigned long long number)
{
    return number != 0ULL && (number & (number - 1ULL)) == 0ULL;
}

int main(void)
{
    char input[256];
    char *start;
    char *end;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (start == end || errno == ERANGE) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    puts(is_in_sequence(number) ? "Present" : "Not present");

    return EXIT_SUCCESS;
}