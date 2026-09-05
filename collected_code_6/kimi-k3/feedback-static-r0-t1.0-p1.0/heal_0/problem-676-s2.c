#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_non_alphanumeric(const char *input, char **output) {
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char *result;
    size_t result_len = 0;
    size_t input_len;
    int ret;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    input_len = strlen(input);

    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[A-Za-z0-9]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return -1;
    }

    cursor = input;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == 0) {
            if (match.rm_so != 0) {
                cursor += match.rm_so;
            }
            result[result_len++] = cursor[match.rm_eo - 1];
            cursor += match.rm_eo;
        } else if (ret == REG_NOMATCH) {
            break;
        } else {
            regfree(&regex);
            free(result);
            return -1;
        }
    }

    result[result_len] = '\0';
    regfree(&regex);
    *output = result;
    return 0;
}

int main(void) {
    const char *test_string = "Hello, World! 123 @#$";
    char *cleaned = NULL;

    if (remove_non_alphanumeric(test_string, &cleaned) == 0) {
        printf("Original: %s\n", test_string);
        printf("Cleaned:  %s\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}