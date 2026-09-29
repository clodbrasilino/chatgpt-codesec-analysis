#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_WORD_LENGTH 100
#define INITIAL_CAPACITY 1000
#define MAX_CAPACITY_LIMIT (SIZE_MAX / 2 / sizeof(WordCount))

typedef struct {
    char *word;
    size_t length;
    int count;
} WordCount;

typedef struct {
    WordCount *words;
    size_t size;
    size_t capacity;
} WordDictionary;

static int init_dictionary(WordDictionary *dict, size_t capacity) {
    if (dict == NULL || capacity == 0 || capacity > MAX_CAPACITY_LIMIT) {
        return -1;
    }
    
    dict->words = calloc(capacity, sizeof(WordCount));
    if (dict->words == NULL) {
        return -1;
    }
    
    dict->size = 0;
    dict->capacity = capacity;
    return 0;
}

static void free_dictionary(WordDictionary *dict) {
    if (dict != NULL) {
        if (dict->words != NULL) {
            for (size_t i = 0; i < dict->size; i++) {
                if (dict->words[i].word != NULL) {
                    free(dict->words[i].word);
                    dict->words[i].word = NULL;
                }
            }
            free(dict->words);
            dict->words = NULL;
        }
        dict->size = 0;
        dict->capacity = 0;
    }
}

static int resize_dictionary(WordDictionary *dict) {
    if (dict == NULL || dict->capacity == 0) {
        return -1;
    }
    
    if (dict->capacity > MAX_CAPACITY_LIMIT) {
        return -1;
    }
    
    size_t new_capacity = dict->capacity * 2;
    if (new_capacity < dict->capacity || new_capacity > MAX_CAPACITY_LIMIT) {
        return -1;
    }
    
    WordCount *new_words = realloc(dict->words, new_capacity * sizeof(WordCount));
    if (new_words == NULL) {
        return -1;
    }
    
    for (size_t i = dict->capacity; i < new_capacity; i++) {
        new_words[i].word = NULL;
        new_words[i].length = 0;
        new_words[i].count = 0;
    }
    
    dict->words = new_words;
    dict->capacity = new_capacity;
    return 0;
}

static int safe_tolower(int c) {
    if (c < 0 || c > UCHAR_MAX) {
        return c;
    }
    return tolower((unsigned char)c);
}

static int find_word_index(const WordDictionary *dict, const char *word, size_t word_len) {
    if (dict == NULL || word == NULL || word_len == 0 || word_len >= MAX_WORD_LENGTH) {
        return -1;
    }
    
    for (size_t i = 0; i < dict->size; i++) {
        if (dict->words[i].length == word_len && 
            dict->words[i].word != NULL &&
            memcmp(dict->words[i].word, word, word_len) == 0) {
            if (i > INT_MAX) {
                return -1;
            }
            return (int)i;
        }
    }
    return -1;
}

static int add_word(WordDictionary *dict, const char *word, size_t word_len) {
    if (dict == NULL || word == NULL || word_len == 0 || word_len >= MAX_WORD_LENGTH) {
        return -1;
    }
    
    if (dict->size > INT_MAX) {
        return -1;
    }

    int index = find_word_index(dict, word, word_len);
    if (index >= 0) {
        if (dict->words[index].count < INT_MAX) {
            dict->words[index].count++;
        }
        return 0;
    }

    if (dict->size >= dict->capacity) {
        if (resize_dictionary(dict) != 0) {
            return -1;
        }
    }

    if (word_len >= SIZE_MAX - 1) {
        return -1;
    }

    char *new_word = malloc(word_len + 1);
    if (new_word == NULL) {
        return -1;
    }
    
    if (word_len > 0) {
        memcpy(new_word, word, word_len);
    }
    new_word[word_len] = '\0';
    
    dict->words[dict->size].word = new_word;
    dict->words[dict->size].length = word_len;
    dict->words[dict->size].count = 1;
    dict->size++;
    
    return 0;
}

static int compare_word_counts(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    
    if (wb->count != wa->count) {
        return (wb->count > wa->count) ? 1 : -1;
    }
    
    if (wa->word == NULL && wb->word == NULL) return 0;
    if (wa->word == NULL) return 1;
    if (wb->word == NULL) return -1;
    
    size_t min_len = (wa->length < wb->length) ? wa->length : wb->length;
    int cmp = memcmp(wa->word, wb->word, min_len);
    if (cmp != 0) {
        return cmp;
    }
    
    if (wa->length != wb->length) {
        return (wa->length < wb->length) ? -1 : 1;
    }
    
    return 0;
}

static int process_word(WordDictionary *dict, const char *word, size_t word_len) {
    if (dict == NULL || word == NULL || word_len == 0 || word_len >= MAX_WORD_LENGTH) {
        return -1;
    }

    if (word_len >= SIZE_MAX - 1) {
        return -1;
    }

    char *buffer = malloc(word_len + 1);
    if (buffer == NULL) {
        return -1;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < word_len && j < word_len; i++) {
        unsigned char c = (unsigned char)word[i];
        if (isalpha(c)) {
            buffer[j++] = (char)safe_tolower(c);
        }
    }
    
    if (j == 0) {
        free(buffer);
        return -1;
    }
    
    buffer[j] = '\0';
    
    int result = add_word(dict, buffer, j);
    free(buffer);
    return result;
}

static int count_words_from_text(WordDictionary *dict, const char *text, size_t text_len) {
    if (dict == NULL || text == NULL || text_len == 0 || text_len > SIZE_MAX - 1) {
        return -1;
    }

    size_t start = 0;
    bool in_word = false;
    
    for (size_t i = 0; i <= text_len; i++) {
        bool is_alpha = false;
        if (i < text_len) {
            unsigned char c = (unsigned char)text[i];
            is_alpha = (isalpha(c) != 0);
        }
        
        if (is_alpha) {
            if (!in_word) {
                start = i;
                in_word = true;
            }
        } else {
            if (in_word) {
                size_t word_len = i - start;
                if (word_len > 0 && word_len < MAX_WORD_LENGTH) {
                    if (process_word(dict, text + start, word_len) != 0) {
                        return -1;
                    }
                }
                in_word = false;
            }
        }
    }
    
    return 0;
}

static void print_most_common_words(WordDictionary *dict, size_t top_n) {
    if (dict == NULL || dict->size == 0) {
        printf("No words found.\n");
        return;
    }

    qsort(dict->words, dict->size, sizeof(WordCount), compare_word_counts);

    size_t limit = (top_n < dict->size) ? top_n : dict->size;
    
    printf("Top %zu most common words:\n", limit);
    for (size_t i = 0; i < limit; i++) {
        if (dict->words[i].word != NULL) {
            printf("%zu. %s: %d\n", i + 1, dict->words[i].word, dict->words[i].count);
        }
    }
}

int main(void) {
    WordDictionary dict;
    
    if (init_dictionary(&dict, INITIAL_CAPACITY) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    const char sample_text[] = 
        "The quick brown fox jumps over the lazy dog. "
        "The dog was really lazy but the fox was very quick. "
        "A quick movement of the enemy will jeopardize six gunboats. "
        "The five boxing wizards jump quickly. "
        "How vexingly quick daft zebras jump!";

    size_t text_len = sizeof(sample_text) - 1;

    if (count_words_from_text(&dict, sample_text, text_len) != 0) {
        fprintf(stderr, "Error processing text\n");
        free_dictionary(&dict);
        return EXIT_FAILURE;
    }

    print_most_common_words(&dict, 10);

    free_dictionary(&dict);
    return EXIT_SUCCESS;
}