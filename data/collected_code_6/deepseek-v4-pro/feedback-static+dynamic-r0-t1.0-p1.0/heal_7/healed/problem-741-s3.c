#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool all_characters_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    char first_char = str[0];
    size_t i = 0;
    
    while (str[i] != '\0') {
        if (str[i] != first_char) {
            return false;
        }
        i++;
    }
    
    return true;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "aaba";
    const char *test3 = "x";
    const char *test4 = "";
    const char *test5 = NULL;
    
    printf("%s: %s\n", test1, all_characters_same(test1) ? "True" : "False");
    printf("%s: %s\n", test2, all_characters_same(test2) ? "True" : "False");
    printf("%s: %s\n", test3, all_characters_same(test3) ? "True" : "False");
    
    printf("%s: %s\n", test4, all_characters_same(test4) ? "True" : "False");
    
    printf("NULL: %s\n", all_characters_same(test5) ? "True" : "False");
    
    return 0;
}