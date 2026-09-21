#include <stdio.h>
#include <ctype.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

void toggle_case(char *str, size_t len) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; i < len && str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
            str[i] = tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters = getline(&buffer, &bufsize, stdin);
    if (characters == -1) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(buffer);
        return 1;
    }
    size_t len = strnlen(buffer, (size_t)characters);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    toggle_case(buffer, len);
    printf("%s\n", buffer);
    free(buffer);
    return 0;
}