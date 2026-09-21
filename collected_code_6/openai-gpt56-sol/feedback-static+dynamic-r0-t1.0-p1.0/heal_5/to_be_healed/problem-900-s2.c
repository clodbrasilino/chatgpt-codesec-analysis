#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strncmp'
  */

static bool starts_with_number(const char *string, long number)
{
    int required;
    char *prefix;
    bool result;

    if (string == NULL || number < 0) {
        return false;
    }

    required = snprintf(NULL, 0, "%ld", number);
    if (required < 0) {
        return false;
    }

    prefix = malloc((size_t)required + 1);
    if (prefix == NULL) {
        return false;
    }

    if (snprintf(prefix, (size_t)required + 1, "%ld", number) != required) {
        free(prefix);
        return false;
    }

    /* Possible weaknesses found:
     *  call to undeclared library function 'strncmp' with type 'int (const char *, const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strncmp' [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strncmp'
     */
    result = strncmp(string, prefix, (size_t)required) == 0;
    free(prefix);

    return result;
}

int main(int argc, char *argv[])
{
    char *end;
    long number;

    if (argc != 3) {
        const char *program =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <number> <string>\n", program);
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL || argv[2] == NULL) {
        fputs("Invalid arguments\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || number < 0) {
        fputs("Invalid non-negative number\n", stderr);
        return EXIT_FAILURE;
    }

    if (starts_with_number(argv[2], number)) {
        puts("The string starts with the specified number.");
    } else {
        puts("The string does not start with the specified number.");
    }

    return EXIT_SUCCESS;
}