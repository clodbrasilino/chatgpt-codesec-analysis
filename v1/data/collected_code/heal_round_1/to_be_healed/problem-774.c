#include <regex.h>
 /* Possible weaknesses found:
  *  'NULL' is defined in header '<stddef.h>'; did you forget to '#include <stddef.h>'?
  */

int isValidEmail(const char *email) {
    // Regular expression pattern for email validation
    const char *pattern = "^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$";

    // Compile the regular expression
    regex_t regex;
    int reti = regcomp(&regex, pattern, 0);
    if (reti) {
        return 0; // Failed to compile regex
    }

    // Execute the regular expression
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'NULL' undeclared (first use in this function)
     */
    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1; // Email is valid
    } else if (reti == REG_NOMATCH) {
        return 0; // Email is invalid
    } else {
        return 0; // Error occurred while executing regex
    }
}