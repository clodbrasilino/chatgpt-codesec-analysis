#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 1024

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    size_t size;
} Collection;

static char *duplicate_string(const char *src) {
    if (!src) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(src);
    char *dst = malloc(len + 1);
    if (dst) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dst, src, len + 1);
    }
    return dst;
}

static size_t hash_function(const char *str, size_t size) {
    size_t hash = 5381;
    int c;
    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

static Collection* create_collection(size_t size) {
    Collection *col = malloc(sizeof(Collection));
    if (!col) return NULL;
    col->buckets = calloc(size, sizeof(Node *));
    if (!col->buckets) {
        free(col);
        return NULL;
    }
    col->size = size;
    return col;
}

static void destroy_collection(Collection *col) {
    if (!col) return;
    for (size_t i = 0; i < col->size; i++) {
        Node *current = col->buckets[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp->word);
            free(temp);
        }
    }
    free(col->buckets);
    free(col);
}

static int add_to_collection(Collection *col, const char *word) {
    if (!col || !word) return -1;
    size_t index = hash_function(word, col->size);
    Node *current = col->buckets[index];
    while (current) {
        if (strcmp(current->word, word) == 0) {
            return 0;
        }
        current = current->next;
    }
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return -1;
    new_node->word = duplicate_string(word);
    if (!new_node->word) {
        free(new_node);
        return -1;
    }
    new_node->next = col->buckets[index];
    col->buckets[index] = new_node;
    return 1;
}

char* remove_duplicate_words(const char *input) {
    if (!input) return NULL;
    
    char *input_copy = duplicate_string(input);
    if (!input_copy) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *result = calloc(len + 1, sizeof(char));
    if (!result) {
        free(input_copy);
        return NULL;
    }

    Collection *col = create_collection(HASH_SIZE);
    if (!col) {
        free(input_copy);
        free(result);
        return NULL;
    }

    const char *delimiters = " \t\n\r";
    char *ptr = input_copy;
    size_t result_len = 0;

    while (*ptr) {
        ptr += strspn(ptr, delimiters);
        if (!*ptr) break;
        
        size_t token_len = strcspn(ptr, delimiters);
        char has_next = (ptr[token_len] != '\0');
        ptr[token_len] = '\0';
        
        int added = add_to_collection(col, ptr);
        if (added == -1) {
            destroy_collection(col);
            free(input_copy);
            free(result);
            return NULL;
        }
        if (added == 1) {
            if (result_len > 0) {
                result[result_len++] = ' ';
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, ptr, token_len);
            result_len += token_len;
        }
        
        if (!has_next) break;
        ptr += token_len + 1;
    }

    result[result_len] = '\0';

    destroy_collection(col);
    free(input_copy);

    char *shrunk_result = realloc(result, result_len + 1);
    if (!shrunk_result && result_len > 0) {
        return result;
    }
    
    return shrunk_result ? shrunk_result : result;
}

int main(void) {
    const char *input = "programming in C is fun and C programming is very fun";
    char *unique_words = remove_duplicate_words(input);
    
    if (unique_words) {
        printf("%s\n", unique_words);
        free(unique_words);
    } else {
        fprintf(stderr, "Error processing the string.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}