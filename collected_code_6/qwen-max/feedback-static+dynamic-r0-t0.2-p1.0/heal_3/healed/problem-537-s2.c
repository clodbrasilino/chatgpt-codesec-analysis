#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char* find_first_repeated_word(const char *str) {
    const int max_words = 1024;
    char *words[max_words];
    bool seen[max_words] = {false};
    int word_count = 0;

    const char *p = str;
    while (*p) {
        const char *start = p;
        while (*p && *p != ' ') p++;
        if (start == p) break;

        bool found = false;
        for (int i = 0; i < word_count; i++) {
            if (strncmp(words[i], start, p - start) == 0) {
                found = true;
                break;
            }
        }

        if (found) {
            return (char *)start;
        }

        if (word_count < max_words) {
            words[word_count] = (char *)start;
            seen[word_count++] = true;
        } else {
            return NULL;
        }

        if (*p) p++;
    }

    return NULL;
}

int main() {
    const char *input = "ca ab bc ca";
    char *result = find_first_repeated_word(input);
    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }

    const char *input2 = "a b c d e f g h i j k l m n o p q r s t u v w x y z a";
    result = find_first_repeated_word(input2);
    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }

    const char *input3 = "unique words only";
    result = find_first_repeated_word(input3);
    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("None\n");
    }

    return 0;
}