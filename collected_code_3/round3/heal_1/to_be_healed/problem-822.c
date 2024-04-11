#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool isValidPassword(char* password) {
    int length = strlen(password);
    if(length < 8) {
        return false;
    }
    bool hasUpper = false, hasLower = false, hasDigit = false;
    for(int i = 0; i < length; i++) {
        if(password[i] >= 'A' && password[i] <= 'Z') {
            hasUpper = true;
        }
        else if(password[i] >= 'a' && password[i] <= 'z') {
            hasLower = true;
        }
        else if(password[i] >= '0' && password[i] <= '9') {
            hasDigit = true;
        }
    }
    return hasUpper && hasLower && hasDigit;
}

int main() {
    char password[100];
    /* Possible weaknesses found:
     *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
     *  include '<stdio.h>' or provide a declaration of 'printf'
     */
    printf("Enter your password: ");
    /* Possible weaknesses found:
     *  include '<stdio.h>' or provide a declaration of 'scanf'
     *  implicit declaration of function 'scanf' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'scanf' [-Wbuiltin-declaration-mismatch]
     */
    scanf("%s", password);
    if(isValidPassword(password)) {
        printf("Password is valid.\n");
    }
    else {
        printf("Password is not valid.\n");
    }
    return 0;
}