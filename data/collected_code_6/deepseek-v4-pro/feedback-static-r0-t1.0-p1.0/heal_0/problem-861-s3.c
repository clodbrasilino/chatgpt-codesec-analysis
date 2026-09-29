#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct {
    char **words;
    int *counts;
    int size;
    int capacity;
} AnagramResult;

void init_anagram_result(AnagramResult *result, int capacity) {
    result->words = malloc(sizeof(char*) * capacity);
    result->counts = malloc(sizeof(int) * capacity);
    result->size = 0;
    result->capacity = capacity;
    if (!result->words || !result->counts) {
        free(result->words);
        free(result->counts);
        result->words = NULL;
        result->counts = NULL;
        result->capacity = 0;
    }
}

void add_anagram_result(AnagramResult *result, char *word, int count) {
    if (result->size >= result->capacity) {
        int new_capacity = result->capacity * 2;
        char **new_words = realloc(result->words, sizeof(char*) * new_capacity);
        int *new_counts = realloc(result->counts, sizeof(int) * new_capacity);
        if (!new_words || !new_counts) {
            free(new_words);
            free(new_counts);
            return;
        }
        result->words = new_words;
        result->counts = new_counts;
        result->capacity = new_capacity;
    }
    result->words[result->size] = word;
    result->counts[result->size] = count;
    result->size++;
}

void free_anagram_result(AnagramResult *result) {
    free(result->words);
    free(result->counts);
    result->words = NULL;
    result->counts = NULL;
    result->size = 0;
    result->capacity = 0;
}

void count_chars(const char *str, int *counts) {
    memset(counts, 0, sizeof(int) * ALPHABET_SIZE);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            counts[str[i] - 'a']++;
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            counts[str[i] - 'A']++;
        }
    }
}

int is_anagram(const char *str1, const char *str2) {
    int counts1[ALPHABET_SIZE];
    int counts2[ALPHABET_SIZE];
    count_chars(str1, counts1);
    count_chars(str2, counts2);
    return memcmp(counts1, counts2, sizeof(int) * ALPHABET_SIZE) == 0;
}

AnagramResult find_anagrams(char **word_list, int list_size, const char *target) {
    AnagramResult result;
    init_anagram_result(&result, list_size > 0 ? list_size : 1);
    
    if (!result.words || !result.counts) {
        return result;
    }
    
    int target_counts[ALPHABET_SIZE];
    count_chars(target, target_counts);
    
    for (int i = 0; i < list_size; i++) {
        if (word_list[i] && strcmp(word_list[i], target) != 0) {
            int word_counts[ALPHABET_SIZE];
            count_chars(word_list[i], word_counts);
            if (memcmp(target_counts, word_counts, sizeof(int) * ALPHABET_SIZE) == 0) {
                add_anagram_result(&result, word_list[i], 1);
            }
        }
    }
    
    return result;
}

void print_anagram_result(AnagramResult *result) {
    for (int i = 0; i < result->size; i++) {
        printf("%s\n", result->words[i]);
    }
}

int main(void) {
    char *words[] = {"listen", "silent", "enlist", "google", "inlets", "banana"};
    int size = sizeof(words) / sizeof(words[0]);
    const char *target = "listen";
    
    AnagramResult result = find_anagrams(words, size, target);
    
    printf("Anagrams of '%s':\n", target);
    print_anagram_result(&result);
    
    free_anagram_result(&result);
    
    char *words2[] = {"evil", "vile", "live", "veil", "levi", "hello", "world"};
    int size2 = sizeof(words2) / sizeof(words2[0]);
    const char *target2 = "evil";
    
    AnagramResult result2 = find_anagrams(words2, size2, target2);
    
    printf("\nAnagrams of '%s':\n", target2);
    print_anagram_result(&result2);
    
    free_anagram_result(&result2);
    
    return 0;
}