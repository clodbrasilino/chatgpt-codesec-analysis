#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toggle_case(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t i = 0;
    while (str[i] != '\0') {
        if (isupper((unsigned char)str[i])) {
            str[i] = (char)tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = (char)toupper((unsigned char)str[i]);
        }
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
    
    toggle_case(buffer);
    printf("%s\n", buffer);
    
    return 0;
}