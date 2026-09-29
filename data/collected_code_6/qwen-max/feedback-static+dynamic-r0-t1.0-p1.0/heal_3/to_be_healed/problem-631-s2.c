#include <stdio.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void swap_spaces_underscores(char *str) {
    regex_t space_regex, underscore_regex;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    char *tmp = (char *)malloc(str_len + 1);

    if (regcomp(&space_regex, " ", REG_EXTENDED) || regcomp(&underscore_regex, "_", REG_EXTENDED)) {
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(tmp);
        return;
    }

    if (regexec(&space_regex, str, 0, NULL, 0) == 0) {
        regmatch_t match;
        if (regexec(&space_regex, str, 1, &match, 0) == 0) {
            snprintf(tmp, str_len + 1, "%.*s_%s", (int)(match.rm_so), str, str + match.rm_eo);
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(str, tmp, str_len + 1);
            str[str_len] = '\0';
        }
    }

    if (regexec(&underscore_regex, str, 0, NULL, 0) == 0) {
        regmatch_t match;
        if (regexec(&underscore_regex, str, 1, &match, 0) == 0) {
            snprintf(tmp, str_len + 1, "%.*s %s", (int)(match.rm_so), str, str + match.rm_eo);
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(str, tmp, str_len + 1);
            str[str_len] = '\0';
        }
    }

    free(tmp);
    regfree(&space_regex);
    regfree(&underscore_regex);
}

int main() {
    char test_str[] = "Hello World and_Hello_Under_Score";
    
    swap_spaces_underscores(test_str);
    
    printf("%s\n", test_str);
    
    return 0;
}