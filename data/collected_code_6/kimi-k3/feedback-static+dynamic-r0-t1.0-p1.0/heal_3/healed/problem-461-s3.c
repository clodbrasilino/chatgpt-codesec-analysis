#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int count_uppercase(const char *str) {
    int count = 0;
    if (str == NULL) {
        return 0;
    }
    while (*str != '\0') {
        if (isupper((unsigned char)*str)) {
            count++;
        }
        str++;
    }
    return count;
}

int main(void) {
    char input[256];
    printf("Enter a string: ");
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strcspn(input, "\n");
        input[len] = '\0';
        
        int result = count_uppercase(input);
        printf("Uppercase count: %d\n", result);
    } else {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    return 0;
}