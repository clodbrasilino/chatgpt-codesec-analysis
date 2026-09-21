#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define HASH_SIZE 101

typedef struct WordNode {
    char word[MAX_WORD_LEN];
    struct WordNode *next;
} WordNode;

unsigned int hash_word(const char *word) {
    unsigned int hash = 5381;
    int c;
    while ((c = *word++)) {
        hash = ((hash << 5) + hash) + tolower((unsigned char)c);
    }
    return hash % HASH_SIZE;
}

WordNode *create_node(const char *word) {
    WordNode *node = (WordNode *)malloc(sizeof(WordNode));
    if (node == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    while (len < MAX_WORD_LEN - 1 && word[len] != '\0') {
        len++;
    }
    
    size_t i;
    for (i = 0; i < len; i++) {
        node->word[i] = word[i];
    }
    node->word[len] = '\0';
    node->next = NULL;
    return node;
}

void free_table(WordNode *table[]) {
    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        WordNode *current = table[i];
        while (current != NULL) {
            WordNode *temp = current;
            current = current->next;
            free(temp);
        }
        table[i] = NULL;
    }
}

int is_word_char(char c) {
    return isalnum((unsigned char)c) || c == '\'';
}

char *find_first_repeated_word(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    WordNode *hash_table[HASH_SIZE] = {0};
    const char *p = str;
    const char *word_start = NULL;
    size_t word_len = 0;

    while (*p != '\0') {
        if (is_word_char(*p)) {
            if (word_start == NULL) {
                word_start = p;
                word_len = 0;
            }
            word_len++;
            if (word_len >= MAX_WORD_LEN) {
                word_start = NULL;
                word_len = 0;
                while (is_word_char(*p) && *p != '\0') {
                    p++;
                }
                if (*p == '\0') break;
                continue;
            }
        } else {
            if (word_start != NULL) {
                if (word_len > 0) {
                    char word[MAX_WORD_LEN];
                    size_t copy_len = word_len;
                    if (copy_len >= MAX_WORD_LEN) {
                        copy_len = MAX_WORD_LEN - 1;
                    }
                    memcpy(word, word_start, copy_len);
                    word[copy_len] = '\0';
                    
                    unsigned int hash = hash_word(word);
                    WordNode *current = hash_table[hash];
                    
                    while (current != NULL) {
                        if (strcasecmp(current->word, word) == 0) {
                            char *result = (char *)malloc(copy_len + 1);
                            if (result != NULL) {
                                memcpy(result, word, copy_len);
                                result[copy_len] = '\0';
                            }
                            free_table(hash_table);
                            return result;
                        }
                        current = current->next;
                    }
                    
                    WordNode *new_node = create_node(word);
                    if (new_node == NULL) {
                        free_table(hash_table);
                        return NULL;
                    }
                    new_node->next = hash_table[hash];
                    hash_table[hash] = new_node;
                }
                word_start = NULL;
                word_len = 0;
            }
        }
        p++;
    }
    
    if (word_start != NULL && word_len > 0) {
        char word[MAX_WORD_LEN];
        size_t copy_len = word_len;
        if (copy_len >= MAX_WORD_LEN) {
            copy_len = MAX_WORD_LEN - 1;
        }
        memcpy(word, word_start, copy_len);
        word[copy_len] = '\0';
        
        unsigned int hash = hash_word(word);
        WordNode *current = hash_table[hash];
        
        while (current != NULL) {
            if (strcasecmp(current->word, word) == 0) {
                char *result = (char *)malloc(copy_len + 1);
                if (result != NULL) {
                    memcpy(result, word, copy_len);
                    result[copy_len] = '\0';
                }
                free_table(hash_table);
                return result;
            }
            current = current->next;
        }
    }
    
    free_table(hash_table);
    return NULL;
}

int main(void) {
    const char *test_strings[] = {
        "This is a test. This is only a test.",
        "Hello world, hello again.",
        "One two three four five.",
        "The cat and the dog and the bird.",
        "No repetition here.",
        "",
        "word word word",
        "Case CASE case test",
        NULL
    };
    
    int i;
    for (i = 0; test_strings[i] != NULL; i++) {
        char *result = find_first_repeated_word(test_strings[i]);
        printf("String: \"%s\"\n", test_strings[i]);
        if (result != NULL) {
            printf("First repeated word: \"%s\"\n\n", result);
            free(result);
        } else {
            printf("No repeated word found.\n\n");
        }
    }
    
    return 0;
}