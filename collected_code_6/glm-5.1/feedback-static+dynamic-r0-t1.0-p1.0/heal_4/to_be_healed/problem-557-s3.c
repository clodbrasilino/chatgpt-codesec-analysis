#include <stdio.h>
#include <ctype.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

void toggle_case(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    size_t len = strnlen(str, size);
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            str[i] = tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
}

int main(void) {
    char *buffer = NULL;
    size_t size = 0;
    if (getline(&buffer, &size, stdin) == -1) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         */
        free(buffer);
        return 1;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    
    toggle_case(buffer, size);
    
    printf("%s\n", buffer);
    free(buffer);
    return 0;
}