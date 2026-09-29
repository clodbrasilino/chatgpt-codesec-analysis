bool isValidPassword(const char* password) {
    int length = 0;
    int hasLowercase = 0;
    int hasUppercase = 0;
    int hasDigit = 0;

    // Check for password length greater than or equal to 8
    while (password[length] != '\0') {
        length++;
    }
    if (length < 8) {
        return false;
    }

    // Check for lowercase, uppercase, and digit characters in password
    for (int i = 0; i < length; i++) {
        if (islower(password[i])) {
            hasLowercase = 1;
        } else if (isupper(password[i])) {
            hasUppercase = 1;
        } else if (isdigit(password[i])) {
            hasDigit = 1;
        }
    }

    // Return true if all conditions are met, false otherwise
    return (hasLowercase && hasUppercase && hasDigit);
}