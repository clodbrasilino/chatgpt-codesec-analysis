#include <stdio.h>
#include <string.h>
#include <limits.h>

int find_shortest_word_length(const char *sentence) {
    int min_length = INT_MAX;
    const char *word_start = sentence;

    while (*sentence) {
        if (*sentence == ' ') {
            int word_length = (int)(sentence - word_start);
            if (word_length > 0 && word_length < min_length) {
                min_length = word_length;
            }
            word_start = sentence + 1;
        }
        sentence++;
    }

    int last_word_length = (int)(sentence - word_start);
    if (last_word_length > 0 && last_word_length < min_length) {
        min_length = last_word_length;
    }

    return min_length == INT_MAX ? 0 : min_length;
}

int main() {
    const char *sentence = "Hello world, this is a test";
    int shortest_word_length = find_shortest_word_length(sentence);
    printf("Length of the shortest word: %d\n", shortest_word_length);
    return 0;
}