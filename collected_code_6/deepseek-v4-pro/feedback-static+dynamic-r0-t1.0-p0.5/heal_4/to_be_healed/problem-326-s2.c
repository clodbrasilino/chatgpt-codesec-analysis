#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WordCount {
    char *word;
    int count;
    struct WordCount *next;
} WordCount;

static WordCount *find_word(WordCount *head, const char *word) {
    WordCount *current = head;
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

static WordCount *add_word(WordCount **head, const char *word) {
    WordCount *new_node = (WordCount *)malloc(sizeof(WordCount));
    if (new_node == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    new_node->word = (char *)malloc(word_len + 1);
    if (new_node->word == NULL) {
        free(new_node);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_node->word, word, word_len + 1);
    new_node->count = 1;
    new_node->next = *head;
    *head = new_node;
    return new_node;
}

static void free_list(WordCount *head) {
    WordCount *current = head;
    while (current != NULL) {
        WordCount *next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
}

char *most_frequent_word(char **strings, int count) {
    if (strings == NULL || count <= 0) {
        return NULL;
    }

    WordCount *head = NULL;
    WordCount *max_node = NULL;

    for (int i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        WordCount *existing = find_word(head, strings[i]);
        if (existing != NULL) {
            existing->count++;
        } else {
            existing = add_word(&head, strings[i]);
            if (existing == NULL) {
                free_list(head);
                return NULL;
            }
        }

        if (max_node == NULL || existing->count > max_node->count) {
            max_node = existing;
        }
    }

    if (max_node == NULL) {
        free_list(head);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t result_len = strlen(max_node->word);
    char *result = (char *)malloc(result_len + 1);
    if (result == NULL) {
        free_list(head);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, max_node->word, result_len + 1);
    free_list(head);
    return result;
}

int main(void) {
    char *strings[] = {
        "apple",
        "banana",
        "apple",
        "orange",
        "banana",
        "apple",
        "grape"
    };
    int count = sizeof(strings) / sizeof(strings[0]);

    char *result = most_frequent_word(strings, count);
    if (result != NULL) {
        printf("Most frequent word: %s\n", result);
        free(result);
    } else {
        printf("No words found\n");
    }

    return 0;
}