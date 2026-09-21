#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

int add_spaces_between_capital_words(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int reti = regcomp(&regex, "([A-Z])", REG_EXTENDED);
    if (reti != 0) {
        return -1;
    }

    /* Possible weaknesses found:
     *  dest is initialized
     */
    char *src = str, *dest = str;
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    size_t len = strlen(str);
    char *new_str = malloc(len * 2 + 1);
    if (!new_str) {
        return -1;
    }
    /* Possible weaknesses found:
     *  dest is overwritten
     *  Redundant initialization for 'dest'. The initialized value is overwritten before it is read. [redundantInitialization]
     */
    dest = new_str;

    while (regexec(&regex, src, 1, pmatch, 0) == 0) {
        size_t distance = pmatch[0].rm_so;
        /* Possible weaknesses found:
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include '<string.h>' or provide a declaration of 'memmove'
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         *  invalid operands to binary + (have 'char *' and 'void *')
         *  invalid operands to binary expression ('char *' and 'void *')
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         */
        dest += memmove(dest, src, distance);
        *dest++ = ' ';
        src += distance + 1;
    }
    /* Possible weaknesses found:
     *  include '<string.h>' or provide a declaration of 'strcpy'
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     *  implicit declaration of function 'strcpy' [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strcpy'
     *  call to undeclared library function 'strcpy' with type 'char *(char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    strcpy(dest, src);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t new_len = strlen(new_str);
    if (new_len > len) {
        free(str);
        /* Possible weaknesses found:
         *  Variable 'str' is assigned a value that is never used. [unreadVariable]
         */
        str = realloc(new_str, new_len + 1);
    } else {
        /* Possible weaknesses found:
         *  include the header <string.h> or explicitly provide a declaration for 'memcpy'
         *  include '<string.h>' or provide a declaration of 'memcpy'
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         *  call to undeclared library function 'memcpy' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'memcpy' [-Wimplicit-function-declaration]
         */
        memcpy(str, new_str, new_len + 1);
        free(new_str);
    }

    regfree(&regex);
    return 0;
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    if (add_spaces_between_capital_words(str) != -1) {
        printf("%s\n", str);
    } else {
        perror("Regex error");
        exit(EXIT_FAILURE);
    }
    return 0;
}