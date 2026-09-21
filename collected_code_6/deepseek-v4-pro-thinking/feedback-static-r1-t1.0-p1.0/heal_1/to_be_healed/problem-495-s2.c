#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *read_ptr = input;
    char *write_ptr = result;
    regmatch_t match;

    while (*read_ptr != '\0') {
        ret = regexec(&regex, read_ptr, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining = strlen(read_ptr);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(write_ptr, read_ptr, remaining);
            write_ptr += remaining;
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so >= 0) {
            size_t prefix_len = (size_t)match.rm_so;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(write_ptr, read_ptr, prefix_len);
            write_ptr += prefix_len;
            read_ptr += match.rm_eo;
        } else {
            break;
        }

        if (match.rm_eo == match.rm_so) {
            if (*read_ptr != '\0') {
                *write_ptr++ = *read_ptr++;
            }
        }
    }

    *write_ptr = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *input = "Hello World lowercase example ABC";
    char *output = remove_lowercase_substrings(input);
    if (output == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Input: %s\n", input);
    printf("Output: %s\n", output);
    free(output);
    return EXIT_SUCCESS;
}