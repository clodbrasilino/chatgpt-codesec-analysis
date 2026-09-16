#include <stdio.h>
#include <string.h>

const char *most_frequent_word(const char *words[], int count) {
    if (words == NULL || count <= 0) {
        return NULL;
    }

    int max_count = 0;
    const char *max_word = NULL;

    for (int i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }

        int current_count = 1;
        for (int j = i + 1; j < count; j++) {
            if (words[j] != NULL && strcmp(words[i], words[j]) == 0) {
                current_count++;
            }
        }

        if (current_count > max_count) {
            max_count = current_count;
            max_word = words[i];
        }
    }

    return max_word;
}

int main(void) {
    const char *words[] = {"apple", "banana", "apple", "orange", "banana", "apple"};
    int count = sizeof(words) / sizeof(words[0]);

    const char *result = most_frequent_word(words, count);
    if (result != NULL) {
        printf("%s\n", result);
    }

    return 0;
}