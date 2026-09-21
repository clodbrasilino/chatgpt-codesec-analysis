#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_lowercase_substrings(const char *input, size_t input_len, char **output)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    const char *end;
    char *result;
    size_t result_len;
    size_t remaining;
    size_t copy_len;
    int ret;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    end = input + input_len;

    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return -1;
    }

    cursor = input;
    result_len = 0;

    while (cursor < end && *cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);

        if (ret == REG_NOMATCH) {
            remaining = (size_t)(end - cursor);
            copy_len = strnlen(cursor, remaining);
            if (result_len + copy_len > input_len) {
                regfree(&regex);
                free(result);
                return -1;
            }
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
            break;
        }

        if (ret != 0) {
            regfree(&regex);
            free(result);
            return -1;
        }

        copy_len = (size_t)match.rm_so;
        if (cursor + match.rm_eo > end || result_len + copy_len > input_len) {
            regfree(&regex);
            free(result);
            return -1;
        }

        memcpy(result + result_len, cursor, copy_len);
        result_len += copy_len;
        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);
    *output = result;

    return 0;
}

int main(void)
{
    const char *input = "HelloWorldABCdefGHIjklMNOP";
    char *output = NULL;

    if (remove_lowercase_substrings(input, strlen(input), &output) != 0) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", input);
    printf("Output: %s\n", output);

    free(output);

    return EXIT_SUCCESS;
}