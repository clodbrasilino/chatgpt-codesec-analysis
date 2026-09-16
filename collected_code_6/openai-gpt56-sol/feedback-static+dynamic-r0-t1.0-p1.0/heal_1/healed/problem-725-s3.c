#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int extract_quoted_values(const char *input)
{
    regex_t regex;
    regmatch_t matches[2];
    const char *cursor;
    int count = 0;
    int result;

    if (input == NULL) {
        return -1;
    }

    result = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    cursor = input;

    while ((result = regexec(&regex, cursor, 2, matches, 0)) == 0) {
        size_t length;
        char *value;

        if (matches[1].rm_so < 0 ||
            matches[1].rm_eo < matches[1].rm_so ||
            matches[0].rm_eo <= 0) {
            regfree(&regex);
            return -1;
        }

        length = (size_t)(matches[1].rm_eo - matches[1].rm_so);

        if (length == SIZE_MAX) {
            regfree(&regex);
            return -1;
        }

        value = malloc(length + 1);
        if (value == NULL) {
            regfree(&regex);
            return -1;
        }

        memcpy(value, cursor + matches[1].rm_so, length);
        value[length] = '\0';

        if (printf("%s\n", value) < 0) {
            free(value);
            regfree(&regex);
            return -1;
        }

        free(value);
        cursor += matches[0].rm_eo;
        count++;
    }

    regfree(&regex);

    if (result != REG_NOMATCH) {
        return -1;
    }

    return count;
}

int main(int argc, char *const argv[])
{
    int count;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    count = extract_quoted_values(argv[1]);
    if (count < 0) {
        if (fprintf(stderr, "Failed to extract quoted values\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}