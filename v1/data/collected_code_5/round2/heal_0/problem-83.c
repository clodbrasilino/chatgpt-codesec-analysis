#include <stdio.h>
#include <string.h>

char addedChars(const char* str) {
    int total = 0;
    size_t length = strlen(str);

    for(size_t i = 0; i < length; i++) {
        total += str[i];
    }

    return (char)(total % 256);
}

int main() {
    const char* test_string = "12345";
    char result = addedChars(test_string);
    printf("The character from adding all characters is: %c\n", result);
    
    return 0;
}