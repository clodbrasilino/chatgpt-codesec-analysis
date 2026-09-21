#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int month_has_28_days(int month)
{
    return month == 2;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    long month;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    } else if (!feof(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    month = strtol(input, &end, 10);

    if (errno == ERANGE || end == input || month < 1 || month > 12) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    puts(month_has_28_days((int)month) ? "Yes" : "No");

    free(input);
    return EXIT_SUCCESS;
}