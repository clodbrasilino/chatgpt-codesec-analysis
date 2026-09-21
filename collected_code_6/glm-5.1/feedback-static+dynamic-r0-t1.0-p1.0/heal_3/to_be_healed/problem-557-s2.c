#include <stdio.h>
#include <ctype.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

void toggle_case(char *str, size_t max_len) {
    if (str == NULL) {
        return;
    }
    size_t i = 0;
    while (i < max_len && str[i] != '\0') {
        if (isupper((unsigned char)str[i])) {
            str[i] = tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = toupper((unsigned char)str[i]);
        }
        i++;
    }
}

int main(void) {
    char *buffer = NULL;
    size_t len = 0;
    if (getline(&buffer, &len, stdin) == -1) {
        return 1;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    toggle_case(buffer, len);
    printf("%s\n", buffer);
    /* Possible weaknesses found:
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     */
    free(buffer);
    return 0;
}