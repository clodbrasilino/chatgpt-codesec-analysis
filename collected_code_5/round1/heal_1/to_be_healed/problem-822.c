#include <stdbool.h>
#include <string.h>

bool isValidPassword(char *password) {
    if(password == NULL) {
        return false;
    }

    int length = strlen(password);
    if(length < 8 || length > 20) {
        return false;
    }

    bool hasDigit = false;
    bool hasLower = false;
    bool hasUpper = false;
    for(int i = 0; i < length; i++) {
        char ch = password[i];

        if(ch >= '0' && ch <= '9') {
            hasDigit = true;
        } else if(ch >= 'a' && ch <= 'z') {
            hasLower = true;
        } else if(ch >= 'A' && ch <= 'Z') {
            hasUpper = true;
        }
    }

    return hasDigit && hasLower && hasUpper;
}

int main() {
    char password[21];
    /* Possible weaknesses found:
     *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
     *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    printf("Enter a password: ");
    /* Possible weaknesses found:
     *  include the header <stdio.h> or explicitly provide a declaration for 'scanf'
     *  call to undeclared library function 'scanf' with type 'int (const char *restrict, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    scanf("%20s", password);

    if(isValidPassword(password)) {
        printf("Password is valid\n");
    } else {
        printf("Password is invalid\n");
    }

    return 0;
}