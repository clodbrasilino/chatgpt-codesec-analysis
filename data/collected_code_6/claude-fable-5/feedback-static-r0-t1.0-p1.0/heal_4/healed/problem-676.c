#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

char *remove_non_alphanumeric(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t input_len;
    size_t result_pos;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:alnum:]]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    result_pos = 0;
    cursor = input;

    while (*cursor != '\0') {
        size_t segment_len;
        size_t remaining;

        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret != 0) {
            break;
        }
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            break;
        }

        segment_len = (size_t)(match.rm_eo - match.rm_so);

        if (result_pos > input_len) {
            break;
        }
        remaining = input_len - result_pos;
        if (segment_len > remaining) {
            break;
        }

        memcpy(result + result_pos, cursor + match.rm_so, segment_len);
        result_pos += segment_len;
        cursor += match.rm_eo;
    }

    result[result_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "Hello, World! 123",
        "a@b#c$d%e^1&2*3",
        "!!!???...",
        "AlreadyClean123"
    };
    size_t count;
    size_t i;

    count = sizeof(test_strings) / sizeof(test_strings[0]);

    for (i = 0; i < count; i++) {
        char *cleaned = remove_non_alphanumeric(test_strings[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Failed to process string: %s\n",
                    test_strings[i]);
            return EXIT_FAILURE;
        }
        printf("Original: %s\nCleaned:  %s\n\n",
               test_strings[i], cleaned);
        free(cleaned);
    }

    return EXIT_SUCCESS;
}