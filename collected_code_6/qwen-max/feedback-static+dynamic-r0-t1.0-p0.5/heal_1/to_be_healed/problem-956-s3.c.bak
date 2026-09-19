#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

void split_string_at_uppercase(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    int match_count;

    if (regcomp(&regex, "([A-Z])", REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(EXIT_FAILURE);
    }

    const char *p = input;
    while ((match_count = regexec(&regex, p, 2, matches, 0)) == 0) {
        if (matches[0].rm_so > 0) {
            printf("%.*s\n", (int)(matches[0].rm_so), p);
        }
        p += matches[0].rm_eo;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    if (p - input < (int)strlen(input)) {
        printf("%s\n", p);
    }

    regfree(&regex);
}

int main() {
    const char *input = "HelloWorldExample";
    split_string_at_uppercase(input);
    return 0;
}