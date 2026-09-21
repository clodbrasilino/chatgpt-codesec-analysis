#include <stdio.h>
#include <string.h>
#include <regex.h>

int remove_whitespace(const char *input, char *output) {
    regex_t regex;
    regmatch_t match[1];
    int status, len = 0, olen = 0;

    status = regcomp(&regex, "\\s", REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return -1;
    }

    while ((status = regexec(&regex, input + len, 1, match, 0)) == 0) {
        if (match[0].rm_so > 0) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(output + olen, input + len, match[0].rm_so);
            olen += match[0].rm_so;
            len += match[0].rm_so;
        }
        len += match[0].rm_eo - match[0].rm_so;
    }

    if (status != REG_NOMATCH) {
        regfree(&regex);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(output + olen, input + len);
    regfree(&regex);
    return 0;
}

int main() {
    const char *input = " Hello, World!  This is a test. ";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[256];
    if (remove_whitespace(input, output) == 0) {
        printf("Result: %s\n", output);
    } else {
        printf("Failed to remove whitespaces.\n");
    }
    return 0;
}