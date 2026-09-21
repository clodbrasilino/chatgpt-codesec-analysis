#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 256

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

char* get_most_frequent_word(const char** strings, int num_strings) {
    if (strings == NULL || num_strings <= 0) {
        return NULL;
    }

    WordCount* counts = (WordCount*)malloc(num_strings * sizeof(WordCount));
    if (counts == NULL) {
        return NULL;
    }

    int unique_words = 0;
    int max_count = 0;
    char* most_frequent = NULL;

    for (int i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        int found = 0;
        for (int j = 0; j < unique_words; j++) {
            if (strncmp(counts[j].word, strings[i], MAX_WORD_LEN - 1) == 0) {
                counts[j].count++;
                if (counts[j].count > max_count) {
                    max_count = counts[j].count;
                    most_frequent = counts[j].word;
                }
                found = 1;
                break;
            }
        }

        if (!found) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(counts[unique_words].word, strings[i], MAX_WORD_LEN - 1);
            counts[unique_words].word[MAX_WORD_LEN - 1] = '\0';
            counts[unique_words].count = 1;
            
            if (max_count == 0) {
                max_count = 1;
                most_frequent = counts[unique_words].word;
            }
            unique_words++;
        }
    }

    char* result = NULL;
    if (most_frequent != NULL) {
        result = strdup(most_frequent);
    }

    free(counts);
    return result;
}

int main(void) {
    const char* str_list[] = {
        "apple",
        "banana",
        "apple",
        "orange",
        "banana",
        "apple"
    };
    int num_strings = sizeof(str_list) / sizeof(str_list[0]);

    char* result = get_most_frequent_word(str_list, num_strings);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}