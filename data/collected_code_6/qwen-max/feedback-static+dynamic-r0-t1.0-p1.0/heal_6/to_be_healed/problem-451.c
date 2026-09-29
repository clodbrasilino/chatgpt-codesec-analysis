#include <stdio.h>
#include <string.h>
#include <regex.h>

int remove_whitespace(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match[1];
    int status, len = 0, olen = 0;

    status = regcomp(&regex, "\\s", REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return -1;
    }

    while ((status = regexec(&regex, input + len, 1, match, 0)) == 0) {
        if (match[0].rm_so > 0) {
            size_t to_copy = match[0].rm_so;
            if (to_copy > output_size - olen - 1) {
                to_copy = output_size - olen - 1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + olen, input + len, to_copy);
            olen += to_copy;
            len += to_copy;
            if (olen >= output_size - 1) break;
        }
        len += match[0].rm_eo - match[0].rm_so;
    }

    if (status != REG_NOMATCH) {
        regfree(&regex);
        return -1;
    }

    size_t remaining_length = (input + len - input) < (output_size - olen - 1) ? (input + len - input) : (output_size - olen - 1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + olen, input + len, remaining_length);
    olen += remaining_length;

    output[olen] = '\0';
    regfree(&regex);
    return 0;
}

int main() {
    const char *input = " Hello, World!  This is a test. ";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[256];

    if (remove_whitespace(input, output, sizeof(output)) == 0) {
        printf("Result: %s\n", output);
    } else {
        printf("Failed to remove whitespaces.\n");
    }
    return 0;
}