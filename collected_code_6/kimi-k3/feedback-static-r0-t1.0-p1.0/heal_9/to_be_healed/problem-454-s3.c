#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

int match_word_with_z(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strnlen(str, 256);
    if (len == 0) {
        return 0;
    }

    size_t start = 0;

    while (start < len) {
        while (start < len && !isalpha((unsigned char)str[start])) {
            start++;
        }

        if (start >= len) {
            break;
        }

        size_t end = start;
        int has_z = 0;

        while (end < len && isalpha((unsigned char)str[end])) {
            if (str[end] == 'z' || str[end] == 'Z') {
                has_z = 1;
            }
            end++;
        }

        if (has_z) {
            return 1;
        }

        start = end;
    }

    return 0;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;

    read_len = getline(&buffer, &buffer_size, stdin);
    if (read_len == -1) {
        /* Possible weaknesses found:
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(buffer);
        return 1;
    }

    if (read_len > 0 && buffer[read_len - 1] == '\n') {
        buffer[read_len - 1] = '\0';
    }

    if (match_word_with_z(buffer)) {
        printf("Match found\n");
    } else {
        printf("No match\n");
    }

    free(buffer);
    return 0;
}