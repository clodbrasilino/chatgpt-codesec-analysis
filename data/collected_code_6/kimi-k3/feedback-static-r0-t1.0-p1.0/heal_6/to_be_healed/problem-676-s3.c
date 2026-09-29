#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

int remove_non_alphanumeric(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    size_t out_len = 0;
    size_t input_len;
    int ret;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    input_len = strnlen(input, output_size);
    if (input_len >= output_size) {
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
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining = strlen(cursor);
            if (remaining > 0) {
                if (remaining >= output_size - out_len) {
                    regfree(&regex);
                    return -1;
                }
                if (out_len > SIZE_MAX - remaining) {
                    regfree(&regex);
                    return -1;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(output + out_len, cursor, remaining);
                out_len += remaining;
            }
            break;
        } else if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_so > 0) {
            size_t copy_len = (size_t)match.rm_so;
            if (copy_len >= output_size - out_len) {
                regfree(&regex);
                return -1;
            }
            if (out_len > SIZE_MAX - copy_len) {
                regfree(&regex);
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[256];
    int result;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(input) >= sizeof(output)) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    result = remove_non_alphanumeric(input, output, sizeof(output));
    if (result == 0) {
        printf("%s\n", output);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}