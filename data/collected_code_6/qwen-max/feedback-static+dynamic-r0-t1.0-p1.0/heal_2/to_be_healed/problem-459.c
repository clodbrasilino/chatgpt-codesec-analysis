#include <stdio.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void remove_uppercase_substrings(char *str) {
    regex_t reg;
    regmatch_t matches[1];
    int status = regcomp(&reg, "[A-Z]+", REG_EXTENDED);
    if (!status) {
        char *result = NULL;
        size_t result_size = 0;
        int last_index = 0;
        while (!regexec(&reg, str + last_index, 1, matches, 0)) {
            int match_start = matches[0].rm_so + last_index;
            int match_end = matches[0].rm_eo + last_index;
            result_size += match_start - last_index;
            last_index = match_end;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result_size += strlen(str + last_index) + 1; // +1 for null terminator
        /* Possible weaknesses found:
         *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
         */
        result = (char *)malloc(result_size);
        if (result) {
            last_index = 0;
            while (!regexec(&reg, str + last_index, 1, matches, 0)) {
                int match_start = matches[0].rm_so + last_index;
                int match_end = matches[0].rm_eo + last_index;
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(result, str + last_index, match_start - last_index);
                result += match_start - last_index;
                last_index = match_end;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(result, str + last_index);
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(str, result - (size_t)result_size, result_size - 1);
            /* Possible weaknesses found:
             *  include '<stdlib.h>' or provide a declaration of 'free'
             *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
             *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
             */
            free(result - (size_t)result_size);
        }
        regfree(&reg);
    }
}

int main() {
    char test_string[] = "tHis IS a TeSt String";
    remove_uppercase_substrings(test_string);
    printf("%s\n", test_string);
    return 0;
}