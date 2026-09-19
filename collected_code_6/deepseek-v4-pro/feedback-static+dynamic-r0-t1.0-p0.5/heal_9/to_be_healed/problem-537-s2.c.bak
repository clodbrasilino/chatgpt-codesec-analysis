#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define HASH_SIZE 1000

typedef struct WordNode {
    char *word;
    char *original;
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

static char *strdup_original(const char *start, size_t len) {
    char *word = (char *)malloc(len + 1);
    if (!word) return NULL;
    memcpy(word, start, len);
    word[len] = '\0';
    return word;
}

static void free_table(WordNode **table) {
    if (!table) return;
    for (int i = 0; i < HASH_SIZE; i++) {
        WordNode *current = table[i];
        while (current) {
            WordNode *next = current->next;
            free(current->word);
            free(current->original);
            free(current);
            current = next;
        }
        table[i] = NULL;
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

    while (1) {
        if (*p && isalpha((unsigned char)*p)) {
            if (!word_start) {
                word_start = p;
                word_len = 1;
            } else {
                word_len++;
            }
        } else {
            if (word_start) {
                char *lower_word = strdup_lower(word_start, word_len);
                if (!lower_word) {
                    free_table(hash_table);
                    return NULL;
                }

                unsigned int index = hash_string(lower_word);
                WordNode *current = hash_table[index];
                while (current) {
                    if (strcmp(current->word, lower_word) == 0) {
                        char *result = strdup_original(current->original, strlen(current->original));
                        free(lower_word);
                        free_table(hash_table);
                        return result;
                    }
                    current = current->next;
                }

                char *original_word = strdup_original(word_start, word_len);
                if (!original_word) {
                    free(lower_word);
                    free_table(hash_table);
                    return NULL;
                }

                WordNode *new_node = (WordNode *)malloc(sizeof(WordNode));
                if (!new_node) {
                    free(lower_word);
                    free(original_word);
                    free_table(hash_table);
                    return NULL;
                }
                new_node->word = lower_word;
                new_node->original = original_word;
                new_node->next = hash_table[index];
                hash_table[index] = new_node;

                word_start = NULL;
                word_len = 0;
            }
        }
        if (*p == '\0') break;
        p++;
    }

    free_table(hash_table);
    return NULL;
}

int main(void) {
    const char *test1 = "This is a test. This is only a test.";
    const char *test2 = "No repetition here.";
    const char *test3 = "Hello hello HELLO world";
    const char *test4 = "";
    const char *test5 = "One two three four five six seven eight nine ten one two";

    char *result1 = find_first_repeated_word(test1);
    char *result2 = find_first_repeated_word(test2);
    char *result3 = find_first_repeated_word(test3);
    char *result4 = find_first_repeated_word(test4);
    char *result5 = find_first_repeated_word(test5);

    printf("Test 1: %s\n", result1 ? result1 : "None");
    printf("Test 2: %s\n", result2 ? result2 : "None");
    printf("Test 3: %s\n", result3 ? result3 : "None");
    printf("Test 4: %s\n", result4 ? result4 : "None");
    printf("Test 5: %s\n", result5 ? result5 : "None");

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);

    return 0;
}