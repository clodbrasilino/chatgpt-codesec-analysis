#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

int starts_ends_same_char(const char *str) {
    regex_t regex;
    int reti;
    int result = 0;

    if (str == NULL) {
        return 0;
    }

    reti = regcomp(&regex, "^(.).*\\1$|^.$", REG_EXTENDED);
    if (reti != 0) {
        return 0;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (reti == 0) {
        result = 1;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    char input[1024];
    char *newline;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    newline = strchr(input, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    if (starts_ends_same_char(input)) {
        printf("String starts and ends with the same character.\n");
    } else {
        printf("String does not start and end with the same character.\n");
    }

    return 0;
}