#include <stdio.h>
#include <string.h>
#include <limits.h>

int find_shortest_word_length(const char *sentence) {
    int shortest = INT_MAX;
    int current_length = 0;

    while (*sentence) {
        if (*sentence == ' ' || *sentence == '\t' || *sentence == '\n') {
            if (current_length > 0) {
                if (shortest > current_length) {
                    shortest = current_length;
                }
                current_length = 0;
            }
        } else {
            current_length++;
        }
        sentence++;
    }

    if (current_length > 0 && shortest > current_length) {
        shortest = current_length;
    }

    return shortest == INT_MAX ? 0 : shortest;
}

int main() {
    const char *test_sentence = "The quick brown fox jumps over the lazy dog";
    int length = find_shortest_word_length(test_sentence);
    printf("The length of the shortest word is: %d\n", length);
    return 0;
}