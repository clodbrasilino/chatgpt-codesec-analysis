#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void convert_to_lowercase(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }
    
    size_t i = 0;
    while (i < max_len - 1 && str[i] != '\0') {
        str[i] = (char)tolower((unsigned char)str[i]);
        i++;
    }
    str[i] = '\0';
}

int main(void) {
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strcspn(buffer, "\n");
    if (len < sizeof(buffer)) {
        buffer[len] = '\0';
    }
    
    convert_to_lowercase(buffer, sizeof(buffer));
    
    if (printf("%s\n", buffer) < 0) {
        fprintf(stderr, "Error writing output\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}