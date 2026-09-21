#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void convert_to_uppercase(char *str, size_t size) {
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
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    buffer[sizeof(buffer) - 1] = '\0';
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    convert_to_uppercase(buffer, sizeof(buffer));
    printf("Uppercase: %s\n", buffer);
    
    return EXIT_SUCCESS;
}