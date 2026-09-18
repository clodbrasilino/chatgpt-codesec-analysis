#include <stdbool.h>
#include <string.h>

#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 20

bool isValidPassword(char* password) {
    int i;
    if (password == NULL) {
        return false;
    }

    int length = strlen(password);

    if (length < MIN_PASSWORD_LENGTH || length > MAX_PASSWORD_LENGTH) {
        return false;
    }
    
    bool hasUpperCase = false;
    bool hasLowerCase = false;
    bool hasDigit = false;

    for(i=0; i < length; ++i) {
        if(password[i] >= 'A' && password[i] <= 'Z') {
            hasUpperCase = true;
        } else if(password[i] >= 'a' && password[i] <= 'z') {
            hasLowerCase = true;
        } else if(password[i] >= '0' && password[i] <= '9') {
            hasDigit = true;
        }

        if(hasUpperCase && hasLowerCase && hasDigit) {
            return true;
        }
    }
    return false;
}

int main() {
    char password[] = "Password123";
    
    if(isValidPassword(password)) {
        printf("The password is valid");
    } else {
        printf("The password is not valid");
    }
    
    return 0;
}