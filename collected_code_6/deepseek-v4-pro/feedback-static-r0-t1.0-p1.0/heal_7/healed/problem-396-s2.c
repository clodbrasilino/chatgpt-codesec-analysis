#include <stdio.h>
#include <string.h>

int starts_ends_same(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    return str[0] == str[len - 1];
}

int main(void) {
    char input[256];
    size_t len;
    size_t input_len;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    len = strcspn(input, "\n");
    if (len < sizeof(input)) {
        input[len] = '\0';
    } else {
        input[sizeof(input) - 1] = '\0';
    }
    
    input_len = strlen(input);
    if (input_len == 0) {
        return 1;
    }
    
    if (starts_ends_same(input)) {
        printf("The string starts and ends with the same character.\n");
    } else {
        printf("The string does not start and end with the same character.\n");
    }
    
    return 0;
}