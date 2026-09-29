#include <stdio.h>
#include <string.h>
#include <stdint.h>

size_t count_characters(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t length = 0;
    while (length < SIZE_MAX && str[length] != '\0') {
        length++;
    }
    
    return length;
}

int main(void) {
    const char *test1 = "Hello, World!";
    const char *test2 = "";
    const char *test3 = NULL;
    
    printf("Test 1: %zu\n", count_characters(test1));
    printf("Test 2: %zu\n", count_characters(test2));
    printf("Test 3: %zu\n", count_characters(test3));
    
    return 0;
}