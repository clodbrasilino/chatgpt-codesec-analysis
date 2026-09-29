#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int month_has_28_days(int month)
{
    return month == 2;
}

int main(void)
{
    char input[64];
    char *end;
    char *newline;
    long month;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    newline = strchr(input, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else if (!feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    month = strtol(input, &end, 10);

    if (errno == ERANGE || end == input || month < 1 || month > 12) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(month_has_28_days((int)month) ? "Yes" : "No");

    return EXIT_SUCCESS;
}