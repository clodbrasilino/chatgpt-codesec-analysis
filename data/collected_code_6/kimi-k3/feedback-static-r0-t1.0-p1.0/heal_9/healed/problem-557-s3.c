#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toggle_case(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    
    size_t i = 0;
    while (i < size - 1 && str[i] != '\0') {
        if (isupper((unsigned char)str[i])) {
            str[i] = (char)tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = (char)toupper((unsigned char)str[i]);
        }
        i++;
    }
    str[size - 1] = '\0';
}

int main(void) {
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    toggle_case(buffer, sizeof(buffer));
    printf("%s\n", buffer);
    
    return 0;
}