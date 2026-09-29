#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 4096

static int append_bytes(char *dest, size_t capacity, size_t *dest_pos,
                        const char *src, size_t len)
{
    if (*dest_pos >= capacity || len >= capacity - *dest_pos) {
        return -1;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest + *dest_pos, src, len);
        *dest_pos += len;
    }

    return 0;
}

char *replace_with_colon(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t input_len;
    size_t pos;
    size_t last;
    size_t dest_pos;
    size_t capacity;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LENGTH);
    if (input_len == MAX_INPUT_LENGTH) {
        regfree(&regex);
        return NULL;
    }

    capacity = input_len + 1;
    result = malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    pos = 0;
    last = 0;
    dest_pos = 0;

    while (pos < input_len) {
        size_t match_start;
        size_t match_end;

        ret = regexec(&regex, input + pos, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0 || match.rm_so < 0 || match.rm_eo < match.rm_so) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        match_start = pos + (size_t)match.rm_so;
        match_end = pos + (size_t)match.rm_eo;

        if (match_end == match_start) {
            pos = match_end + 1;
            continue;
        }

        if (match_start < last || match_end < match_start ||
            match_start > input_len || match_end > input_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (append_bytes(result, capacity, &dest_pos,
                         input + last, match_start - last) != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (dest_pos >= capacity) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        result[dest_pos] = ':';
        dest_pos++;

        last = match_end;
        pos = match_end;
    }

    if (last > input_len) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    if (append_bytes(result, capacity, &dest_pos,
                     input + last, input_len - last) != 0) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    if (dest_pos >= capacity) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    result[dest_pos] = '\0';

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *input = "Hello, World. This is a test, with spaces.";
    char *result = replace_with_colon(input);

    if (result == NULL) {
        fprintf(stderr, "Error: replacement failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Modified: %s\n", result);

    free(result);
    return EXIT_SUCCESS;
}