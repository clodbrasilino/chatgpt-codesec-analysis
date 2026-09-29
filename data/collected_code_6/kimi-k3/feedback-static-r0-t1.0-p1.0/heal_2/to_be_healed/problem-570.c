#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_words_containing(char **list, int size, const char *substring) {
    int i, j;
    int removed = 0;
    
    if (list == NULL || substring == NULL || size < 0) {
        return -1;
    }
    
    for (i = 0, j = 0; i < size; i++) {
        if (list[i] == NULL) {
            continue;
        }
        if (strstr(list[i], substring) != NULL) {
            free(list[i]);
            list[i] = NULL;
            removed++;
        } else {
            list[j] = list[i];
            if (i != j) {
                list[i] = NULL;
            }
            j++;
        }
    }
    
    return j;
}

int main(void) {
    char **words;
    int size = 6;
    int new_size;
    int i;
    
    words = malloc(size * sizeof(char *));
    if (words == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    words[0] = malloc(strlen("apple") + 1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    words[1] = malloc(strlen("banana") + 1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    words[2] = malloc(strlen("cherry") + 1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    words[3] = malloc(strlen("date") + 1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    words[4] = malloc(strlen("elderberry") + 1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    words[5] = malloc(strlen("fig") + 1);
    
    if (words[0] == NULL || words[1] == NULL || words[2] == NULL ||
        words[3] == NULL || words[4] == NULL || words[5] == NULL) {
        for (i = 0; i < size; i++) {
            free(words[i]);
        }
        free(words);
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    snprintf(words[0], strlen("apple") + 1, "apple");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    snprintf(words[1], strlen("banana") + 1, "banana");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    snprintf(words[2], strlen("cherry") + 1, "cherry");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    snprintf(words[3], strlen("date") + 1, "date");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    snprintf(words[4], strlen("elderberry") + 1, "elderberry");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    snprintf(words[5], strlen("fig") + 1, "fig");
    
    printf("Original list:\n");
    for (i = 0; i < size; i++) {
        printf("%s\n", words[i]);
    }
    
    new_size = remove_words_containing(words, size, "an");
    
    if (new_size < 0) {
        for (i = 0; i < size; i++) {
            free(words[i]);
        }
        free(words);
        return 1;
    }
    
    printf("\nList after removing words containing 'an':\n");
    for (i = 0; i < new_size; i++) {
        printf("%s\n", words[i]);
    }
    
    for (i = 0; i < size; i++) {
        free(words[i]);
    }
    free(words);
    
    return 0;
}