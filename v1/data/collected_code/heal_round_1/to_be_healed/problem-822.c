/* Possible weaknesses found:
 *  unknown type name 'bool'
 *  include '<ctype.h>' or provide a declaration of 'islower'
 *  'bool' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
 */
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
        /* Possible weaknesses found:
         *  'false' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  'false' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
         */
        return false;
    }

    // Check for lowercase, uppercase, and digit characters in password
    for (int i = 0; i < length; i++) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'islower' [-Wimplicit-function-declaration]
         */
        if (islower(password[i])) {
            hasLowercase = 1;
        /* Possible weaknesses found:
         *  include '<ctype.h>' or provide a declaration of 'isupper'
         *  implicit declaration of function 'isupper' [-Wimplicit-function-declaration]
         */
        } else if (isupper(password[i])) {
            hasUppercase = 1;
        /* Possible weaknesses found:
         *  implicit declaration of function 'isdigit' [-Wimplicit-function-declaration]
         *  include '<ctype.h>' or provide a declaration of 'isdigit'
         */
        } else if (isdigit(password[i])) {
            hasDigit = 1;
        }
    }

    // Return true if all conditions are met, false otherwise
    return (hasLowercase && hasUppercase && hasDigit);
}