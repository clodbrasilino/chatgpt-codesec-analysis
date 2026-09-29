#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    size_t count;
} Element;

typedef struct {
    Element *elements;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(void) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    
    dict->size = 0;
    dict->capacity = 16;
    dict->elements = malloc(dict->capacity * sizeof(Element));
    
    if (!dict->elements) {
        free(dict);
        return NULL;
    }
    
    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    
    if (dict->elements) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->elements[i].word);
        }
        free(dict->elements);
    }
    free(dict);
}

int add_element(Dictionary *dict, const char *word) {
    if (!dict || !word) {
        return 0;
    }
    
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->elements[i].word, word) == 0) {
            dict->elements[i].count++;
            return 1;
        }
    }
    
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        Element *new_elements = realloc(dict->elements, new_capacity * sizeof(Element));
        if (!new_elements) {
            return 0;
        }
        dict->elements = new_elements;
        dict->capacity = new_capacity;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *word_copy = malloc(strlen(word) + 1);
    if (!word_copy) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(word_copy, word);
    
    dict->elements[dict->size].word = word_copy;
    dict->elements[dict->size].count = 1;
    dict->size++;
    
    return 1;
}

int compare_elements(const void *a, const void *b) {
    const Element *elem_a = (const Element *)a;
    const Element *elem_b = (const Element *)b;
    
    if (elem_a->count < elem_b->count) {
        return 1;
    }
    if (elem_a->count > elem_b->count) {
        return -1;
    }
    return strcmp(elem_a->word, elem_b->word);
}

void find_most_common_elements(const char *text) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (!text || strlen(text) == 0) {
        printf("The provided text is empty or null.\n");
        return;
    }
    
    Dictionary *dict = create_dictionary();
    if (!dict) {
        fprintf(stderr, "Error: Memory allocation failed for dictionary.\n");
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *text_copy = malloc(strlen(text) + 1);
    if (!text_copy) {
        fprintf(stderr, "Error: Memory allocation failed for text processing.\n");
        free_dictionary(dict);
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(text_copy, text);
    
    for (size_t i = 0; text_copy[i]; i++) {
        text_copy[i] = (char)tolower((unsigned char)text_copy[i]);
    }
    
    const char *delimiters = " \t\n\r\v\f.,;:!?()[]{}\"'\\/";
    char *token = strtok(text_copy, delimiters);
    
    while (token) {
        if (!add_element(dict, token)) {
            fprintf(stderr, "Error: Memory allocation failed during element addition.\n");
            free(text_copy);
            free_dictionary(dict);
            return;
        }
        token = strtok(NULL, delimiters);
    }
    
    free(text_copy);
    
    if (dict->size == 0) {
        printf("No valid elements found in the text.\n");
        free_dictionary(dict);
        return;
    }
    
    qsort(dict->elements, dict->size, sizeof(Element), compare_elements);
    
    size_t max_count = dict->elements[0].count;
    printf("Most common element(s) appearing %zu times:\n", max_count);
    
    for (size_t i = 0; i < dict->size; i++) {
        if (dict->elements[i].count == max_count) {
            printf("- '%s'\n", dict->elements[i].word);
        } else {
            break;
        }
    }
    
    free_dictionary(dict);
}

int main(void) {
    const char *sample_text = "C programming is powerful. C is a compiled language, and C programming is widely used.";
    
    printf("Text: \"%s\"\n\n", sample_text);
    find_most_common_elements(sample_text);
    
    return 0;
}