#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096
#define OUTPUT_BUF_SIZE 256

static int remove_non_alphanumeric(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    size_t out_len = 0;
    size_t input_len;
    size_t remaining;
    size_t copy_len;
    size_t available;
    int ret;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return -1;
    }

    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = input;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            remaining = strnlen(cursor, MAX_INPUT_LEN - (size_t)(cursor - input));
            if (remaining > 0) {
                if (out_len >= output_size) {
                    regfree(&regex);
                    return -1;
                }
                available = output_size - out_len;
                if (remaining >= available) {
                    regfree(&regex);
                    return -1;
                }
                if (remaining > SIZE_MAX - out_len) {
                    regfree(&regex);
                    return -1;
                }
                if (out_len + remaining >= output_size) {
                    regfree(&regex);
                    return -1;
                }
                memcpy(output + out_len, cursor, remaining);
                out_len += remaining;
            }
            break;
        } else if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_so > 0) {
            copy_len = (size_t)match.rm_so;
            if (out_len >= output_size) {
                regfree(&regex);
                return -1;
            }
            available = output_size - out_len;
            if (copy_len >= available) {
                regfree(&regex);
                return -1;
            }
            if (copy_len > SIZE_MAX - out_len) {
                regfree(&regex);
                return -1;
            }
            if (out_len + copy_len >= output_size) {
                regfree(&regex);
                return -1;
            }
            memcpy(output + out_len, cursor, copy_len);
            out_len += copy_len;
        }
        cursor += match.rm_eo;
    }

    if (out_len >= output_size) {
        regfree(&regex);
        return -1;
    }

    output[out_len] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "Hello, World! 123 @#$";
    char output[OUTPUT_BUF_SIZE];

    memset(output, 0, sizeof(output));

    if (remove_non_alphanumeric(input, output, sizeof(output)) == 0) {
        printf("%s\n", output);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}