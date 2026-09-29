#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096U

static char *cleanup_fail(regex_t *regex, char *buffer)
{
    if (regex != NULL) {
        regfree(regex);
    }
    free(buffer);
    return NULL;
}

static int safe_copy(char *dest, size_t dest_size, size_t dest_pos,
                     const char *src, size_t copy_len)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (dest_pos >= dest_size) {
        return -1;
    }
    if (copy_len >= dest_size - dest_pos) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(&dest[dest_pos], src, copy_len);
    return 0;
}

char *snake_to_camel(const char *input)
{
    regex_t regex;
    regmatch_t match[2];
    char *result;
    size_t len;
    size_t buf_size;
    size_t out_pos;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN + 1U);
    if (len > MAX_INPUT_LEN) {
        return NULL;
    }

    buf_size = len + 1U;
    result = malloc(buf_size);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "_([a-zA-Z0-9])", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    cursor = input;
    out_pos = 0U;

    while (regexec(&regex, cursor, 2U, match, 0) == 0) {
        size_t prefix_len;
        size_t remaining;

        if (match[0].rm_so < 0 || match[1].rm_so < 0 ||
            match[0].rm_eo < match[0].rm_so) {
            return cleanup_fail(&regex, result);
        }

        prefix_len = (size_t)match[0].rm_so;

        if (out_pos >= buf_size) {
            return cleanup_fail(&regex, result);
        }

        remaining = buf_size - out_pos;

        if (prefix_len >= remaining || (remaining - prefix_len) < 2U) {
            return cleanup_fail(&regex, result);
        }

        if (prefix_len > strnlen(cursor, prefix_len)) {
            return cleanup_fail(&regex, result);
        }

        if (prefix_len > 0U) {
            if (safe_copy(result, buf_size, out_pos, cursor, prefix_len) != 0) {
                return cleanup_fail(&regex, result);
            }
            out_pos += prefix_len;
        }

        if (out_pos + 1U >= buf_size) {
            return cleanup_fail(&regex, result);
        }

        result[out_pos] = (char)toupper((unsigned char)cursor[match[1].rm_so]);
        out_pos += 1U;

        cursor += match[0].rm_eo;
    }

    {
        size_t rest_len;
        size_t remaining;

        if (out_pos >= buf_size) {
            return cleanup_fail(&regex, result);
        }

        remaining = buf_size - out_pos;
        rest_len = strnlen(cursor, remaining);

        if (rest_len >= remaining) {
            return cleanup_fail(&regex, result);
        }

        if (rest_len > 0U) {
            if (safe_copy(result, buf_size, out_pos, cursor, rest_len) != 0) {
                return cleanup_fail(&regex, result);
            }
            out_pos += rest_len;
        }
    }

    if (out_pos >= buf_size) {
        return cleanup_fail(&regex, result);
    }

    result[out_pos] = '\0';
    regfree(&regex);

    return result;
}

int main(void)
{
    const char *tests[] = {
        "hello_world",
        "convert_snake_case_to_camel_case",
        "already",
        "multiple__underscores",
        "trailing_"
    };
    size_t i;
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0U; i < count; i++) {
        char *converted = snake_to_camel(tests[i]);
        if (converted == NULL) {
            fprintf(stderr, "Conversion failed for: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("%s -> %s\n", tests[i], converted);
        free(converted);
    }

    return EXIT_SUCCESS;
}