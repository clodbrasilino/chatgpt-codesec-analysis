#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NO_OF_CHARS 256
#define NOT_FOUND 0

char first_non_repeated_char(const char* str) {
    if (str == NULL) {
        return '\0';
    }
    
    int *char_count = (int*)calloc(NO_OF_CHARS, sizeof(int));
    if (char_count == NULL) {
        return '\0';
    }
    
    const char *ptr = str;
    while (*ptr != '\0') {
        char_count[(unsigned char)*ptr]++;
        ptr++;
    }
    
    ptr = str;
    while (*ptr != '\0') {
        if (char_count[(unsigned char)*ptr] == 1) {
            char result = *ptr;
            free(char_count);
            return result;
        }
        ptr++;
    }
    
    free(char_count);
    return '\0';
}

int main(void) {
    const char *test_strings[] = {
        "aabbcc",
        "hello world",
        "programming",
        "racecar",
        "a",
        "",
        "abcabc",
        "xxyyzz"
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        char result = first_non_repeated_char(test_strings[i]);
        printf("String: \"%s\"\n", test_strings[i]);
        if (result != '\0') {
            printf("First non-repeated character: %c\n", result);
        } else {
            printf("No non-repeated character found\n");
        }
        printf("\n");
    }
    
    return 0;
}