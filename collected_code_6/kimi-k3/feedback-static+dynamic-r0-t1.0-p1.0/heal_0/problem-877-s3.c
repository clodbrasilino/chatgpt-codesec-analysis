#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_string(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strlen(str);
    if (len <= 1) {
        return;
    }
    
    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = 0; j < len - i - 1; j++) {
            if (str[j] > str[j + 1]) {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}

int main(void) {
    char buffer[256];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    sort_string(buffer);
    
    printf("Sorted string: %s\n", buffer);
    
    return EXIT_SUCCESS;
}