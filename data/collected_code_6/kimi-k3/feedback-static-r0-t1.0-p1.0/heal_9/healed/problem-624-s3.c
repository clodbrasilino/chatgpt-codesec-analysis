#include <stdio.h>
#include <ctype.h>
#include <string.h>

void to_uppercase(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    
    size_t i = 0;
    while (i < size - 1 && str[i] != '\0') {
        str[i] = (char)toupper((unsigned char)str[i]);
        i++;
    }
}

int main(void) {
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    to_uppercase(buffer, sizeof(buffer));
    
    printf("%s\n", buffer);
    
    return 0;
}