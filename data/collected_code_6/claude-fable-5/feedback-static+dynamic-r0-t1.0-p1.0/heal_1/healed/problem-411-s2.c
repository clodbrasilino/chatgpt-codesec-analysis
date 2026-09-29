#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

static char *snake_to_camel(const char *input)
{
    regex_t regex;
    regmatch_t match[2];
    char *result;
    size_t len;
    size_t out_pos;
    size_t buf_size;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, 4096U);
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
        regoff_t start = match[0].rm_so;
        regoff_t char_pos = match[1].rm_so;

        if (start > 0) {
            if (out_pos + (size_t)start >= buf_size) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            memcpy(&result[out_pos], cursor, (size_t)start);
            out_pos += (size_t)start;
        }

        if (out_pos + 1U >= buf_size) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        result[out_pos] = (char)toupper((unsigned char)cursor[char_pos]);
        out_pos++;

        cursor += match[0].rm_eo;
    }

    {
        size_t remaining = strnlen(cursor, buf_size);

        if (out_pos + remaining >= buf_size) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        memcpy(&result[out_pos], cursor, remaining);
        out_pos += remaining;
    }

    result[out_pos] = '\0';

    if (out_pos > 0U) {
        result[0] = (char)toupper((unsigned char)result[0]);
    }

    regfree(&regex);

    return result;
}

int main(void)
{
    const char *tests[] = {
        "hello_world",
        "snake_case_string",
        "already",
        "multi_word_example_test"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    int status = EXIT_SUCCESS;

    for (i = 0U; i < count; i++) {
        char *converted = snake_to_camel(tests[i]);

        if (converted == NULL) {
            if (fprintf(stderr, "Conversion failed for: %s\n", tests[i]) < 0) {
                status = EXIT_FAILURE;
                break;
            }
            status = EXIT_FAILURE;
            continue;
        }

        if (printf("%s -> %s\n", tests[i], converted) < 0) {
            free(converted);
            status = EXIT_FAILURE;
            break;
        }

        free(converted);
    }

    return status;
}