#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

static int safe_copy(char *dest, size_t dest_size, size_t dest_off,
                     const char *src, size_t count)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (dest_off >= dest_size) {
        return -1;
    }
    if (count > dest_size - dest_off) {
        return -1;
    }
    memmove(dest + dest_off, src, count);
    return 0;
}

char *remove_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t len;
    size_t pos;
    size_t out;
    size_t buf_size;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    buf_size = len + 1;
    result = malloc(buf_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    pos = 0;
    out = 0;
    while (pos <= len) {
        ret = regexec(&regex, input + pos, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = len - pos;
            if (safe_copy(result, buf_size, out, input + pos, remaining) != 0) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            out += remaining;
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
        if ((size_t)match.rm_eo > len - pos) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (safe_copy(result, buf_size, out, input + pos,
                      (size_t)match.rm_so) != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        out += (size_t)match.rm_so;
        pos += (size_t)match.rm_eo;
        if (match.rm_eo == match.rm_so) {
            break;
        }
    }

    if (out >= buf_size) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    result[out] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test = "HelloWORLDthisISaTEST";
    char *cleaned;

    cleaned = remove_uppercase(test);
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