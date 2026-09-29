#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

int lengthOfLastWord(const char *s, size_t max_len) {
    int len = 0;
    size_t i = 0;
    size_t str_len = 0;
    
    if (s == NULL || max_len == 0) {
        return 0;
    }
    
    while (str_len < max_len && s[str_len] != '\0') {
        str_len++;
    }
    
    if (str_len == 0) {
        return 0;
    }
    
    i = str_len - 1;

    while (i > 0 && s[i] == ' ') {
        i--;
    }
    
    if (s[i] == ' ') {
        return 0;
    }

    while (i > 0 && s[i] != ' ') {
        len++;
        i--;
    }
    
    if (s[i] != ' ') {
        len++;
    }

    return len;
}

int main(void) {
    char *str = NULL;
    size_t size = 0;
    ssize_t nread;

    nread = getline(&str, &size, stdin);
    if (nread != -1) {
        if (nread > 0 && str[nread - 1] == '\n') {
            str[nread - 1] = '\0';
            nread--;
        }
        printf("%d\n", lengthOfLastWord(str, (size_t)nread + 1));
        /* Possible weaknesses found:
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        free(str);
    }

    return 0;
}