#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ALPHABET_SIZE 256

typedef struct {
    size_t count;
    size_t capacity;
    char **items;
} AnagramList;

static int init_anagram_list(AnagramList *list, size_t initial_capacity)
{
    if (list == NULL || initial_capacity == 0) {
        return -1;
    }
    
    list->items = (char **)calloc(initial_capacity, sizeof(char *));
    if (list->items == NULL) {
        return -1;
    }
    
    list->count = 0;
    list->capacity = initial_capacity;
    return 0;
}

static void free_anagram_list(AnagramList *list)
{
    if (list == NULL) {
        return;
    }
    
    if (list->items != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            free(list->items[i]);
        }
        free(list->items);
        list->items = NULL;
    }
    
    list->count = 0;
    list->capacity = 0;
}

static int resize_anagram_list(AnagramList *list)
{
    if (list == NULL || list->items == NULL) {
        return -1;
    }
    
    if (list->capacity > SIZE_MAX / 2) {
        return -1;
    }
    
    size_t new_capacity = list->capacity * 2;
    char **new_items = (char **)realloc(list->items, new_capacity * sizeof(char *));
    
    if (new_items == NULL) {
        return -1;
    }
    
    list->items = new_items;
    list->capacity = new_capacity;
    return 0;
}

static int add_to_anagram_list(AnagramList *list, const char *str)
{
    if (list == NULL || str == NULL) {
        return -1;
    }
    
    if (list->count >= list->capacity) {
        if (resize_anagram_list(list) != 0) {
            return -1;
        }
    }
    
    size_t len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        return -1;
    }
    
    list->items[list->count] = (char *)malloc(len + 1);
    
    if (list->items[list->count] == NULL) {
        return -1;
    }
    
    strncpy(list->items[list->count], str, len);
    list->items[list->count][len] = '\0';
    list->count++;
    return 0;
}

static void get_char_frequency(const char *str, int *freq, size_t freq_size)
{
    if (str == NULL || freq == NULL || freq_size < ALPHABET_SIZE) {
        return;
    }
    
    memset(freq, 0, ALPHABET_SIZE * sizeof(int));
    
    while (*str != '\0') {
        unsigned char c = (unsigned char)*str;
        freq[c]++;
        str++;
    }
}

static int are_anagrams(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    
    size_t len1 = strnlen(str1, SIZE_MAX);
    size_t len2 = strnlen(str2, SIZE_MAX);
    
    if (len1 == SIZE_MAX || len2 == SIZE_MAX) {
        return 0;
    }
    
    if (len1 != len2) {
        return 0;
    }
    
    int freq1[ALPHABET_SIZE];
    int freq2[ALPHABET_SIZE];
    
    get_char_frequency(str1, freq1, ALPHABET_SIZE);
    get_char_frequency(str2, freq2, ALPHABET_SIZE);
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (freq1[i] != freq2[i]) {
            return 0;
        }
    }
    
    return 1;
}

int find_anagrams(const char *target, const char **word_list, size_t list_size, AnagramList *result)
{
    if (target == NULL || word_list == NULL || result == NULL || list_size == 0) {
        return -1;
    }
    
    if (init_anagram_list(result, list_size) != 0) {
        return -1;
    }
    
    for (size_t i = 0; i < list_size; i++) {
        if (word_list[i] == NULL) {
            continue;
        }
        
        if (are_anagrams(target, word_list[i])) {
            if (add_to_anagram_list(result, word_list[i]) != 0) {
                free_anagram_list(result);
                return -1;
            }
        }
    }
    
    return 0;
}

int main(void)
{
    const char *target = "listen";
    const char *words[] = {
        "enlist",
        "silent",
        "hello",
        "inlets",
        "world",
        "tinsel",
        "banana"
    };
    size_t word_count = sizeof(words) / sizeof(words[0]);
    
    AnagramList result;
    
    if (find_anagrams(target, words, word_count, &result) != 0) {
        fprintf(stderr, "Error finding anagrams\n");
        return EXIT_FAILURE;
    }
    
    printf("Anagrams of '%s':\n", target);
    for (size_t i = 0; i < result.count; i++) {
        printf("%s\n", result.items[i]);
    }
    
    free_anagram_list(&result);
    
    return EXIT_SUCCESS;
}