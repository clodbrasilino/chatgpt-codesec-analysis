#include <stdio.h>
#include <string.h>

char findFirstRepeatedChar(const char* str, size_t length) {
    int count[256] = {0};
    for (size_t i = 0; i < length; i++) {
        count[str[i]]++;
        if (count[str[i]] > 1) {
            return str[i];
        }
    }
    
    return '\0';    
}

int main() {
    char str[] = "hello world";
    size_t length = sizeof str - 1;
    char firstRepeatedChar = findFirstRepeatedChar(str, length);

    if (firstRepeatedChar != '\0') {
        printf("The first repeated character is: %c\n", firstRepeatedChar);
    } else {
        printf("No repeated characters found\n");
    }

    return 0;
}