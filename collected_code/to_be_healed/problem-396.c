#include <regex.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  'NULL' is defined in header '<stddef.h>'; did you forget to '#include <stddef.h>'?
  */

bool startsAndEndsWithSameChar(const char* str) {
    regex_t regex;
    regcomp(&regex, "^([a-zA-Z]).*\\1$", REG_EXTENDED);

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'NULL' undeclared (first use in this function)
     */
    int result = regexec(&regex, str, 0, NULL, 0);

    regfree(&regex);

    return result == 0;
}