#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memchr'
  */

static bool is_valid_email(const char *email)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]"
        "([A-Za-z0-9-]{0,61}[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]"
        "([A-Za-z0-9-]{0,61}[A-Za-z0-9])?)+$";
    regex_t regex;
    const char *end;
    int result;

    if (email == NULL || email[0] == '\0') {
        return false;
    }

    /* Possible weaknesses found:
     *  call to undeclared library function 'memchr' with type 'void *(const void *, int, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'memchr'
     *  implicit declaration of function 'memchr' [-Wimplicit-function-declaration]
     */
    end = memchr(email, '\0', 255U);
    if (end == NULL || (size_t)(end - email) > 254U) {
        return false;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }

    result = regexec(&regex, email, 0U, NULL, 0);
    regfree(&regex);

    return result == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email-address>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_valid_email(argv[1])) {
        puts("Valid email address");
        return EXIT_SUCCESS;
    }

    puts("Invalid email address");
    return EXIT_FAILURE;
}