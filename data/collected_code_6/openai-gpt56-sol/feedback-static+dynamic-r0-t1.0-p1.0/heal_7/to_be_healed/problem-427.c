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
int main(int argc, char *const argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char converted[CONVERTED_DATE_SIZE];

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s yyyy-mm-dd\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (convert_date(argv[1], converted, sizeof converted) != 0) {
        fprintf(stderr, "Invalid date format\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", converted) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}