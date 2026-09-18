#include <ctype.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool has_uppercase(const char *s) {
    while(*s) {
        if(isupper(*s)) {
            return true;
        }
        s++;
    }
    return false;
}

bool has_lowercase(const char *s) {
    while(*s) {
        if(islower(*s)) {
            return true;
        }
        s++;
    }
    return false;
}

bool has_digit(const char *s) {
    while(*s) {
        if(isdigit(*s)) {
            return true;
        }
        s++;
    }
    return false;
}

bool is_string_valid(const char *s, size_t length) {
    return strlen(s) == length && has_uppercase(s) && has_lowercase(s) && has_digit(s);
}

int main() {
    const char test_string[] = "AbC1";
    if(is_string_valid(test_string, sizeof(test_string) - 1)) {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("The string is valid\n");
    } else {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("The string is invalid\n");
    }

    return 0;
}