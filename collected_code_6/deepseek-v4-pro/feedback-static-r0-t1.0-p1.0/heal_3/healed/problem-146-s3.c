#include <stdio.h>
#include <string.h>
#include <stddef.h>

int total_ascii_value(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int total = 0;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        total += (unsigned char)str[i];
    }
    
    return total;
}

int main(void) {
    char str[256];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        str[0] = '\0';
    }
    
    size_t len = strlen(str);
    
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    int result = total_ascii_value(str);
    printf("Total ASCII value: %d\n", result);
    
    return 0;
}