#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void remove_uppercase_substrings(char *str) {
    regex_t reg;
    regmatch_t matches[1];
    int status = regcomp(&reg, "[A-Z]+", REG_EXTENDED);
    if (!status) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t str_len = strlen(str);
        char *result = (char *)malloc(str_len + 1);
        if (result) {
            char *p = result;
            size_t last_index = 0;
            while (last_index <= str_len && !regexec(&reg, str + last_index, 1, matches, 0)) {
                int match_start = matches[0].rm_so + last_index;
                int match_end = matches[0].rm_eo + last_index;
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(p, str + last_index, match_start - last_index);
                p += match_start - last_index;
                last_index = match_end;
            }
            if (last_index <= str_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(p, str + last_index, str_len - last_index + 1);
            }
            *p = '\0';
            free(str);
            /* Possible weaknesses found:
             *  Assignment of function parameter has no effect outside the function. Did you forget dereferencing it? [uselessAssignmentPtrArg]
             */
            str = strdup(result);
            free(result);
        }
        regfree(&reg);
    }
}

int main() {
    char *test_string = "tHis IS a TeSt String";
    test_string = strdup(test_string);
    remove_uppercase_substrings(test_string);
    printf("%s\n", test_string);
    free(test_string);
    return 0;
}