#include <stdio.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int is_string_starting_with_vowel(const char *str) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, "^[aeiouAEIOU]", REG_EXTENDED|REG_NOSUB) != 0) {
        return -1;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        const size_t MSG_SIZE = 100;
        /* Possible weaknesses found:
         *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
         */
        char *msgbuf = malloc(MSG_SIZE);
        if (msgbuf == NULL) {
            return -1;
        }
        regerror(reti, &regex, msgbuf, MSG_SIZE);
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(msgbuf);
        return -1;
    }
}

int main() {
    const char *test_str = "example";
    int result = is_string_starting_with_vowel(test_str);

    if (result == 1) {
        printf("The string '%s' starts with a vowel.\n", test_str);
    } else if (result == 0) {
        printf("The string '%s' does not start with a vowel.\n", test_str);
    } else {
        printf("An error occurred while checking the string.\n");
    }

    return 0;
}