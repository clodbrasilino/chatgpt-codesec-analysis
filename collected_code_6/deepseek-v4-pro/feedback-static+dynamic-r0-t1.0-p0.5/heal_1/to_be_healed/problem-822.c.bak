#include <stdbool.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool is_valid_password(const char *password) {
    if (password == NULL) {
        return false;
    }

    size_t length = strlen(password);
    if (length < 8 || length > 64) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    for (size_t i = 0; i < length; i++) {
        unsigned char c = (unsigned char)password[i];
        if (isupper(c)) {
            has_upper = true;
        } else if (islower(c)) {
            has_lower = true;
        } else if (isdigit(c)) {
            has_digit = true;
        } else if (ispunct(c)) {
            has_special = true;
        } else if (!isprint(c)) {
            return false;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main(void) {
    const char *test_passwords[] = {
        "Password1!",
        "weak",
        "NoSpecial1",
        "noupper1!",
        "NOLOWER1!",
        "NoDigit!",
        "Valid123!",
        NULL
    };

    for (int i = 0; test_passwords[i] != NULL; i++) {
        if (is_valid_password(test_passwords[i])) {
            /* Possible weaknesses found:
             *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
             *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
             */
            printf("Valid: %s\n", test_passwords[i]);
        } else {
            printf("Invalid: %s\n", test_passwords[i]);
        }
    }

    return 0;
}