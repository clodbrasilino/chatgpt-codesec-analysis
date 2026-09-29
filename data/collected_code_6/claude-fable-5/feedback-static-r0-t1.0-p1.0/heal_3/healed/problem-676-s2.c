#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

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
            if (remaining > len || pos > len - remaining) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            memcpy(result + pos, cursor, remaining);
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
        if ((size_t)match.rm_so > len || pos > len - (size_t)match.rm_so) {
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
        memcpy(result + pos, cursor, (size_t)match.rm_so);
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