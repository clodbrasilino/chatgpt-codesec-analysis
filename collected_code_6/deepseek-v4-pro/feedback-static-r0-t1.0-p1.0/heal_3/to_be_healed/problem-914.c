#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

bool is_alternating(const char *str) {
    if (str == NULL || str[0] == '\0' || str[1] == '\0') {
        return false;
    }
    
    char first = str[0];
    char second = str[1];
    
    if (first == second) {
        return false;
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (i % 2 == 0) {
            if (str[i] != first) {
                return false;
            }
        } else {
            if (str[i] != second) {
                return false;
            }
        }
    }
    
    return true;
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t length;
    
    printf("Enter a string: ");
    length = getline(&buffer, &bufsize, stdin);
    if (length == -1) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         */
        free(buffer);
        return 1;
    }
    
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    }
    
    if (is_alternating(buffer)) {
        printf("The string consists of two alternating characters.\n");
    } else {
        printf("The string does not consist of two alternating characters.\n");
    }
    
    free(buffer);
    return 0;
}