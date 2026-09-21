#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void extract_quoted_strings(const char *input) {
    regex_t regex;
    regmatch_t match[2];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];

    const char *pattern = "\"([^\"]*)\"";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&regex, input, 2, match, 0) == 0) {
        size_t len = match[1].rm_eo - match[1].rm_so;
        if (len < sizeof(buffer)) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer, input + match[1].rm_so, len);
            buffer[len] = '\0';
            printf("%s\n", buffer);
        }
        input += match[0].rm_eo;
    }

    regfree(&regex);
}

int main() {
    const char *input = "This is a \"test\" string with \"multiple\" quoted \"values\".";
    extract_quoted_strings(input);
    return 0;
}