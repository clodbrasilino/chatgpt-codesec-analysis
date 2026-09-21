#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int convert_date(const char *input, char *output, size_t output_size)
{
    const char *pattern = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    regex_t regex;
    regmatch_t matches[4];
    int result;

    if (input == NULL || output == NULL || output_size == 0U) {
        return -1;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, input, 4U, matches, 0);
    if (result != 0) {
        regfree(&regex);
        return -1;
    }

    result = snprintf(
        output,
        output_size,
        "%.*s-%.*s-%.*s",
        (int)(matches[3].rm_eo - matches[3].rm_so),
        input + matches[3].rm_so,
        (int)(matches[2].rm_eo - matches[2].rm_so),
        input + matches[2].rm_so,
        (int)(matches[1].rm_eo - matches[1].rm_so),
        input + matches[1].rm_so
    );

    regfree(&regex);

    if (result < 0 || (size_t)result >= output_size) {
        return -1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char converted[11];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s yyyy-mm-dd\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (convert_date(argv[1], converted, sizeof(converted)) != 0) {
        fprintf(stderr, "Invalid date format\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", converted) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}