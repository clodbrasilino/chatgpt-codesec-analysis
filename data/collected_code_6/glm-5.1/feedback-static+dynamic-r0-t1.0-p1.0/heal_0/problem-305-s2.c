#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match_words(const char **words, size_t count, size_t index1, size_t index2) {
    if (words == NULL || count == 0) {
        return 0;
    }
    if (index1 >= count || index2 >= count) {
        return 0;
    }
    if (words[index1] == NULL || words[index2] == NULL) {
        return 0;
    }
    if (words[index1][0] != 'p' || words[index2][0] != 'p') {
        return 0;
    }
    return strcmp(words[index1], words[index2]) == 0;
}

int main(void) {
    const char *word_list[] = {
        "pear",
        "peach",
        "apple",
        "plum",
        "pumpkin",
        "banana"
    };
    size_t word_count = sizeof(word_list) / sizeof(word_list[0]);

    int result1 = match_words(word_list, word_count, 0, 1);
    printf("Match 'pear' and 'peach': %d\n", result1);

    int result2 = match_words(word_list, word_count, 0, 3);
    printf("Match 'pear' and 'plum': %d\n", result2);

    int result3 = match_words(word_list, word_count, 2, 3);
    printf("Match 'apple' and 'plum': %d\n", result3);

    return 0;
}