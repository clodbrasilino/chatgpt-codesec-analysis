#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void to_upper_case(char *str) {
    if (str == NULL) {
        return;
    }
    while (*str) {
        *str = (char)toupper((unsigned char)*str);
        str++;
    }
}

int main(void) {
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    to_upper_case(input);
    
    printf("Uppercase: %s\n", input);
    
    return 0;
}