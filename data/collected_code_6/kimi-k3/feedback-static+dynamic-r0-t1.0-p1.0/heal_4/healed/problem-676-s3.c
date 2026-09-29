#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_non_alphanumeric(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    size_t out_len = 0;
    size_t input_len;
    size_t remaining;
    size_t copy_len;
    int ret;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    input_len = strnlen(input, 4096);
    if (input_len >= 4096) {
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
            remaining = strnlen(cursor, 4096 - (size_t)(cursor - input));
            if (remaining > 0) {
                if (out_len >= output_size || remaining >= output_size - out_len) {
                    regfree(&regex);
                    return -1;
                }
                if (out_len + remaining < output_size) {
                    memcpy(output + out_len, cursor, remaining);
                    out_len += remaining;
                } else {
                    regfree(&regex);
                    return -1;
                }
            }
            break;
        } else if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_so > 0) {
            copy_len = (size_t)match.rm_so;
            if (out_len >= output_size || copy_len >= output_size - out_len) {
                regfree(&regex);
                return -1;
            }
            if (out_len + copy_len < output_size) {
                memcpy(output + out_len, cursor, copy_len);
                out_len += copy_len;
            } else {
                regfree(&regex);
                return -1;
            }
        }
        cursor += match.rm_eo;
    }

    if (out_len < output_size) {
        output[out_len] = '\0';
    } else {
        regfree(&regex);
        return -1;
    }
    
    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "Hello, World! 123 @#$";
    char output[256];

    memset(output, 0, sizeof(output));

    if (remove_non_alphanumeric(input, output, sizeof(output)) == 0) {
        printf("%s\n", output);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}