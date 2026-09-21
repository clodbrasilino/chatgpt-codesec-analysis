#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    char buffer[10240];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        printf("%d\n", lengthOfLastWord(buffer));
    }

    return 0;
}