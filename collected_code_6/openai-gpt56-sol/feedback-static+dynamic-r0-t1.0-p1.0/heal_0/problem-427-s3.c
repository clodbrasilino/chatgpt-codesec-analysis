#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DATE_INPUT_SIZE 128
#define DATE_OUTPUT_SIZE 11

static int convert_date(const char *input, char *output, size_t output_size)
{
    static const char pattern[] = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    regex_t regex;
    regmatch_t matches[4];
    int result;

    if (input == NULL || output == NULL || output_size < DATE_OUTPUT_SIZE) {
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

int main(void)
{
    char input[DATE_INPUT_SIZE];
    char output[DATE_OUTPUT_SIZE];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Failed to read the date.\n", stderr);
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\r\n")] = '\0';

    if (convert_date(input, output, sizeof(output)) != 0) {
        fputs("Invalid date format.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", output) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}