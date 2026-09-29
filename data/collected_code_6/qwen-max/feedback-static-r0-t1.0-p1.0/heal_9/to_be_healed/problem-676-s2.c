#include <stdio.h>
#include <string.h>
#include <regex.h>

void clean_string(char *str, size_t str_size) {
    regex_t regex;
    regmatch_t match[1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[1024] = "";
    size_t pos = 0;

    if (regcomp(&regex, "[^a-zA-Z0-9]", 0)) {
        return;
    }

    while (regexec(&regex, str + pos, 1, match, 0) == 0) {
        if (match[0].rm_so > 0) {
            size_t len = match[0].rm_so;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t current_len = strlen(result);
            if (current_len + len < sizeof(result) - 1) {
                snprintf(result + current_len, sizeof(result) - current_len, "%.*s", (int)len, str + pos);
            }
        }
        pos += match[0].rm_eo;
    }

    size_t remaining_len = strnlen(str + pos, str_size - pos);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t current_len = strlen(result);
    if (pos < str_size && current_len + remaining_len < sizeof(result) - 1) {
        snprintf(result + current_len, sizeof(result) - current_len, "%.*s", (int)remaining_len, str + pos);
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, result, str_size - 1);
    str[str_size - 1] = '\0';
    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    clean_string(input, sizeof(input));
    printf("%s\n", input);
    return 0;
}