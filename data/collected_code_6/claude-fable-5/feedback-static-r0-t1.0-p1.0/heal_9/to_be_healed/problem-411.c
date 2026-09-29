#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096U

static char *snake_to_camel(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    const char *cursor;
    size_t out_pos;
    size_t len;
    size_t tail_len;
    size_t buf_size;
    int status;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    status = regcomp(&regex, "_([a-zA-Z])", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    buf_size = len + 1U;
    result = calloc(buf_size, sizeof(char));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    out_pos = 0U;
    cursor = input;

    while (regexec(&regex, cursor, 1U, &match, 0) == 0) {
        size_t chunk;
        size_t cursor_len;
        /* Possible weaknesses found:
         *  The scope of the variable 'i' can be reduced. [variableScope]
         */
        size_t i;

        cursor_len = strnlen(cursor, buf_size);
        if (match.rm_so < 0 || match.rm_eo < 0 ||
            (size_t)match.rm_eo > cursor_len ||
            (size_t)match.rm_so >= (size_t)match.rm_eo) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        chunk = (size_t)match.rm_so;

        if (chunk > 0U) {
            size_t remaining;

            if (out_pos >= buf_size) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            remaining = buf_size - out_pos;
            if (chunk >= remaining) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            for (i = 0U; i < chunk && (out_pos + i) < buf_size; i++) {
                result[out_pos + i] = cursor[i];
            }
            if (i != chunk) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            out_pos += chunk;
        }

        if (out_pos + 1U >= buf_size) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if ((size_t)(match.rm_so + 1) >= cursor_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result[out_pos] = (char)toupper((unsigned char)cursor[match.rm_so + 1]);
        out_pos++;
        cursor += match.rm_eo;
    }

    tail_len = strnlen(cursor, buf_size);
    if (out_pos >= buf_size) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    if (tail_len >= buf_size - out_pos) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    {
        size_t i;
        for (i = 0U; i < tail_len && (out_pos + i) < buf_size; i++) {
            result[out_pos + i] = cursor[i];
        }
        if (i != tail_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }
    out_pos += tail_len;

    if (out_pos >= buf_size) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    result[out_pos] = '\0';

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *tests[] = {
        "hello_world_example",
        "convert_this_snake_case",
        "single",
        "a_b_c_d"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        char *camel = snake_to_camel(tests[i]);
        if (camel == NULL) {
            fprintf(stderr, "Conversion failed for: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (printf("%s -> %s\n", tests[i], camel) < 0) {
            free(camel);
            return EXIT_FAILURE;
        }
        free(camel);
    }

    return EXIT_SUCCESS;
}