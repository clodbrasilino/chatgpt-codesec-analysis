#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 4096

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    if (s == NULL) {
        return 0;
    }

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

static int checked_copy(char *dest, size_t dest_capacity, size_t dest_pos,
                        const char *src, size_t copy_len)
{
    size_t i;

    if (dest == NULL || src == NULL) {
        return -1;
    }

    if (dest_pos >= dest_capacity || copy_len >= dest_capacity - dest_pos) {
        return -1;
    }

    for (i = 0; i < copy_len; i++) {
        dest[dest_pos + i] = src[i];
    }

    return 0;
}

char *camel_to_snake(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *output;
    char *shrunk;
    size_t input_len;
    size_t capacity;
    size_t out_pos = 0;
    size_t offset = 0;

    if (input == NULL) {
        return NULL;
    }

    input_len = bounded_strlen(input, MAX_INPUT_LENGTH + 1);
    if (input_len > MAX_INPUT_LENGTH) {
        return NULL;
    }

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    capacity = (input_len * 2) + 1;

    output = malloc(capacity);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (offset < input_len) {
        int ret = regexec(&regex, input + offset, 1, &match, 0);

        if (ret == REG_NOMATCH) {
            size_t remaining = input_len - offset;

            if (checked_copy(output, capacity, out_pos, input + offset, remaining) != 0) {
                free(output);
                regfree(&regex);
                return NULL;
            }
            out_pos += remaining;
            break;
        }

        if (ret != 0) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        if (out_pos + (size_t)match.rm_so + 2 >= capacity) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        if (checked_copy(output, capacity, out_pos, input + offset, (size_t)match.rm_so) != 0) {
            free(output);
            regfree(&regex);
            return NULL;
        }
        out_pos += (size_t)match.rm_so;

        if (offset + (size_t)match.rm_so > 0) {
            output[out_pos++] = '_';
        }
        output[out_pos++] = (char)tolower((unsigned char)input[offset + (size_t)match.rm_so]);

        offset += (size_t)match.rm_so + 1;
    }

    output[out_pos] = '\0';
    regfree(&regex);

    shrunk = realloc(output, out_pos + 1);
    if (shrunk != NULL) {
        output = shrunk;
    }

    return output;
}

int main(void)
{
    const char *tests[] = {
        "camelCaseString",
        "thisIsATest",
        "helloWorld",
        "convertCamelCaseToSnakeCase",
        "simple",
        "already_snake",
        ""
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        char *snake = camel_to_snake(tests[i]);
        if (snake == NULL) {
            fprintf(stderr, "Conversion failed for input: \"%s\"\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("Input:  %s\nOutput: %s\n\n", tests[i], snake);
        free(snake);
    }

    return EXIT_SUCCESS;
}