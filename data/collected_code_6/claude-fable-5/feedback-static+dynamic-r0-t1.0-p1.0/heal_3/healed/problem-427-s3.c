#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DATE_BUFFER_SIZE 11

int convert_date(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t matches[4];
    int ret;
    int written;

    if (input == NULL || output == NULL || output_size < DATE_BUFFER_SIZE) {
        return -1;
    }

    ret = regcomp(&regex, "^([0-9]{4})-([0-9]{2})-([0-9]{2})$", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, input, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }

    written = snprintf(output, output_size, "%.*s-%.*s-%.*s",
                       (int)(matches[3].rm_eo - matches[3].rm_so),
                       input + matches[3].rm_so,
                       (int)(matches[2].rm_eo - matches[2].rm_so),
                       input + matches[2].rm_so,
                       (int)(matches[1].rm_eo - matches[1].rm_so),
                       input + matches[1].rm_so);

    regfree(&regex);

    if (written < 0 || (size_t)written >= output_size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *input = "2024-05-17";
    char *output;
    size_t output_size = DATE_BUFFER_SIZE;

    output = calloc(output_size, sizeof(char));
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (convert_date(input, output, output_size) != 0) {
        fprintf(stderr, "Failed to convert date: %s\n", input);
        free(output);
        return EXIT_FAILURE;
    }

    if (printf("Input:  %s\nOutput: %s\n", input, output) < 0) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}