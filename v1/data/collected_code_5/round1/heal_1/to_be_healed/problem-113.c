#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>

bool isInteger(const char* str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    if (*str == '+' || *str == '-') {
        str++;
    }
    
    while (*str != '\0') {
        if (!isdigit(*str)) {
            return false;
            str++;
        }
    }
    
    return true;
}

int main() {
    const char *str = "-1234";
    if (isInteger(str)) {
        /* Possible weaknesses found:
         *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
         *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        printf("The string is an integer.\n");
    } else {
        printf("The string is not an integer.\n");
    }
    
    return 0;
}