#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_difference_of_two_squares(intmax_t number)
{
    intmax_t remainder = number % 4;
    return remainder != 2 && remainder != -2;
}

static bool read_number(intmax_t *number)
{
    if (number == NULL) {
        return false;
    }

    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return false;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
    } else if (!feof(stdin)) {
        free(line);
        return false;
    }

    char *end = NULL;
    errno = 0;
    intmax_t value = strtoimax(line, &end, 10);

    if (errno == ERANGE || end == line) {
        free(line);
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return false;
    }

    *number = value;
    free(line);
    return true;
}

int main(void)
{
    intmax_t number;

    if (!read_number(&number)) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n",
               is_difference_of_two_squares(number) ? "Yes" : "No") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}