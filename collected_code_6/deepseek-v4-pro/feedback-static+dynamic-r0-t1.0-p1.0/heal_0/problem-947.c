#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int shortest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int min_len = INT_MAX;
    int current_len = 0;
    int in_word = 0;
    
    while (*str != '\0') {
        if (isalpha((unsigned char)*str)) {
            if (!in_word) {
                in_word = 1;
                current_len = 1;
            } else {
                current_len++;
            }
        } else {
            if (in_word) {
                if (current_len < min_len) {
                    min_len = current_len;
                }
                in_word = 0;
                current_len = 0;
            }
        }
        str++;
    }
    
    if (in_word) {
        if (current_len < min_len) {
            min_len = current_len;
        }
    }
    
    return (min_len == INT_MAX) ? 0 : min_len;
}

int main(void) {
    const char *test1 = "The quick brown fox jumps over the lazy dog";
    const char *test2 = "Hello world";
    const char *test3 = "";
    const char *test4 = "   ";
    const char *test5 = "a";
    
    printf("Test 1: %d\n", shortest_word_length(test1));
    printf("Test 2: %d\n", shortest_word_length(test2));
    printf("Test 3: %d\n", shortest_word_length(test3));
    printf("Test 4: %d\n", shortest_word_length(test4));
    printf("Test 5: %d\n", shortest_word_length(test5));
    
    return 0;
}