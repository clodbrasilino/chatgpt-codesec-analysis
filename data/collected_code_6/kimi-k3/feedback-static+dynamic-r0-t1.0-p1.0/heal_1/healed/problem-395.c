#include <stdio.h>
#include <string.h>
#include <limits.h>

char first_non_repeated_char(const char *str) {
    int char_count[UCHAR_MAX + 1] = {0};
    size_t i;
    
    if (str == NULL) {
        return '\0';
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        char_count[(unsigned char)str[i]]++;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        if (char_count[(unsigned char)str[i]] == 1) {
            return str[i];
        }
    }
    
    return '\0';
}

int main(void) {
    char input[1024];
    char result;
    
    printf("Enter a string: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    result = first_non_repeated_char(input);
    
    if (result != '\0') {
        printf("First non-repeated character: %c\n", result);
    } else {
        printf("No non-repeated character found\n");
    }
    
    return 0;
}