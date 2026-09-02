#include <stdio.h>

int count_characters(const char *str) {
    int count = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (str[count] != '\0') {
        count++;
    }
    
    return count;
}

int main(void) {
    const char *test_string = "Hello, World!";
    int result = count_characters(test_string);
    
    printf("String: \"%s\"\n", test_string);
    printf("Character count: %d\n", result);
    
    return 0;
}