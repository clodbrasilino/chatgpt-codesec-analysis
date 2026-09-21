#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

static int safe_copy(char *dest, size_t dest_size, size_t pos,
                     const char *src, size_t count)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (pos > dest_size || count > dest_size - pos) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest + pos, src, count);
    return 0;
}

char *remove_non_alnum(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t len;
    size_t pos;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[^[:alnum:]]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    pos = 0;
    cursor = input;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t offset = (size_t)(cursor - input);
            size_t remaining;

            if (offset > len) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            remaining = strnlen(cursor, len - offset);
            if (safe_copy(result, len, pos, cursor, remaining) != 0) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            pos += remaining;
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        if ((size_t)(cursor - input) > len ||
            (size_t)match.rm_eo > len - (size_t)(cursor - input)) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        if (safe_copy(result, len, pos, cursor, (size_t)match.rm_so) != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        pos += (size_t)match.rm_so;
        cursor += match.rm_eo;
    }

    if (pos > len) {
        regfree(&regex);
        free(result);
        return NULL;
    }

    result[pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test = "Hello, World! 123 @#$ abc_def";
    char *cleaned;

    cleaned = remove_non_alnum(test);
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