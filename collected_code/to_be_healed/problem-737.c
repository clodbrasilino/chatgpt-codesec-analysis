#include <regex.h>
 /* Possible weaknesses found:
  *  'NULL' is defined in header '<stddef.h>'; did you forget to '#include <stddef.h>'?
  */

int startsWithVowel(char* str) {
    regex_t regex;
    regcomp(&regex, "^[aeiouAEIOU]", REG_EXTENDED);

    /* Possible weaknesses found:
     *  'NULL' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int result = regexec(&regex, str, 0, NULL, 0);

    regfree(&regex);

    if (result == 0) {
        return 1; // String starts with a vowel
    }
    else if (result == REG_NOMATCH) {
        return 0; // String does not start with a vowel
    }

    return -1; // Error occurred while executing the regex
}