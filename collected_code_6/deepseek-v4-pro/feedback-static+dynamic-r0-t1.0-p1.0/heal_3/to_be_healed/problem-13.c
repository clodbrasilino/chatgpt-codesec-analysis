#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAX_WORD_LEN 100
#define INITIAL_CAPACITY 100
#define TOP_N 10

typedef struct {
    char *word;
    int count;
} WordCount;

typedef struct {
    WordCount *items;
    int size;
    int capacity;
} WordCountArray;

void init_array(WordCountArray *arr) {
    arr->capacity = INITIAL_CAPACITY;
    arr->size = 0;
    arr->items = (WordCount *)malloc(sizeof(WordCount) * arr->capacity);
    if (arr->items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void free_array(WordCountArray *arr) {
    if (arr == NULL) {
        return;
    }
    for (int i = 0; i < arr->size; i++) {
        free(arr->items[i].word);
    }
    free(arr->items);
    arr->items = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void add_word(WordCountArray *arr, const char *word) {
    if (word == NULL) {
        return;
    }
    
    for (int i = 0; i < arr->size; i++) {
        if (strcmp(arr->items[i].word, word) == 0) {
            arr->items[i].count++;
            return;
        }
    }

    if (arr->size >= arr->capacity) {
        size_t new_capacity = arr->capacity * 2;
        if (new_capacity > (size_t)(-1) / sizeof(WordCount)) {
            fprintf(stderr, "Capacity overflow\n");
            free_array(arr);
            exit(EXIT_FAILURE);
        }
        WordCount *new_items = (WordCount *)realloc(arr->items, sizeof(WordCount) * new_capacity);
        if (new_items == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            free_array(arr);
            exit(EXIT_FAILURE);
        }
        arr->items = new_items;
        arr->capacity = (int)new_capacity;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    if (word_len >= MAX_WORD_LEN) {
        return;
    }

    arr->items[arr->size].word = (char *)malloc(word_len + 1);
    if (arr->items[arr->size].word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_array(arr);
        exit(EXIT_FAILURE);
    }
    if (word_len + 1 <= MAX_WORD_LEN + 1) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr->items[arr->size].word, word, word_len + 1);
    } else {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(arr->items[arr->size].word, word, MAX_WORD_LEN);
        arr->items[arr->size].word[MAX_WORD_LEN] = '\0';
    }
    arr->items[arr->size].count = 1;
    arr->size++;
}

int compare_word_counts(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    return wb->count - wa->count;
}

void print_top_words(WordCountArray *arr, int n) {
    if (n > arr->size) {
        n = arr->size;
    }
    qsort(arr->items, arr->size, sizeof(WordCount), compare_word_counts);
    for (int i = 0; i < n; i++) {
        printf("%s: %d\n", arr->items[i].word, arr->items[i].count);
    }
}

void sanitize_word(char *word) {
    if (word == NULL) {
        return;
    }
    word[MAX_WORD_LEN] = '\0';
    /* Possible weaknesses found:
     *  Array index 'i' is used before limits check. [arrayIndexThenCheck]
     */
    for (size_t i = 0; word[i] != '\0' && i < MAX_WORD_LEN; i++) {
        word[i] = tolower((unsigned char)word[i]);
    }
}

void process_dictionary(const char *filename) {
    if (filename == NULL) {
        fprintf(stderr, "Invalid filename\n");
        exit(EXIT_FAILURE);
    }

    /* Possible weaknesses found:
     * Flawfinder fopen: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    WordCountArray arr;
    init_array(&arr);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN + 1];
    int scan_result;
    /* Possible weaknesses found:
     * Flawfinder fscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    while ((scan_result = fscanf(file, "%100s", word)) == 1) {
        if (feof(file)) {
            break;
        }
        word[MAX_WORD_LEN] = '\0';
        sanitize_word(word);
        add_word(&arr, word);
    }

    if (scan_result == 0 && !feof(file)) {
        fprintf(stderr, "Error reading file\n");
        int c;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = fgetc(file)) != EOF && c != '\n');
    }

    fclose(file);
    print_top_words(&arr, TOP_N);
    free_array(&arr);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <dictionary_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    process_dictionary(argv[1]);
    return EXIT_SUCCESS;
}