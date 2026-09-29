#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

char *remove_whitespace(const char *input);

char *remove_whitespace(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result = NULL;
    size_t result_len = 0;
    size_t input_len;
    size_t buffer_size;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    buffer_size = input_len + 1;
    result = malloc(buffer_size);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    cursor = input;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(cursor, MAX_INPUT_LEN);
            if (result_len > buffer_size - 1 ||
                remaining > (buffer_size - 1) - result_len) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            memcpy(result + result_len, cursor, remaining);
            result_len += remaining;
            break;
        } else if (ret != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        if (result_len > buffer_size - 1 ||
            (size_t)match.rm_so > (buffer_size - 1) - result_len) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        memcpy(result + result_len, cursor, (size_t)match.rm_so);
        result_len += (size_t)match.rm_so;
        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test = "  Hello \t World \n from  C  ";
    char *cleaned;

    cleaned = remove_whitespace(test);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to remove whitespace\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: \"%s\"\n", test) < 0) {
        free(cleaned);
        return EXIT_FAILURE;
    }

    if (printf("Cleaned:  \"%s\"\n", cleaned) < 0) {
        free(cleaned);
        return EXIT_FAILURE;
    }

    free(cleaned);
    return EXIT_SUCCESS;
}