#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_uppercase_substrings(const char *input, char **output)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t input_length;
    size_t source_offset = 0;
    size_t destination_offset = 0;
    int status;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    input_length = strlen(input);

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    status = regcomp(&regex, "[[:upper:]]+", REG_EXTENDED);
    if (status != 0) {
        free(result);
        return -1;
    }

    while (source_offset < input_length) {
        size_t remaining = input_length - source_offset;

        status = regexec(&regex, input + source_offset, 1, &match, 0);

        if (status == REG_NOMATCH) {
            memcpy(result + destination_offset,
                   input + source_offset,
                   remaining);
            destination_offset += remaining;
            break;
        }

        if (status != 0 ||
            match.rm_so < 0 ||
            match.rm_eo <= match.rm_so ||
            (size_t)match.rm_eo > remaining) {
            regfree(&regex);
            free(result);
            return -1;
        }

        memcpy(result + destination_offset,
               input + source_offset,
               (size_t)match.rm_so);
        destination_offset += (size_t)match.rm_so;
        source_offset += (size_t)match.rm_eo;
    }

    result[destination_offset] = '\0';
    regfree(&regex);
    *output = result;

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *result = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (remove_uppercase_substrings(argv[1], &result) != 0) {
        fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}