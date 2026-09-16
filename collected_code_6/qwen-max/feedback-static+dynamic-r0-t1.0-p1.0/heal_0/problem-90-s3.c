#include <stdio.h>
#include <string.h>

int find_longest_word_length(const char *sentence) {
    int max_length = 0;
    int current_length = 0;

    while (*sentence) {
        if (*sentence == ' ') {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 0;
        } else {
            current_length++;
        }
        sentence++;
    }

    if (current_length > max_length) {
        max_length = current_length;
    }

    return max_length;
}

int main() {
    const char *sentence = "This is a sample sentence with some words";
    int length = find_longest_word_length(sentence);
    printf("The length of the longest word is: %d\n", length);
    return 0;
}