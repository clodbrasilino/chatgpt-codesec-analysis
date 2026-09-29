#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordEntry;

char *strdup_custom(const char *src) {
    size_t len = strlen(src) + 1;
    char *dst = (char *)malloc(len);
    if (dst) {
        memcpy(dst, src, len);
    }
    return dst;
}

char *get_most_frequent_word(char **strings, int num_strings) {
    WordEntry *entries = NULL;
    int capacity = 0;
    int size = 0;
    char *result = NULL;

    for (int i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        char *current = strings[i];
        while (*current != '\0') {
            while (*current != '\0' && !isalpha((unsigned char)*current)) {
                current++;
            }
            if (*current == '\0') {
                break;
            }

            /* Possible weaknesses found:
             *  Variable 'start' can be declared as pointer to const [constVariablePointer]
             */
            char *start = current;
            while (*current != '\0' && isalpha((unsigned char)*current)) {
                current++;
            }

            size_t word_len = current - start;
            char *word = (char *)malloc(word_len + 1);
            if (word == NULL) {
                for (int j = 0; j < size; j++) free(entries[j].word);
                free(entries);
                return NULL;
            }

            for (size_t k = 0; k < word_len; k++) {
                word[k] = tolower((unsigned char)start[k]);
            }
            word[word_len] = '\0';

            int found_index = -1;
            for (int j = 0; j < size; j++) {
                if (strcmp(entries[j].word, word) == 0) {
                    found_index = j;
                    break;
                }
            }

            if (found_index != -1) {
                free(word);
                entries[found_index].count++;
            } else {
                if (size >= capacity) {
                    int new_capacity = capacity == 0 ? 16 : capacity * 2;
                    WordEntry *new_entries = (WordEntry *)realloc(entries, new_capacity * sizeof(WordEntry));
                    if (new_entries == NULL) {
                        free(word);
                        for (int j = 0; j < size; j++) free(entries[j].word);
                        free(entries);
                        return NULL;
                    }
                    entries = new_entries;
                    capacity = new_capacity;
                }
                entries[size].word = word;
                entries[size].count = 1;
                size++;
            }
        }
    }

    int max_count = 0;
    for (int i = 0; i < size; i++) {
        if (entries[i].count > max_count) {
            max_count = entries[i].count;
        }
    }

    if (max_count > 0) {
        for (int i = 0; i < size; i++) {
            if (entries[i].count == max_count) {
                result = strdup_custom(entries[i].word);
                break;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        free(entries[i].word);
    }
    free(entries);

    return result;
}

int main() {
    char *strings[] = {
        "Hello world! This is a test.",
        "Testing, one two three. Hello again.",
        "World of testing. Hello world!"
    };

    int num_strings = sizeof(strings) / sizeof(strings[0]);

    char *most_frequent = get_most_frequent_word(strings, num_strings);

    if (most_frequent != NULL) {
        printf("%s\n", most_frequent);
        free(most_frequent);
    } else {
        printf("No words found.\n");
    }

    return 0;
}