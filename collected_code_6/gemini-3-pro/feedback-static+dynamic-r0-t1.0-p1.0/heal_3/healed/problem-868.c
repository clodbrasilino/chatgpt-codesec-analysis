#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int lengthOfLastWord(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int length = 0;
    int last_length = 0;

    while (*s != '\0') {
        if (isspace((unsigned char)*s)) {
            if (length > 0) {
                last_length = length;
                length = 0;
            }
        } else {
            length++;
        }
        s++;
    }

    return length > 0 ? length : last_length;
}

int main(void) {
    size_t bufsize = 10240;
    char *buffer = (char *)malloc(bufsize);
    
    if (buffer != NULL) {
        if (fgets(buffer, (int)bufsize, stdin) != NULL) {
            char *p = buffer;
            while (*p != '\0') {
                if (*p == '\n') {
                    *p = '\0';
                    break;
                }
                p++;
            }
            printf("%d\n", lengthOfLastWord(buffer));
        }
        free(buffer);
    }
    
    return 0;
}