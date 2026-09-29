#include <stdio.h>
#include <string.h>
#include <regex.h>

void clean_string(char *str, size_t str_len) {
    regex_t regex;
    regmatch_t match[1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[1024] = "";
    int pos = 0;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED)) {
        return;
    }

    while (pos < str_len && regexec(&regex, str + pos, 1, match, 0) == 0) {
        if (match[0].rm_so > 0) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = snprintf(result + strlen(result), sizeof(result) - strlen(result) - 1, "%.*s", (int)match[0].rm_so, str + pos);
            (void)len;
        }
        pos += match[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (pos < (int)str_len && (strlen(result) + str_len - pos) < sizeof(result) - 1) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = snprintf(result + strlen(result), sizeof(result) - strlen(result) - 1, "%s", str + pos);
        (void)len;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, result, str_len);
    str[str_len - 1] = '\0';
    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    clean_string(input, sizeof(input) - 1);
    printf("%s\n", input);
    return 0;
}