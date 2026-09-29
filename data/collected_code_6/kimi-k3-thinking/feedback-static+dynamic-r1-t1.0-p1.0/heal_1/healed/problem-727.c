#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 4096

char *remove_non_alphanumeric(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    char *work;
    size_t result_len = 0;
    size_t input_len;
    size_t remaining;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LENGTH);

    work = malloc(input_len + 1);
    if (work == NULL) {
        return NULL;
    }
    memcpy(work, input, input_len);
    work[input_len] = '\0';

    result = malloc(input_len + 1);
    if (result == NULL) {
        free(work);
        return NULL;
    }

    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        free(work);
        free(result);
        return NULL;
    }

    cursor = work;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            remaining = input_len - (size_t)(cursor - work);
            if (remaining > input_len - result_len) {
                regfree(&regex);
                free(work);
                free(result);
                return NULL;
            }
            memcpy(result + result_len, cursor, remaining);
            result_len += remaining;
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            free(work);
            free(result);
            return NULL;
        }

        if (match.rm_so > 0) {
            if ((size_t)match.rm_so > input_len - result_len) {
                regfree(&regex);
                free(work);
                free(result);
                return NULL;
            }
            memcpy(result + result_len, cursor, (size_t)match.rm_so);
            result_len += (size_t)match.rm_so;
        }
        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);
    free(work);
    return result;
}

int main(void)
{
    const char *test = "Hello, World! 123 @#$% C-Programming_2024";
    char *cleaned = remove_non_alphanumeric(test);

    if (cleaned == NULL) {
        fprintf(stderr, "Error: string processing failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);
    return EXIT_SUCCESS;
}