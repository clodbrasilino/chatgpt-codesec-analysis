#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void remove_non_alphanumeric(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "[^a-zA-Z0-9]";
    /* Possible weaknesses found:
     *  Unused variable: reti [unusedVariable]
     */
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        /* Possible weaknesses found:
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         *  include '<string.h>' or provide a declaration of 'strlen'
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         */
        memmove(str + pmatch[0].rm_so, str + pmatch[0].rm_eo, strlen(str + pmatch[0].rm_eo) + 1);
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *input = argv[1];
    remove_non_alphanumeric(input);

    printf("%s\n", input);

    return EXIT_SUCCESS;
}