#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct WordNode {
    char *word;
    struct WordNode *next;
} WordNode;

typedef struct {
    WordNode **buckets;
    size_t size;
} HashSet;

static unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++) != '\0') {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

static HashSet *hashset_create(size_t size) {
    HashSet *set = malloc(sizeof(HashSet));
    if (!set) return NULL;
    set->size = size;
    set->buckets = calloc(size, sizeof(WordNode *));
    if (!set->buckets) {
        free(set);
        return NULL;
    }
    return set;
}

static int hashset_contains(HashSet *set, const char *word) {
    unsigned long index = hash_string(word) % set->size;
    WordNode *node = set->buckets[index];
    while (node) {
        if (strcmp(node->word, word) == 0) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

static int hashset_add(HashSet *set, const char *word) {
    if (hashset_contains(set, word)) {
        return 0;
    }
    unsigned long index = hash_string(word) % set->size;
    WordNode *node = malloc(sizeof(WordNode));
    if (!node) return -1;
    node->word = strdup(word);
    if (!node->word) {
        free(node);
        return -1;
    }
    node->next = set->buckets[index];
    set->buckets[index] = node;
    return 1;
}

static void hashset_free(HashSet *set) {
    if (!set) return;
    if (set->buckets) {
        for (size_t i = 0; i < set->size; i++) {
            WordNode *node = set->buckets[i];
            while (node) {
                WordNode *next = node->next;
                free(node->word);
                free(node);
                node = next;
            }
        }
        free(set->buckets);
    }
    free(set);
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static char **split_words(const char *str, int *count) {
    int capacity = 16;
    int word_count = 0;
    char **words = malloc((size_t)capacity * sizeof(char *));
    if (!words) {
        *count = 0;
        return NULL;
    }

    const char *p = str;
    while (*p) {
        while (*p && isspace((unsigned char)*p)) p++;
        if (*p == '\0') break;
        
        const char *start = p;
        while (*p && !isspace((unsigned char)*p)) p++;
        
        size_t length = (size_t)(p - start);
        
        char *word = malloc(length + 1);
        if (!word) {
            for (int i = 0; i < word_count; i++) free(words[i]);
            free(words);
            *count = 0;
            return NULL;
        }
        
        if (length > 0) {
            size_t dest_size = length + 1;
            if (length < dest_size) {
                memcpy(word, start, length);
            }
        }
        word[length] = '\0';
        
        if (word_count >= capacity) {
            capacity *= 2;
            char **new_words = realloc(words, (size_t)capacity * sizeof(char *));
            if (!new_words) {
                free(word);
                for (int i = 0; i < word_count; i++) free(words[i]);
                free(words);
                *count = 0;
                return NULL;
            }
            words = new_words;
        }
        words[word_count++] = word;
    }
    
    *count = word_count;
    return words;
}

char *remove_duplicate_words(const char *input) {
    if (!input) return NULL;
    
    if (*input == '\0') {
        char *result = malloc(1);
        if (result) result[0] = '\0';
        return result;
    }
    
    int word_count;
    char **words = split_words(input, &word_count);
    if (!words) return NULL;
    
    if (word_count == 0) {
        free(words);
        char *result = malloc(1);
        if (result) result[0] = '\0';
        return result;
    }
    
    HashSet *set = hashset_create(64);
    if (!set) {
        for (int i = 0; i < word_count; i++) free(words[i]);
        free(words);
        return NULL;
    }
    
    size_t total_length = 0;
    int unique_count = 0;
    char **unique_words = malloc((size_t)word_count * sizeof(char *));
    if (!unique_words) {
        for (int i = 0; i < word_count; i++) free(words[i]);
        free(words);
        hashset_free(set);
        return NULL;
    }
    
    for (int i = 0; i < word_count; i++) {
        int add_result = hashset_add(set, words[i]);
        if (add_result == 1) {
            unique_words[unique_count++] = words[i];
            size_t word_len = strlen(words[i]);
            if (word_len > SIZE_MAX - 1 || word_len > SIZE_MAX - 1 - total_length) {
                for (int j = 0; j < word_count; j++) free(words[j]);
                free(words);
                free(unique_words);
                hashset_free(set);
                return NULL;
            }
            total_length += word_len + 1;
        } else if (add_result == -1) {
            for (int j = 0; j < word_count; j++) free(words[j]);
            free(words);
            free(unique_words);
            hashset_free(set);
            return NULL;
        }
    }
    
    for (int i = 0; i < unique_count; i++) {
        words[i] = unique_words[i];
    }
    
    if (unique_count == 0 || total_length == 0) {
        for (int i = 0; i < word_count; i++) free(words[i]);
        free(words);
        free(unique_words);
        hashset_free(set);
        char *result = malloc(1);
        if (result) result[0] = '\0';
        return result;
    }
    
    char *result = malloc(total_length);
    if (!result) {
        for (int i = 0; i < word_count; i++) free(words[i]);
        free(words);
        free(unique_words);
        hashset_free(set);
        return NULL;
    }
    
    size_t offset = 0;
    for (int i = 0; i < unique_count; i++) {
        size_t len = strlen(unique_words[i]);
        if (offset + len < total_length) {
            memcpy(result + offset, unique_words[i], len);
            offset += len;
        }
        if (i < unique_count - 1 && offset + 1 <= total_length) {
            result[offset] = ' ';
            offset++;
        }
    }
    result[offset] = '\0';
    
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
    free(unique_words);
    hashset_free(set);
    
    return result;
}

int main(void) {
    const char *test1 = "hello world hello again world";
    char *result1 = remove_duplicate_words(test1);
    if (result1) {
        printf("Input: %s\nOutput: %s\n", test1, result1);
        free(result1);
    }
    
    const char *test2 = "the quick brown fox jumps over the lazy dog";
    char *result2 = remove_duplicate_words(test2);
    if (result2) {
        printf("Input: %s\nOutput: %s\n", test2, result2);
        free(result2);
    }
    
    const char *test3 = "single";
    char *result3 = remove_duplicate_words(test3);
    if (result3) {
        printf("Input: %s\nOutput: %s\n", test3, result3);
        free(result3);
    }
    
    const char *test4 = "";
    char *result4 = remove_duplicate_words(test4);
    if (result4) {
        printf("Input: %s\nOutput: %s\n", test4, result4);
        free(result4);
    }
    
    const char *test5 = "Python Exercises Practice Solution";
    char *result5 = remove_duplicate_words(test5);
    if (result5) {
        printf("Input: %s\nOutput: %s\n", test5, result5);
        free(result5);
    }
    
    const char *test6 = "a b c a b c d e f";
    char *result6 = remove_duplicate_words(test6);
    if (result6) {
        printf("Input: %s\nOutput: %s\n", test6, result6);
        free(result6);
    }
    
    return 0;
}