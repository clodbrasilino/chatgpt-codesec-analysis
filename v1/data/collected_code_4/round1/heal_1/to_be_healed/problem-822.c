#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

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
     *  include '<stdio.h>' or provide a declaration of 'printf'
     *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
     */
    printf("Enter a password: ");
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'scanf' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'scanf' [-Wimplicit-function-declaration]
     *  include '<stdio.h>' or provide a declaration of 'scanf'
     */
    scanf("%20s", password);

    if(isValidPassword(password)) {
        printf("Password is valid\n");
    } else {
        printf("Password is invalid\n");
    }

    return 0;
}