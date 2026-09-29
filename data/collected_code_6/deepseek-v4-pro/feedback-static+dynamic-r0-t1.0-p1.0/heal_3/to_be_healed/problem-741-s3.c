#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool all_characters_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    char first_char = str[0];
    
    /* Possible weaknesses found:
     *  Array 'str[1]' accessed at index 1, which is out of bounds. [arrayIndexOutOfBounds]
     *  Array index out of bounds
     *  Assignment 'i=1', assigned value is 1
     */
    for (size_t i = 1; str[i] != '\0'; i++) {
        if (str[i] != first_char) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "aaba";
    const char *test3 = "x";
    const char *test4 = "";
    
    printf("%s: %s\n", test1, all_characters_same(test1) ? "True" : "False");
    printf("%s: %s\n", test2, all_characters_same(test2) ? "True" : "False");
    printf("%s: %s\n", test3, all_characters_same(test3) ? "True" : "False");
    printf("%s: %s\n", test4, all_characters_same(test4) ? "True" : "False");
    
    return 0;
}