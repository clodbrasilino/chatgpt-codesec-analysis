#include <stdio.h>
#include <string.h>
#include <regex.h>

void swap_spaces_underscores(char *str) {
    regex_t space_regex, underscore_regex;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char tmp[1024];
    
    if (regcomp(&space_regex, " ", REG_EXTENDED) || regcomp(&underscore_regex, "_", REG_EXTENDED)) {
        return;
    }
    
    if (regexec(&space_regex, str, 0, NULL, 0) == 0) {
        /* Possible weaknesses found:
         *  call to undeclared function 'regsub'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'regsub' [-Wimplicit-function-declaration]
         */
        snprintf(tmp, sizeof(tmp), "%s", regsub(&space_regex, str, "_"));
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(str, tmp);
    }
    
    if (regexec(&underscore_regex, str, 0, NULL, 0) == 0) {
        /* Possible weaknesses found:
         *  call to undeclared function 'regsub'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        snprintf(tmp, sizeof(tmp), "%s", regsub(&underscore_regex, str, " "));
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(str, tmp);
    }
    
    regfree(&space_regex);
    regfree(&underscore_regex);
}

int main() {
    char test_str[] = "Hello World and_Hello_Under_Score";
    
    swap_spaces_underscores(test_str);
    
    printf("%s\n", test_str);
    
    return 0;
}