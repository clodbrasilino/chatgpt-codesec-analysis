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
    size_t offset;
    size_t alloc_size;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[^a-zA-Z0-9]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        regfree(&regex);
        return NULL;
    }

    alloc_size = len + 1;
    result = malloc(alloc_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    pos = 0;
    offset = 0;

    while (offset < len) {
        ret = regexec(&regex, input + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = len - offset;
            if (pos + remaining >= alloc_size) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + pos, input + offset, remaining);
            pos += remaining;
            break;
        }
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (pos + (size_t)match.rm_so >= alloc_size) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + pos, input + offset, (size_t)match.rm_so);
        pos += (size_t)match.rm_so;
        if ((size_t)match.rm_eo > len - offset) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        offset += (size_t)match.rm_eo;
    }

    result[pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test = "Hello, World! 123 #$% Test_456";
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