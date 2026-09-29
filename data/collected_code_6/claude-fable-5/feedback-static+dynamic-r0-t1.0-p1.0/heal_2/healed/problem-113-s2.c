#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define BUFFER_SIZE 256

int is_integer(const char *str)
{
    char *endptr;
    long value;

    if (str == NULL) {
        return 0;
    }

    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') {
        return 0;
    }

    errno = 0;
    value = strtol(str, &endptr, 10);

    if (errno == ERANGE) {
        return 0;
    }

    if (endptr == str) {
        return 0;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return 0;
    }

    (void)value;
    return 1;
}

static void flush_stdin(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        ;
    }
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t len;

    printf("Enter a string: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strcspn(buffer, "\n");

    if (buffer[len] == '\0' && len == sizeof(buffer) - 1) {
        fprintf(stderr, "Input too long: maximum %zu characters allowed\n",
                sizeof(buffer) - 2);
        flush_stdin();
        return EXIT_FAILURE;
    }

    buffer[len] = '\0';

    if (is_integer(buffer)) {
        printf("\"%s\" is a valid integer\n", buffer);
    } else {
        printf("\"%s\" is not a valid integer\n", buffer);
    }

    return EXIT_SUCCESS;
}