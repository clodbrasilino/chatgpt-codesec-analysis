#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strncmp'
  */

static bool string_starts_with_number(const char *string, long number)
{
    int required_length;
    char *prefix;
    bool matches;

    if (string == NULL) {
        return false;
    }

    required_length = snprintf(NULL, 0, "%ld", number);
    if (required_length < 0) {
        return false;
    }

    prefix = malloc((size_t)required_length + 1U);
    if (prefix == NULL) {
        return false;
    }

    if (snprintf(prefix, (size_t)required_length + 1U, "%ld", number) !=
        required_length) {
        free(prefix);
        return false;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strncmp' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strncmp' with type 'int (const char *, const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strncmp'
     */
    matches = strncmp(string, prefix, (size_t)required_length) == 0;
    free(prefix);

    return matches;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end;
    long number;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    number = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || end == NULL || *end != '\0') {
        fputs("Invalid number\n", stderr);
        return EXIT_FAILURE;
    }

    if (string_starts_with_number(argv[2], number)) {
        puts("The string starts with the specified number.");
    } else {
        puts("The string does not start with the specified number.");
    }

    return EXIT_SUCCESS;
}