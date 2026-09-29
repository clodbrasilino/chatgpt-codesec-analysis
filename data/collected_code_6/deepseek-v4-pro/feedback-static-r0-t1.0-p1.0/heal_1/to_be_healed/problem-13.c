#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    for (int i = 0; i < arr->size; i++) {
        free(arr->items[i].word);
    }
    free(arr->items);
}

void add_word(WordCountArray *arr, const char *word) {
    for (int i = 0; i < arr->size; i++) {
        if (strcmp(arr->items[i].word, word) == 0) {
            arr->items[i].count++;
            return;
        }
    }

    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        WordCount *new_items = (WordCount *)realloc(arr->items, sizeof(WordCount) * arr->capacity);
        if (new_items == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            free_array(arr);
            exit(EXIT_FAILURE);
        }
        arr->items = new_items;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    arr->items[arr->size].word = (char *)malloc(strlen(word) + 1);
    if (arr->items[arr->size].word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_array(arr);
        exit(EXIT_FAILURE);
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(arr->items[arr->size].word, word);
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

void process_dictionary(const char *filename) {
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
    char word[MAX_WORD_LEN];
    /* Possible weaknesses found:
     * Flawfinder fscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    while (fscanf(file, "%99s", word) == 1) {
        for (int i = 0; word[i]; i++) {
            word[i] = tolower((unsigned char)word[i]);
        }
        add_word(&arr, word);
    }

    fclose(file);
    print_top_words(&arr, TOP_N);
    free_array(&arr);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <dictionary_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    process_dictionary(argv[1]);
    return EXIT_SUCCESS;
}