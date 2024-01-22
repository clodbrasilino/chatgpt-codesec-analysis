#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 256

char findFirstNonRepeatedCharacter(char *str, size_t str_length) {
    if (str == NULL || str_length == 0) {
        return '\0';
    }

    unsigned int count[MAX_SIZE] = {0};

    for (size_t i = 0; i < str_length; i++) {
        count[(unsigned char)str[i]]++;
    }

    for (size_t i = 0; i < str_length; i++) {
        if (count[(unsigned char)str[i]] == 1) {
            return str[i];
        }
    }

    return '\0';
}

bool isValidString(const char *str, const size_t len) {
    if((str == NULL) || (len == 0) || (len > MAX_SIZE)) {
        return false;
    }
    
    return (str[len] == '\0') ? true : false;
}

int main() {
    char str[MAX_SIZE + 1] = "abacddbec";
    size_t str_length = strlen(str);

    if (isValidString(str, str_length) == false) {
        printf("Invalid string. Exiting...\n");
        return 1;
    }

    char result = findFirstNonRepeatedCharacter(str, str_length);

    if (result) {
        printf("First non-repeated character: %c\n", result);
    } else {
        printf("No unique character found\n");
    }

    return 0;
}