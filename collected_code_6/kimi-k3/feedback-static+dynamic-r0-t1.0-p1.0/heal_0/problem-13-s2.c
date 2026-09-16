#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define INITIAL_CAPACITY 1000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

typedef struct {
    WordCount *words;
    size_t size;
    size_t capacity;
} WordDictionary;

int init_dictionary(WordDictionary *dict, size_t capacity) {
    dict->words = malloc(capacity * sizeof(WordCount));
    if (dict->words == NULL) {
        return -1;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return 0;
}

void free_dictionary(WordDictionary *dict) {
    if (dict != NULL && dict->words != NULL) {
        free(dict->words);
        dict->words = NULL;
        dict->size = 0;
        dict->capacity = 0;
    }
}

int resize_dictionary(WordDictionary *dict) {
    size_t new_capacity = dict->capacity * 2;
    WordCount *new_words = realloc(dict->words, new_capacity * sizeof(WordCount));
    if (new_words == NULL) {
        return -1;
    }
    dict->words = new_words;
    dict->capacity = new_capacity;
    return 0;
}

void to_lowercase(char *str) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int find_word_index(WordDictionary *dict, const char *word) {
    if (dict == NULL || word == NULL) {
        return -1;
    }
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->words[i].word, word) == 0) {
            return (int)i;
        }
    }
    return -1;
}

int add_word(WordDictionary *dict, const char *word) {
    if (dict == NULL || word == NULL || strlen(word) == 0) {
        return -1;
    }

    if (strlen(word) >= MAX_WORD_LENGTH) {
        return -1;
    }

    int index = find_word_index(dict, word);
    if (index >= 0) {
        dict->words[index].count++;
        return 0;
    }

    if (dict->size >= dict->capacity) {
        if (resize_dictionary(dict) != 0) {
            return -1;
        }
    }

    strncpy(dict->words[dict->size].word, word, MAX_WORD_LENGTH - 1);
    dict->words[dict->size].word[MAX_WORD_LENGTH - 1] = '\0';
    dict->words[dict->size].count = 1;
    dict->size++;

    return 0;
}

int compare_word_counts(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    
    if (wb->count != wa->count) {
        return wb->count - wa->count;
    }
    return strcmp(wa->word, wb->word);
}

int process_word(WordDictionary *dict, const char *word) {
    if (word == NULL) {
        return -1;
    }

    char buffer[MAX_WORD_LENGTH];
    size_t len = strlen(word);
    
    if (len == 0 || len >= MAX_WORD_LENGTH) {
        return -1;
    }

    size_t j = 0;
    for (size_t i = 0; i < len && j < MAX_WORD_LENGTH - 1; i++) {
        if (isalpha((unsigned char)word[i])) {
            buffer[j++] = word[i];
        }
    }
    buffer[j] = '\0';

    if (j == 0) {
        return -1;
    }

    to_lowercase(buffer);
    return add_word(dict, buffer);
}

int count_words_from_text(WordDictionary *dict, const char *text) {
    if (dict == NULL || text == NULL) {
        return -1;
    }

    char buffer[MAX_WORD_LENGTH];
    size_t buf_index = 0;
    size_t text_len = strlen(text);

    for (size_t i = 0; i <= text_len; i++) {
        if (isalpha((unsigned char)text[i])) {
            if (buf_index < MAX_WORD_LENGTH - 1) {
                buffer[buf_index++] = text[i];
            }
        } else {
            if (buf_index > 0) {
                buffer[buf_index] = '\0';
                if (process_word(dict, buffer) != 0) {
                    return -1;
                }
                buf_index = 0;
            }
        }
    }

    return 0;
}

void print_most_common_words(WordDictionary *dict, size_t top_n) {
    if (dict == NULL || dict->size == 0) {
        printf("No words found.\n");
        return;
    }

    qsort(dict->words, dict->size, sizeof(WordCount), compare_word_counts);

    size_t limit = (top_n < dict->size) ? top_n : dict->size;
    
    printf("Top %zu most common words:\n", limit);
    for (size_t i = 0; i < limit; i++) {
        printf("%zu. %s: %d\n", i + 1, dict->words[i].word, dict->words[i].count);
    }
}

int main(void) {
    WordDictionary dict;
    
    if (init_dictionary(&dict, INITIAL_CAPACITY) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    const char *sample_text = 
        "The quick brown fox jumps over the lazy dog. "
        "The dog was really lazy but the fox was very quick. "
        "A quick movement of the enemy will jeopardize six gunboats. "
        "The five boxing wizards jump quickly. "
        "How vexingly quick daft zebras jump!";

    if (count_words_from_text(&dict, sample_text) != 0) {
        fprintf(stderr, "Error processing text\n");
        free_dictionary(&dict);
        return EXIT_FAILURE;
    }

    print_most_common_words(&dict, 10);

    free_dictionary(&dict);
    return EXIT_SUCCESS;
}