#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

static int safe_append(char *dest, size_t dest_size, size_t *pos,
                       const char *src, size_t chunk)
{
    if (dest == NULL || pos == NULL || src == NULL) {
        return -1;
    }
    if (chunk >= dest_size || *pos >= dest_size) {
        return -1;
    }
    if (*pos > dest_size - 1 - chunk) {
        return -1;
    }
    memcpy(dest + *pos, src, chunk);
    *pos += chunk;
    return 0;
}

char *remove_non_alnum(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t len;
    size_t pos;
    size_t chunk;
    size_t remaining;
    size_t result_size;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result_size = len + 1;
    result = malloc(result_size);
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
            remaining = len - (size_t)(cursor - input);
            chunk = strnlen(cursor, remaining);
            if (safe_append(result, result_size, &pos, cursor, chunk) != 0) {
                regfree(&regex);
                free(result);
                return NULL;
            }
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
        chunk = (size_t)match.rm_so;
        if (safe_append(result, result_size, &pos, cursor, chunk) != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        if ((size_t)match.rm_eo == 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        cursor += match.rm_eo;
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