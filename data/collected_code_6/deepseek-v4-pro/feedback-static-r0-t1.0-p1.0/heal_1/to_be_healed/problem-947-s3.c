#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

int shortest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int min_len = INT_MAX;
    int current_len = 0;
    int in_word = 0;

    while (*str) {
        if (isalpha((unsigned char)*str) || *str == '\'' || *str == '-') {
            if (!in_word) {
                in_word = 1;
                current_len = 0;
            }
            current_len++;
        } else {
            if (in_word) {
                if (current_len < min_len) {
                    min_len = current_len;
                }
                in_word = 0;
            }
        }
        str++;
    }

    if (in_word && current_len < min_len) {
        min_len = current_len;
    }

    return (min_len == INT_MAX) ? 0 : min_len;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'text1' can be declared as const array [constVariable]
     */
    char text1[] = "The quick brown fox jumps over the lazy dog";
    /* Possible weaknesses found:
     *  Variable 'text2' can be declared as const array [constVariable]
     */
    char text2[] = "Hello, world! This is a test.";
    /* Possible weaknesses found:
     *  Variable 'text3' can be declared as const array [constVariable]
     */
    char text3[] = "";
    /* Possible weaknesses found:
     *  Variable 'text4' can be declared as const array [constVariable]
     */
    char text4[] = "One";
    /* Possible weaknesses found:
     *  Variable 'text5' can be declared as const array [constVariable]
     */
    char text5[] = "a bb ccc dddd eeeee";

    printf("Shortest word length 1: %d\n", shortest_word_length(text1));
    printf("Shortest word length 2: %d\n", shortest_word_length(text2));
    printf("Shortest word length 3: %d\n", shortest_word_length(text3));
    printf("Shortest word length 4: %d\n", shortest_word_length(text4));
    printf("Shortest word length 5: %d\n", shortest_word_length(text5));
    printf("Shortest word length NULL: %d\n", shortest_word_length(NULL));

    return 0;
}