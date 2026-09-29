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

        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], start) == 0) {
                return (char *)start;
            }
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
    const char *input = "This is a test to find the first repeated word in this string";
    char *result = find_first_repeated_word(input);
    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated word found.\n");
    }
    return 0;
}