#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 65536

char *remove_multiple_spaces(const char *input);
static int safe_append(char *dest, size_t dest_size, size_t *dest_pos,
                       const char *src, size_t src_len);

static int safe_append(char *dest, size_t dest_size, size_t *dest_pos,
                       const char *src, size_t src_len)
{
    if (dest == NULL || dest_pos == NULL || src == NULL) {
        return -1;
    }
    if (src_len >= dest_size) {
        return -1;
    }
    if (*dest_pos >= dest_size - src_len) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest + *dest_pos, src, src_len);
    *dest_pos += src_len;
    return 0;
}

char *remove_multiple_spaces(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t input_len;
    size_t result_size;
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

    result_pos = 0;
    cursor = input;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == 0) {
            size_t chunk_len;

            if (match.rm_so < 0 || match.rm_eo < 0 ||
                match.rm_eo < match.rm_so) {
                free(result);
                regfree(&regex);
                return NULL;
            }

            chunk_len = (size_t)match.rm_so;

            if (safe_append(result, result_size, &result_pos,
                            cursor, chunk_len) != 0) {
                free(result);
                regfree(&regex);
                return NULL;
            }

            if (result_pos >= result_size - 1) {
                free(result);
                regfree(&regex);
                return NULL;
            }

            result[result_pos] = ' ';
            result_pos++;
            cursor += (size_t)match.rm_eo;
        } else if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(cursor, result_size);

            if (safe_append(result, result_size, &result_pos,
                            cursor, remaining) != 0) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            break;
        } else {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    if (result_pos >= result_size) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    result[result_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test = "Hello    world,   this  is    a     test.";
    char *cleaned;

    cleaned = remove_multiple_spaces(test);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", test) < 0) {
        free(cleaned);
        return EXIT_FAILURE;
    }
    if (printf("Cleaned:  %s\n", cleaned) < 0) {
        free(cleaned);
        return EXIT_FAILURE;
    }

    free(cleaned);
    return EXIT_SUCCESS;
}