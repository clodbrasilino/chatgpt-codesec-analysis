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
            size_t current_len = strnlen(result, sizeof(result));
            if (current_len + len < sizeof(result) - 1) {
                /* Possible weaknesses found:
                 * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
                 */
                strncat(result, str + pos, len);
            }
        }
        pos += match[0].rm_eo;
    }

    size_t remaining_len = strnlen(str + pos, str_size - pos);
    size_t current_len = strnlen(result, sizeof(result));
    if (pos < str_size && current_len + remaining_len < sizeof(result) - 1) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, str + pos, remaining_len);
    }

    size_t min_size = (str_size - 1 < sizeof(result)) ? str_size - 1 : sizeof(result);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, result, min_size);
    str[min_size] = '\0';
    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    clean_string(input, sizeof(input));
    printf("%s\n", input);
    return 0;
}