#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 4096

void replace_chars(char *str, size_t size) {
    size_t i;
    for (i = 0; i < size && str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main(void) {
    char buffer[BUFFER_SIZE] = {0};
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        replace_chars(buffer, len);
        printf("%s\n", buffer);
    }
    
    return 0;
}