#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

enum { DATE_BUFFER_SIZE = sizeof("dd-mm-yyyy"), MATCH_COUNT = 4 };

static int convert_date(const char *input, char *output, size_t output_size)
{
    static const char pattern[] = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    regex_t regex;
    regmatch_t matches[MATCH_COUNT];
    int result;

    if (input == NULL || output == NULL || output_size < DATE_BUFFER_SIZE) {
        return -1;
    }

    output[0] = '\0';

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, input, MATCH_COUNT, matches, 0);
    if (result != 0) {
        regfree(&regex);
        return -1;
    }

    result = snprintf(output,
                      output_size,
                      "%.*s-%.*s-%.*s",
                      (int)(matches[3].rm_eo - matches[3].rm_so),
                      input + matches[3].rm_so,
                      (int)(matches[2].rm_eo - matches[2].rm_so),
                      input + matches[2].rm_so,
                      (int)(matches[1].rm_eo - matches[1].rm_so),
                      input + matches[1].rm_so);

    regfree(&regex);

    if (result < 0 || (size_t)result >= output_size) {
        output[0] = '\0';
        return -1;
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char converted[DATE_BUFFER_SIZE];

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "convert_date";

        fprintf(stderr, "Usage: %s yyyy-mm-dd\n", program_name);
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