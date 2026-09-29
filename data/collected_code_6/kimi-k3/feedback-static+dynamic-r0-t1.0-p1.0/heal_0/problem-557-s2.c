#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toggle_case(char *str) {
    if (str == NULL) {
        return;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
            str[i] = (char)tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = (char)toupper((unsigned char)str[i]);
        }
    }
}

int main(void) {
    char str[] = "Hello World! 123";
    
    printf("Original: %s\n", str);
    toggle_case(str);
    printf("Toggled:  %s\n", str);
    
    return 0;
}