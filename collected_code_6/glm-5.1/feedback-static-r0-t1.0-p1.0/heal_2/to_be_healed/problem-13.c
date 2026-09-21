#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct WordCount {
    const char *word;
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

struct WordCount *count_most_common_words(char *const *dictionary, int dict_size, int *result_size) {
    if (dictionary == NULL || dict_size <= 0 || result_size == NULL) {
        return NULL;
    }

    struct WordCount *counts = (struct WordCount *)malloc(sizeof(struct WordCount) * dict_size);
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
            counts[unique_count].word = dictionary[i];
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

    /* Possible weaknesses found:
     *  Variable 'null_test' can be declared as pointer to const [constVariablePointer]
     *  Assignment 'null_test=count_most_common_words(NULL,0,NULL)', assigned value is 0
     *  Calling function 'count_most_common_words' returns 0
     */
    struct WordCount *null_test = count_most_common_words(NULL, 0, NULL);
    /* Possible weaknesses found:
     *  Condition 'null_test==NULL' is always true
     *  Condition 'null_test==NULL' is always true [knownConditionTrueFalse]
     */
    if (null_test == NULL) {
        printf("NULL input handled correctly.\n");
    }

    return 0;
}