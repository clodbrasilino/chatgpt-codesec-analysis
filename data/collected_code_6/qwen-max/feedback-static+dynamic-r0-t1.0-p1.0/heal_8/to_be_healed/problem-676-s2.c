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
    size_t pos = 0;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED)) {
        return;
    }

    while (pos < str_len && regexec(&regex, str + pos, 1, match, 0) == 0) {
        if (match[0].rm_so > 0) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining = sizeof(result) - strlen(result) - 1;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = snprintf(result + strlen(result), remaining, "%.*s", (int)match[0].rm_so, str + pos);
            (void)len;
        }
        pos += match[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (pos < str_len && (strlen(result) + (str_len - pos)) < sizeof(result) - 1) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining = sizeof(result) - strlen(result) - 1;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = snprintf(result + strlen(result), remaining, "%s", str + pos);
        (void)len;
    }

    if (str_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t to_copy = (str_len - 1) < strlen(result) ? (str_len - 1) : strlen(result);
        if (to_copy > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(str, result, to_copy);
            str[to_copy] = '\0';
        }
    }
    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    clean_string(input, sizeof(input) - 1);
    printf("%s\n", input);
    return 0;
}