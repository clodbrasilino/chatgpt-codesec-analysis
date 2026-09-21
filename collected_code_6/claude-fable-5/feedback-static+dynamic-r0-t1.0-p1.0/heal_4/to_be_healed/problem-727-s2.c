#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

static int safe_copy(char *dst, size_t dst_size, size_t pos,
                     const char *src, size_t copy_len)
{
    if (dst == NULL || src == NULL) {
        return -1;
    }
    if (copy_len > dst_size) {
        return -1;
    }
    if (pos > dst_size - copy_len) {
        return -1;
    }
    if (pos + copy_len >= dst_size) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst + pos, src, copy_len);
    return 0;
}

char *remove_non_alnum(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t len;
    size_t pos;
    size_t offset;
    size_t alloc_size;
    size_t copy_len;
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
            copy_len = len - offset;
            if (safe_copy(result, alloc_size, pos, input + offset, copy_len) != 0) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            pos += copy_len;
            break;
        }
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        copy_len = (size_t)match.rm_so;
        if (copy_len > len - offset) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (safe_copy(result, alloc_size, pos, input + offset, copy_len) != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        pos += copy_len;
        if ((size_t)match.rm_eo > len - offset) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        offset += (size_t)match.rm_eo;
    }

    if (pos >= alloc_size) {
        free(result);
        regfree(&regex);
        return NULL;
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