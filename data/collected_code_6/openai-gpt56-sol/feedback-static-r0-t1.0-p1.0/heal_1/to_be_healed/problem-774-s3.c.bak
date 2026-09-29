#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcspn'
  */

static bool is_valid_email(const char *email)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9](?:[A-Za-z0-9-]{0,61}[A-Za-z0-9])?"
        "(?:\\.[A-Za-z0-9](?:[A-Za-z0-9-]{0,61}[A-Za-z0-9])?)+$";
    regex_t regex;
    int status;
    bool valid;

    if (email == NULL) {
        return false;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return false;
    }

    status = regexec(&regex, email, 0, NULL, 0);
    valid = status == 0;
    regfree(&regex);

    return valid;
}

int main(void)
{
    char email[255];

    if (fgets(email, sizeof(email), stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strcspn' [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strcspn'
     *  call to undeclared library function 'strcspn' with type 'unsigned long (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    email[strcspn(email, "\r\n")] = '\0';

    if (is_valid_email(email)) {
        puts("Valid email address");
    } else {
        puts("Invalid email address");
    }

    return 0;
}