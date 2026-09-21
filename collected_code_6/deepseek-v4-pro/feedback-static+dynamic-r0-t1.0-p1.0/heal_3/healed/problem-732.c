#include <stdio.h>
#include <string.h>

void replace_chars(char *str, size_t size) {
    size_t i = 0;
    while (i < size && str[i] != '\0') {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
        i++;
    }
}

int main(void) {
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strcspn(buffer, "\n");
        if (len < sizeof(buffer)) {
            buffer[len] = '\0';
        } else {
            buffer[sizeof(buffer) - 1] = '\0';
        }
        replace_chars(buffer, sizeof(buffer));
        printf("%s\n", buffer);
    }
    
    return 0;
}