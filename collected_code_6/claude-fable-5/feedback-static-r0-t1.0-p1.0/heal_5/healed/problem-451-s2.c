#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

char *remove_whitespace(const char *input);
static int safe_append(char *dest, size_t dest_cap, size_t *dest_len,
                       const char *src, size_t src_len);

static int safe_append(char *dest, size_t dest_cap, size_t *dest_len,
                       const char *src, size_t src_len)
{
    size_t i;

    if (dest == NULL || dest_len == NULL || src == NULL) {
        return -1;
    }

    if (dest_cap == 0 || *dest_len > dest_cap - 1) {
        return -1;
    }

    if (src_len > (dest_cap - 1) - *dest_len) {
        return -1;
    }

    for (i = 0; i < src_len; i++) {
        dest[*dest_len + i] = src[i];
    }

    *dest_len += src_len;
    return 0;
}

char *remove_whitespace(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result = NULL;
    size_t result_len = 0;
    size_t result_cap;
    size_t input_len;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result_cap = input_len + 1;
    result = malloc(result_cap);
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
            size_t offset = (size_t)(cursor - input);
            size_t remaining;

            if (offset > input_len) {
                regfree(&regex);
                free(result);
                return NULL;
            }

            remaining = strnlen(cursor, input_len - offset);

            if (safe_append(result, result_cap, &result_len,
                            cursor, remaining) != 0) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            break;
        } else if (ret != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        if (match.rm_so < 0 || match.rm_eo <= 0 ||
            match.rm_so > match.rm_eo ||
            (size_t)(cursor - input) > input_len ||
            (size_t)match.rm_eo > input_len - (size_t)(cursor - input)) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        if (safe_append(result, result_cap, &result_len,
                        cursor, (size_t)match.rm_so) != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        cursor += match.rm_eo;
    }

    if (result_len >= result_cap) {
        regfree(&regex);
        free(result);
        return NULL;
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