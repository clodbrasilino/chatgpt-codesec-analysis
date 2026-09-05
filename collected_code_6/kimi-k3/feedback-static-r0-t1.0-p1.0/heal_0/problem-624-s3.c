#include <stdio.h>
#include <ctype.h>
#include <string.h>

void to_uppercase(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t i = 0;
    while (str[i] != '\0') {
        str[i] = (char)toupper((unsigned char)str[i]);
        i++;
    }
}

int main(void) {
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    to_uppercase(buffer);
    
    printf("%s\n", buffer);
    
    return 0;
}