#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

enum { CONVERTED_DATE_SIZE = 11 };

static int convert_date(const char *input, char *output, size_t output_size)
{
    static const char pattern[] = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    regex_t regex;
    regmatch_t matches[4];
    int result;

    if (input == NULL || output == NULL ||
        output_size < (size_t)CONVERTED_DATE_SIZE) {
        return -1;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, input, 4, matches, 0);
    if (result != 0) {
        regfree(&regex);
        return -1;
    }

    result = snprintf(output, output_size, "%.2s-%.2s-%.4s",
                      input + matches[3].rm_so,
                      input + matches[2].rm_so,
                      input + matches[1].rm_so);

    regfree(&regex);

    if (result != CONVERTED_DATE_SIZE - 1) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *converted;

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s yyyy-mm-dd\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    converted = malloc(CONVERTED_DATE_SIZE);
    if (converted == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (convert_date(argv[1], converted, CONVERTED_DATE_SIZE) != 0) {
        fprintf(stderr, "Invalid date format\n");
        free(converted);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", converted) < 0) {
        free(converted);
        return EXIT_FAILURE;
    }

    free(converted);
    return EXIT_SUCCESS;
}