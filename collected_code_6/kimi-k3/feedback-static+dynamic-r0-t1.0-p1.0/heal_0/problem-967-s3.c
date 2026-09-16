#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_SIZE 1024

bool contains_all_vowels(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    bool vowel_flags[5] = {false};
    const char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    size_t i;
    
    while (*str != '\0') {
        char c = tolower((unsigned char)*str);
        for (i = 0; i < 5; i++) {
            if (c == vowels[i]) {
                vowel_flags[i] = true;
                break;
            }
        }
        str++;
    }
    
    for (i = 0; i < 5; i++) {
        if (!vowel_flags[i]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    char input[MAX_INPUT_SIZE];
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    if (contains_all_vowels(input)) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }
    
    return 0;
}