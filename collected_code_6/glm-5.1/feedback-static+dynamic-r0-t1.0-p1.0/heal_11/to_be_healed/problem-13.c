#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct WordCount {
    char *word;
    int count;
};

int compare_counts(const void *a, const void *b) {
    const struct WordCount *wa = (const struct WordCount *)a;
    const struct WordCount *wb = (const struct WordCount *)b;
    if (wb->count != wa->count) {
        return wb->count - wa->count;
    }
    return strcmp(wa->word, wb->word);
}

struct WordCount *count_most_common_words(char * const *dictionary, int dict_size, int *result_size) {
    if (dictionary == NULL || dict_size <= 0 || result_size == NULL) {
        return NULL;
    }

    struct WordCount *counts = malloc(sizeof(struct WordCount) * dict_size);
    if (counts == NULL) {
        *result_size = 0;
        return NULL;
    }

    int unique_count = 0;
    for (int i = 0; i < dict_size; i++) {
        if (dictionary[i] == NULL) {
            continue;
        }

        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(counts[j].word, dictionary[i]) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            size_t len = strnlen(dictionary[i], 1024);
            size_t alloc_size = (len == 1024) ? 1025 : (len + 1);
            size_t copy_size = (len == 1024) ? 1024 : (len + 1);

            if (alloc_size < copy_size) {
                for (int k = 0; k < unique_count; k++) {
                    free(counts[k].word);
                }
                free(counts);
                *result_size = 0;
                return NULL;
            }

            counts[unique_count].word = malloc(alloc_size);
            if (counts[unique_count].word == NULL) {
                for (int k = 0; k < unique_count; k++) {
                    free(counts[k].word);
                }
                free(counts);
                *result_size = 0;
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(counts[unique_count].word, dictionary[i], copy_size);

            if (len == 1024) {
                counts[unique_count].word[1024] = '\0';
            }

            counts[unique_count].count = 1;
            unique_count++;
        }
    }

    if (unique_count == 0) {
        free(counts);
        *result_size = 0;
        return NULL;
    }

    qsort(counts, unique_count, sizeof(struct WordCount), compare_counts);

    *result_size = unique_count;
    return counts;
}

void free_word_counts(struct WordCount *counts, int size) {
    if (counts != NULL) {
        for (int i = 0; i < size; i++) {
            free(counts[i].word);
        }
        free(counts);
    }
}

int main(void) {
    char *dictionary[] = {
        "apple", "banana", "apple", "orange", "banana", "apple", "grape",
        "kiwi", "banana", "apple", "orange", "grape", "mango", "apple"
    };
    int dict_size = sizeof(dictionary) / sizeof(dictionary[0]);
    int result_size = 0;

    struct WordCount *counts = count_most_common_words(dictionary, dict_size, &result_size);

    if (counts != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%s: %d\n", counts[i].word, counts[i].count);
        }
        free_word_counts(counts, result_size);
    } else {
        printf("No words counted or allocation failed.\n");
    }

    int null_result_size = 0;
    const struct WordCount *null_test = count_most_common_words(NULL, 0, &null_result_size);
    
    (void)null_test;

    return 0;
}