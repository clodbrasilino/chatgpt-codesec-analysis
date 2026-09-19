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

unsigned int hash_string(const char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_SIZE;
}

WordNode **create_hash_table(void) {
    WordNode **table = calloc(HASH_SIZE, sizeof(WordNode *));
    if (!table) {
        return NULL;
    }
    return table;
}

void free_hash_table(WordNode **table) {
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

int word_exists(WordNode **table, const char *word) {
    if (!table || !word) return 0;
    unsigned int index = hash_string(word);
    WordNode *current = table[index];
    while (current) {
        if (strcmp(current->word, word) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int add_word(WordNode **table, const char *word) {
    if (!table || !word) return 0;
    unsigned int index = hash_string(word);
    WordNode *new_node = malloc(sizeof(WordNode));
    if (!new_node) {
        return 0;
    }
    new_node->word = malloc(strlen(word) + 1);
    if (!new_node->word) {
        free(new_node);
        return 0;
    }
    strcpy(new_node->word, word);
    new_node->next = table[index];
    table[index] = new_node;
    return 1;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char *find_first_repeated_word(const char *str) {
    if (!str || *str == '\0') {
        return NULL;
    }

    WordNode **table = create_hash_table();
    if (!table) {
        return NULL;
    }

    char word[MAX_WORD_LEN];
    int word_len = 0;
    char *result = NULL;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            if (word_len < MAX_WORD_LEN - 1) {
                word[word_len++] = tolower((unsigned char)str[i]);
            }
        } else if (word_len > 0) {
            word[word_len] = '\0';
            if (word_exists(table, word)) {
                result = malloc(strlen(word) + 1);
                if (result) {
                    strcpy(result, word);
                }
                free_hash_table(table);
                return result;
            }
            if (!add_word(table, word)) {
                free_hash_table(table);
                return NULL;
            }
            word_len = 0;
        }
    }

    if (word_len > 0) {
        word[word_len] = '\0';
        if (word_exists(table, word)) {
            result = malloc(strlen(word) + 1);
            if (result) {
                strcpy(result, word);
            }
        }
    }

    free_hash_table(table);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "This is a test string with a repeated word",
        "No repetition here",
        "Hello hello world",
        "One two three four one",
        "",
        "   ",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        char *repeated = find_first_repeated_word(test_strings[i]);
        printf("String: \"%s\"\n", test_strings[i]);
        if (repeated) {
            printf("First repeated word: \"%s\"\n", repeated);
            free(repeated);
        } else {
            printf("No repeated word found\n");
        }
        printf("\n");
    }

    return 0;
}