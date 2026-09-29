#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_whitespace(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t out_pos = 0;
    const char *cursor;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    ret = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
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
            if (out_pos + remaining >= output_size) {
                regfree(&regex);
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + out_pos, cursor, remaining);
            out_pos += remaining;
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if ((size_t)match.rm_so > 0) {
            if (out_pos + (size_t)match.rm_so >= output_size) {
                regfree(&regex);
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + out_pos, cursor, (size_t)match.rm_so);
            out_pos += (size_t)match.rm_so;
        }

        cursor += match.rm_eo;
    }

    if (out_pos >= output_size) {
        regfree(&regex);
        return -1;
    }

    output[out_pos] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *test = "  Hello,   World!\tThis is\na test string.  ";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[256];

    if (remove_whitespace(test, result, sizeof(result)) != 0) {
        fprintf(stderr, "Failed to remove whitespace\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: \"%s\"\n", test) < 0) {
        return EXIT_FAILURE;
    }
    if (printf("Result:   \"%s\"\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}