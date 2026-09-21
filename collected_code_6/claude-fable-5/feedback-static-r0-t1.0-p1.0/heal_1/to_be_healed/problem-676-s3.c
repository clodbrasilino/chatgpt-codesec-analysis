#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_non_alnum(const char *input, char *output, size_t output_size);

int remove_non_alnum(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    size_t out_index;
    int ret;
    int eflags;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    ret = regcomp(&regex, "[^A-Za-z0-9]+", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = input;
    out_index = 0;
    eflags = 0;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, eflags);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining = strlen(cursor);
            if (out_index + remaining >= output_size) {
                regfree(&regex);
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(&output[out_index], cursor, remaining);
            out_index += remaining;
            break;
        } else if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_so > 0) {
            size_t copy_len = (size_t)match.rm_so;
            if (out_index + copy_len >= output_size) {
                regfree(&regex);
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(&output[out_index], cursor, copy_len);
            out_index += copy_len;
        }

        cursor += match.rm_eo;
        eflags = REG_NOTBOL;
    }

    output[out_index] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *test = "He!!llo, Wor@ld# 12$3.";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[256];

    if (remove_non_alnum(test, result, sizeof(result)) != 0) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", test) < 0) {
        return EXIT_FAILURE;
    }
    if (printf("Cleaned:  %s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}