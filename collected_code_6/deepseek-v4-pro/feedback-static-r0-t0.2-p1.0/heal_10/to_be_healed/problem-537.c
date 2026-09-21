#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define HASH_SIZE 1000

typedef struct WordNode {
    char *word;
    struct WordNode *next;
} WordNode;

static unsigned int hash_string(const char *str, size_t len) {
    unsigned int hash = 5381;
    for (size_t i = 0; i < len; i++) {
        hash = ((hash << 5) + hash) + (unsigned char)str[i];
    }
    return hash % HASH_SIZE;
}

static WordNode **create_hash_table(void) {
    WordNode **table = calloc(HASH_SIZE, sizeof(WordNode *));
    return table;
}

static void free_hash_table(WordNode **table) {
    if (!table) return;
    for (int i = 0; i < HASH_SIZE; i++) {
        WordNode *current = table[i];
        while (current) {
            WordNode *next = current->next;
            free(current->word);
            free(current);
            current = next;
        }
    }
    free(table);
}

static int word_exists(WordNode **table, const char *word, size_t word_len) {
    unsigned int index = hash_string(word, word_len);
    WordNode *current = table[index];
    while (current) {
        if (strcmp(current->word, word) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

static int add_word(WordNode **table, const char *word, size_t word_len) {
    unsigned int index = hash_string(word, word_len);
    
    if (word_len >= MAX_WORD_LEN) {
        return 0;
    }
    
    WordNode *new_node = malloc(sizeof(WordNode));
    if (!new_node) {
        return 0;
    }
    
    new_node->word = malloc(word_len + 1);
    if (!new_node->word) {
        free(new_node);
        return 0;
    }
    
    if (word_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_node->word, word, word_len);
    }
    new_node->word[word_len] = '\0';
    new_node->next = table[index];
    table[index] = new_node;
    return 1;
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *find_first_repeated_word(const char *str) {
    if (!str) {
        return NULL;
    }

    WordNode **table = create_hash_table();
    if (!table) {
        return NULL;
    }

    char *word = malloc(MAX_WORD_LEN + 1);
    if (!word) {
        free_hash_table(table);
        return NULL;
    }
    
    size_t word_len = 0;
    char *result = NULL;
    size_t max_str_len = MAX_WORD_LEN * 10000;
    size_t str_len = safe_strlen(str, max_str_len);

    for (size_t i = 0; i <= str_len; i++) {
        if (i < str_len && isalpha((unsigned char)str[i])) {
            if (word_len < MAX_WORD_LEN) {
                word[word_len++] = tolower((unsigned char)str[i]);
            }
        } else if (word_len > 0) {
            word[word_len] = '\0';
            if (word_exists(table, word, word_len)) {
                result = malloc(word_len + 1);
                if (result) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result, word, word_len);
                    result[word_len] = '\0';
                }
                free(word);
                free_hash_table(table);
                return result;
            }
            if (!add_word(table, word, word_len)) {
                free(word);
                free_hash_table(table);
                return NULL;
            }
            word_len = 0;
        }
    }

    free(word);
    free_hash_table(table);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "This is a test. This is only a test.",
        "Hello world, hello again.",
        "No repetition here.",
        "One two three one two three",
        "Multiple   spaces and punctuation!!!",
        "",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *repeated = find_first_repeated_word(test_strings[i]);
        printf("String: \"%s\"\n", test_strings[i]);
        if (repeated) {
            printf("First repeated word: \"%s\"\n", repeated);
            free(repeated);
        } else {
            printf("No repeated word found.\n");
        }
        printf("\n");
    }

    return 0;
}