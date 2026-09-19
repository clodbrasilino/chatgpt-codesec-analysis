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

static unsigned int hash_string(const char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_SIZE;
}

static char *strdup_lower(const char *start, size_t len) {
    char *word = (char *)malloc(len + 1);
    if (!word) return NULL;
    for (size_t i = 0; i < len; i++) {
        word[i] = (char)tolower((unsigned char)start[i]);
    }
    word[len] = '\0';
    return word;
}

static void free_table(WordNode **table) {
    for (int i = 0; i < HASH_SIZE; i++) {
        WordNode *current = table[i];
        while (current) {
            WordNode *next = current->next;
            free(current->word);
            free(current);
            current = next;
        }
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char *find_first_repeated_word(const char *str) {
    if (!str) return NULL;

    WordNode *hash_table[HASH_SIZE] = {0};
    const char *p = str;
    const char *word_start = NULL;
    size_t word_len = 0;

    while (*p) {
        if (isalpha((unsigned char)*p)) {
            if (!word_start) {
                word_start = p;
                word_len = 1;
            } else {
                word_len++;
            }
        } else {
            if (word_start) {
                char *word = strdup_lower(word_start, word_len);
                if (!word) {
                    free_table(hash_table);
                    return NULL;
                }

                unsigned int index = hash_string(word);
                WordNode *current = hash_table[index];
                while (current) {
                    if (strcmp(current->word, word) == 0) {
                        char *result = (char *)malloc(word_len + 1);
                        if (!result) {
                            free(word);
                            free_table(hash_table);
                            return NULL;
                        }
                        memcpy(result, word_start, word_len);
                        result[word_len] = '\0';
                        free(word);
                        free_table(hash_table);
                        return result;
                    }
                    current = current->next;
                }

                WordNode *new_node = (WordNode *)malloc(sizeof(WordNode));
                if (!new_node) {
                    free(word);
                    free_table(hash_table);
                    return NULL;
                }
                new_node->word = word;
                new_node->next = hash_table[index];
                hash_table[index] = new_node;

                word_start = NULL;
                word_len = 0;
            }
        }
        p++;
    }

    if (word_start) {
        char *word = strdup_lower(word_start, word_len);
        if (!word) {
            free_table(hash_table);
            return NULL;
        }

        unsigned int index = hash_string(word);
        WordNode *current = hash_table[index];
        while (current) {
            if (strcmp(current->word, word) == 0) {
                char *result = (char *)malloc(word_len + 1);
                if (!result) {
                    free(word);
                    free_table(hash_table);
                    return NULL;
                }
                memcpy(result, word_start, word_len);
                result[word_len] = '\0';
                free(word);
                free_table(hash_table);
                return result;
            }
            current = current->next;
        }
        free(word);
    }

    free_table(hash_table);
    return NULL;
}

int main(void) {
    const char *test1 = "This is a test. This test is only a test.";
    const char *test2 = "Hello world hello";
    const char *test3 = "No repetition here";
    const char *test4 = "";
    const char *test5 = "One two three four one two";

    char *result;

    result = find_first_repeated_word(test1);
    printf("Test 1: %s\n", result ? result : "None");
    free(result);

    result = find_first_repeated_word(test2);
    printf("Test 2: %s\n", result ? result : "None");
    free(result);

    result = find_first_repeated_word(test3);
    printf("Test 3: %s\n", result ? result : "None");
    free(result);

    result = find_first_repeated_word(test4);
    printf("Test 4: %s\n", result ? result : "None");
    free(result);

    result = find_first_repeated_word(test5);
    printf("Test 5: %s\n", result ? result : "None");
    free(result);

    return 0;
}