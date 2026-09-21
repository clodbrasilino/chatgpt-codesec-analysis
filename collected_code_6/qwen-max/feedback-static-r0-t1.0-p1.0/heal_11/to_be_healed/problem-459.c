#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_uppercase_substrings(char *str, size_t str_len) {
    regex_t reg;
    regmatch_t matches[1];
    int status = regcomp(&reg, "[A-Z]+", REG_EXTENDED);
    if (status == 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char result[512] = "";
        size_t result_len = 0;
        int last_index = 0;
        while (regexec(&reg, str + last_index, 1, matches, 0) == 0) {
            int match_start = matches[0].rm_so + last_index;
            int match_end = matches[0].rm_eo + last_index;
            size_t len = (size_t)(match_start - last_index);
            if (result_len + len < sizeof(result) - 1) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, str + last_index, len);
                result[result_len + len] = '\0';
                result_len += len;
            }
            last_index = match_end;
            if (result_len >= sizeof(result) - 2) break;
        }
        size_t remaining_len = (str_len - last_index) < (sizeof(result) - 1 - result_len) ? (str_len - last_index) : (sizeof(result) - 1 - result_len);
        if (result_len + remaining_len < sizeof(result) - 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, str + last_index, remaining_len);
            result[result_len + remaining_len] = '\0';
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(str, result, str_len - 1);
            str[str_len - 1] = '\0';
        }
        regfree(&reg);
    }
}

int main() {
    char test_string[] = "tHis IS a TeSt String";
    remove_uppercase_substrings(test_string, sizeof(test_string));
    printf("%s\n", test_string);
    return 0;
}