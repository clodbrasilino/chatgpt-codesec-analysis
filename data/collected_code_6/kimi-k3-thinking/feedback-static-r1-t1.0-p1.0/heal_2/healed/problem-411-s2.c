#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_INPUT_LEN 65536

static size_t safe_strlen(const char *s, size_t maxlen)
{
    size_t n = 0;

    while (n < maxlen && s[n] != '\0') {
        n++;
    }
    return n;
}

static int checked_memcpy(char *dest, size_t dest_cap, size_t dest_offset,
                          const char *src, size_t count)
{
    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (dest_offset > dest_cap || count > dest_cap - dest_offset) {
        return -1;
    }
    if (count > 0) {
        memcpy(dest + dest_offset, src, count);
    }
    return 0;
}

char *snake_to_camel(const char *input)
{
    regex_t regex;
    regmatch_t match[2];
    char *result;
    const char *cursor;
    size_t len;
    size_t ri;
    size_t cursor_len;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    len = safe_strlen(input, MAX_INPUT_LEN + 1);
    if (len > MAX_INPUT_LEN) {
        return NULL;
    }

    ret = regcomp(&regex, "_([a-zA-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    ri = 0;
    cursor = input;

    while (*cursor != '\0') {
        cursor_len = safe_strlen(cursor, len + 1);

        ret = regexec(&regex, cursor, 2, match, 0);
        if (ret == REG_NOMATCH) {
            if (checked_memcpy(result, len, ri, cursor, cursor_len) != 0) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            ri += cursor_len;
            break;
        }
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match[0].rm_so < 0 || match[0].rm_eo < 0 ||
            match[1].rm_so < 0 || match[1].rm_eo < 0 ||
            match[0].rm_eo < match[0].rm_so ||
            match[1].rm_so < match[0].rm_so ||
            match[1].rm_eo > match[0].rm_eo ||
            match[1].rm_eo <= match[1].rm_so ||
            (size_t)match[0].rm_eo > cursor_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (checked_memcpy(result, len, ri, cursor, (size_t)match[0].rm_so) != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        ri += (size_t)match[0].rm_so;

        if (ri >= len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result[ri++] = (char)toupper((unsigned char)cursor[match[1].rm_so]);
        cursor += match[0].rm_eo;
    }

    result[ri] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *tests[] = {
        "convert_this_snake_case_string",
        "hello_world_example",
        "another_test_case",
        "nounderscores",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *camel = snake_to_camel(tests[i]);
        if (camel == NULL) {
            fprintf(stderr, "Conversion failed for input: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("%s -> %s\n", tests[i], camel);
        free(camel);
    }

    return EXIT_SUCCESS;
}