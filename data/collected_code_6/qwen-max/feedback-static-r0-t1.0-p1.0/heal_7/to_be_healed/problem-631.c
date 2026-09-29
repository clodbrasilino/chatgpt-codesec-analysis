#include <stdio.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void swap_whitespace_underscore(char *str, size_t len) {
    regex_t re;
    if (regcomp(&re, " ", REG_EXTENDED) != 0) return;
    regmatch_t match;
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    char *new_str = malloc(len + 1);
    if (new_str == NULL) return;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(new_str, str);
    while (regexec(&re, new_str, 1, &match, 0) == 0 && match.rm_so < len) {
        memmove(new_str + match.rm_so + 1, new_str + match.rm_so, len - match.rm_so);
        new_str[match.rm_so] = '_';
        len++;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, new_str);
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(new_str);
    regfree(&re);

    if (regcomp(&re, "_", REG_EXTENDED) != 0) return;
    new_str = malloc(len + 1);
    if (new_str == NULL) return;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(new_str, str);
    while (regexec(&re, new_str, 1, &match, 0) == 0 && match.rm_so < len) {
        memmove(new_str + match.rm_so + 1, new_str + match.rm_so, len - match.rm_so);
        new_str[match.rm_so] = ' ';
        len++;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, new_str);
    free(new_str);
    regfree(&re);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strcspn(input, "\n");
        if (len >= 1023) {
            input[1023] = '\0';
            len = 1023;
        } else {
            input[len] = '\0';
        }
        swap_whitespace_underscore(input, len);
        printf("%s\n", input);
    }
    return 0;
}