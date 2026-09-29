#include <stdio.h>
#include <string.h>

int remove_duplicate_words(const char *words[], int count) {
    if (words == NULL || count <= 0) {
        return 0;
    }

    int unique_count = 0;

    for (int i = 0; i < count; ++i) {
        if (words[i] == NULL) {
            continue;
        }

        int is_duplicate = 0;

        for (int j = 0; j < unique_count; ++j) {
            if (strcmp(words[i], words[j]) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            words[unique_count] = words[i];
            ++unique_count;
        }
    }

    return unique_count;
}

int main(void) {
    const char *words[] = {
        "apple",
        "banana",
        "apple",
        "cherry",
        "banana",
        "date"
    };

    int word_count = sizeof(words) / sizeof(words[0]);
    int unique_count = remove_duplicate_words(words, word_count);

    for (int i = 0; i < unique_count; ++i) {
        printf("%s\n", words[i]);
    }

    return 0;
}