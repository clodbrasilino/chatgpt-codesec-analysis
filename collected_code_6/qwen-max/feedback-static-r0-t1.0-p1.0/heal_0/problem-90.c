#include <stdio.h>
#include <string.h>

int longest_word_length(const char *sentence) {
    int max_length = 0, current_length = 0;
    while (*sentence) {
        if (*sentence == ' ' || *sentence == '\t' || *sentence == '\n') {
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
    const char *input = "This is a test of the longest word function";
    int length = longest_word_length(input);
    printf("The length of the longest word is: %d\n", length);
    return 0;
}