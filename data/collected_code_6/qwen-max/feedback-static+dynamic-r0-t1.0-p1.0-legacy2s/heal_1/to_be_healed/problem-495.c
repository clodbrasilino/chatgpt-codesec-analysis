#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void removeLowercaseSubstrings(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int status;

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED|REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    while ((status = regexec(&regex, str, 1, pmatch, 0)) == 0) {
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

    if (status != REG_NOMATCH) {
        regfree(&regex);
        perror("Regex match failed");
        exit(EXIT_FAILURE);
    }

    regfree(&regex);
}

int main() {
    char input[] = "HeLlO WoRlD";
    removeLowercaseSubstrings(input);
    printf("%s\n", input);

    return 0;
}