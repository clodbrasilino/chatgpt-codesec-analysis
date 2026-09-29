#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_uppercase_substrings(char *str) {
    regex_t reg;
    regmatch_t matches[1];
    int status = regcomp(&reg, "[A-Z]+", REG_EXTENDED);
    if (!status) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char result[512] = "";
        int last_index = 0;
        while (!regexec(&reg, str + last_index, 1, matches, 0)) {
            int match_start = matches[0].rm_so + last_index;
            int match_end = matches[0].rm_eo + last_index;
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, str + last_index, (size_t)(match_start - last_index));
            last_index = match_end;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, str + last_index, 512 - strlen(result) - 1);
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         *  'test_string' undeclared (first use in this function)
         *  use of undeclared identifier 'test_string'
         */
        strncpy(str, result, sizeof(test_string));
        /* Possible weaknesses found:
         *  use of undeclared identifier 'test_string'
         */
        str[sizeof(test_string) - 1] = '\0';
        regfree(&reg);
    }
}

int main() {
    char test_string[] = "tHis IS a TeSt String";
    remove_uppercase_substrings(test_string);
    printf("%s\n", test_string);
    return 0;
}