#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

static int safe_copy(char *dest, size_t dest_size, size_t dest_pos,
                     const char *src, size_t count)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (count == 0) {
        return 0;
    }
    if (dest_pos >= dest_size) {
        return -1;
    }
    if (count > dest_size - dest_pos) {
        return -1;
    }
    memcpy(dest + dest_pos, src, count);
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
    size_t result_size;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    ret = regcomp(&regex, "[^a-zA-Z0-9]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result_size = len + 1;
    result = malloc(result_size);
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
            if (remaining > len ||
                pos > len - remaining ||
                pos + remaining >= result_size ||
                safe_copy(result, result_size, pos,
                          input + offset, remaining) != 0) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            pos += remaining;
            break;
        }
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (match.rm_so < 0 || match.rm_eo <= 0 ||
            match.rm_so > match.rm_eo ||
            (size_t)match.rm_eo > len - offset ||
            (size_t)match.rm_so > len - offset ||
            pos > len - (size_t)match.rm_so ||
            pos + (size_t)match.rm_so >= result_size) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (safe_copy(result, result_size, pos,
                      input + offset, (size_t)match.rm_so) != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        pos += (size_t)match.rm_so;
        offset += (size_t)match.rm_eo;
    }

    if (pos >= result_size) {
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