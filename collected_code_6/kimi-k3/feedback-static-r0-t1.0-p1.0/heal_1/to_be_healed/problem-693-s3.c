#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_multiple_spaces(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char *result;
    size_t result_size;
    size_t input_len;
    size_t pos = 0;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strlen(input);
    if (input_len == 0) {
        result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    ret = regcomp(&regex, "  +", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result_size = input_len + 1;
    result = malloc(result_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t prefix_len = (size_t)match.rm_so;
        /* Possible weaknesses found:
         *  Value stored to 'match_len' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'match_len' is assigned a value that is never used. [unreadVariable]
         */
        size_t match_len = (size_t)(match.rm_eo - match.rm_so);

        if (pos + prefix_len + 2 > result_size) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        memcpy(result + pos, cursor, prefix_len);
        pos += prefix_len;

        result[pos++] = ' ';

        cursor += match.rm_eo;
    }

    {
        size_t remaining = strlen(cursor);
        if (pos + remaining + 1 > result_size) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + pos, cursor, remaining);
        pos += remaining;
    }

    result[pos] = '\0';

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_string = "This   is    a   test    string  with   multiple    spaces.";
    char *cleaned;

    cleaned = remove_multiple_spaces(test_string);
    if (cleaned == NULL) {
        fprintf(stderr, "Error: failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);
    return EXIT_SUCCESS;
}