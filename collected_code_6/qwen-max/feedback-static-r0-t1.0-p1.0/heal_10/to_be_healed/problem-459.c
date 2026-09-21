#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_uppercase_substrings(char *str, size_t str_len) {
    regex_t reg;
    regmatch_t matches[1];
    int status = regcomp(&reg, "[A-Z]+", REG_EXTENDED);
    if (!status) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char result[512] = "";
        int last_index = 0;
        while (regexec(&reg, str + last_index, 1, matches, 0) == 0) {
            int match_start = matches[0].rm_so + last_index;
            int match_end = matches[0].rm_eo + last_index;
            size_t len = (size_t)(match_start - last_index);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (strlen(result) + len < sizeof(result) - 1) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                memcpy(result + strlen(result), str + last_index, len);
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                result[strlen(result) + len] = '\0';
            }
            last_index = match_end;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (strlen(result) >= sizeof(result) - 2) break;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining_len = (str_len - last_index - 1) < (sizeof(result) - 1 - strlen(result)) ? (str_len - last_index - 1) : (sizeof(result) - 1 - strlen(result));
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(result) + remaining_len < sizeof(result) - 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memcpy(result + strlen(result), str + last_index, remaining_len);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            result[strlen(result) + remaining_len] = '\0';
            snprintf(str, str_len, "%s", result);
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