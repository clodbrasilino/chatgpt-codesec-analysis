#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int shortest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int min_length = INT_MAX;
    int current_length = 0;
    int in_word = 0;
    
    while (*str != '\0') {
        if (isspace((unsigned char)*str)) {
            if (in_word) {
                if (current_length < min_length) {
                    min_length = current_length;
                }
                current_length = 0;
                in_word = 0;
            }
        } else {
            in_word = 1;
            current_length++;
        }
        str++;
    }
    
    if (in_word && current_length < min_length) {
        min_length = current_length;
    }
    
    return (min_length == INT_MAX) ? 0 : min_length;
}

int main(void) {
    char text1[] = "The quick brown fox jumps over the lazy dog";
    char text2[] = "hello";
    char text3[] = "   ";
    char text4[] = "";
    char text5[] = "a bb ccc dddd eeeee";
    
    printf("Shortest word length in '%s': %d\n", text1, shortest_word_length(text1));
    printf("Shortest word length in '%s': %d\n", text2, shortest_word_length(text2));
    printf("Shortest word length in '%s': %d\n", text3, shortest_word_length(text3));
    printf("Shortest word length in '%s': %d\n", text4, shortest_word_length(text4));
    printf("Shortest word length in '%s': %d\n", text5, shortest_word_length(text5));
    printf("Shortest word length in NULL: %d\n", shortest_word_length(NULL));
    
    return 0;
}