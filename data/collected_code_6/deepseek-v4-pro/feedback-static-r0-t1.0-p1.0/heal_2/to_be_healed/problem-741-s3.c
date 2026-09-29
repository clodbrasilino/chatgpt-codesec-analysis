#include <stdio.h>
#include <stdbool.h>

bool all_characters_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    char first_char = str[0];
    
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Assignment 'i=1', assigned value is 1
     *  Array 'str[1]' accessed at index 1, which is out of bounds. [arrayIndexOutOfBounds]
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
    
    printf("%s: %s\n", test1, all_characters_same(test1) ? "All same" : "Not all same");
    printf("%s: %s\n", test2, all_characters_same(test2) ? "All same" : "Not all same");
    printf("%s: %s\n", test3, all_characters_same(test3) ? "All same" : "Not all same");
    printf("%s: %s\n", test4, all_characters_same(test4) ? "All same" : "Not all same");
    
    return 0;
}