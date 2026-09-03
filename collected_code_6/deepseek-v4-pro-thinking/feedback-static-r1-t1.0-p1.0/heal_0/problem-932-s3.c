#include <stdio.h>
#include <string.h>
#include <stddef.h>

void remove_duplicate_words(char **words, int *count) {
    if (words == NULL || count == NULL || *count <= 0) {
        return;
    }

    int total = *count;
    int unique_count = 0;

    for (int i = 0; i < total; ++i) {
        if (words[i] == NULL) {
            continue;
        }

        int duplicate = 0;
        for (int j = 0; j < unique_count; ++j) {
            if (words[j] != NULL && strcmp(words[i], words[j]) == 0) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate) {
            words[i] = NULL;
        } else {
            if (unique_count != i) {
                words[unique_count] = words[i];
                words[i] = NULL;
            }
            ++unique_count;
        }
    }

    *count = unique_count;
}

int main(void) {
    char *words[] = {"apple", "banana", "apple", "cherry", "banana", "date"};
    int count = (int)(sizeof(words) / sizeof(words[0]));

    remove_duplicate_words(words, &count);

    for (int i = 0; i < count; ++i) {
        printf("%s\n", words[i]);
    }

    return 0;
}