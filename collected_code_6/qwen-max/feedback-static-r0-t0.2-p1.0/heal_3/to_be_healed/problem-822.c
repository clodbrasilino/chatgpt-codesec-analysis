#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

bool is_valid_password(const char *password, size_t length) {
    if (length < 8) return false;
    bool has_upper = false, has_lower = false, has_digit = false, has_special = false;
    for (size_t i = 0; i < length; ++i) {
        if (password[i] >= 'A' && password[i] <= 'Z') has_upper = true;
        else if (password[i] >= 'a' && password[i] <= 'z') has_lower = true;
        else if (password[i] >= '0' && password[i] <= '9') has_digit = true;
        /* Possible weaknesses found:
         *  include the header <string.h> or explicitly provide a declaration for 'strchr'
         *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        else if (strchr("!@#$%^&*()-_=+[]{}|;:',.<>/?", password[i])) has_special = true;
    }
    return has_upper && has_lower && has_digit && has_special;
}

int main() {
    const char password[] = "P@ssw0rd!";
    size_t length = sizeof(password) - 1;
    if (is_valid_password(password, length)) {
        printf("Password is valid.\n");
    } else {
        printf("Password is invalid.\n");
    }
    return 0;
}