#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_valid_password(const char *password) {
    if (password == NULL) return false;

    size_t length = 0;
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;

    /* Possible weaknesses found:
     *  Assuming that condition 'length<64' is not redundant
     *  Either the condition 'length<64' is redundant or the array 'password[5]' is accessed at index 63, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Array index out of bounds
     */
    while (length < 64 && password[length] != '\0') {
        /* Possible weaknesses found:
         *  Either the condition 'length<64' is redundant or the array 'password[5]' is accessed at index 63, which is out of bounds. [arrayIndexOutOfBoundsCond]
         *  Array index out of bounds
         */
        if (password[length] >= 'A' && password[length] <= 'Z') {
            has_upper = true;
        } else if (password[length] >= 'a' && password[length] <= 'z') {
            has_lower = true;
        } else if (password[length] >= '0' && password[length] <= '9') {
            has_digit = true;
        }
        length++;
    }

    return length >= 8 && has_upper && has_lower && has_digit;
}

int main() {
    const char *password1 = "Password123";
    const char *password2 = "pass";
    const char *password3 = "PASSWORD123";
    const char *password4 = "password123";

    printf("Password1: %s\n", is_valid_password(password1) ? "Valid" : "Invalid");
    printf("Password2: %s\n", is_valid_password(password2) ? "Valid" : "Invalid");
    printf("Password3: %s\n", is_valid_password(password3) ? "Valid" : "Invalid");
    printf("Password4: %s\n", is_valid_password(password4) ? "Valid" : "Invalid");

    return 0;
}