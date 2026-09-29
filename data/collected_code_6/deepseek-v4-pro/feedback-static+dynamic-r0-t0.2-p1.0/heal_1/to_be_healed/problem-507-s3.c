#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordList;

int remove_word(WordList *list, const char *target) {
    if (list == NULL || target == NULL) {
        return -1;
    }
    
    int i, j;
    int removed = 0;
    
    for (i = 0; i < list->count; i++) {
        if (strcmp(list->words[i], target) == 0) {
            for (j = i; j < list->count - 1; j++) {
                /* Possible weaknesses found:
                 * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
                 */
                strcpy(list->words[j], list->words[j + 1]);
            }
            list->count--;
            i--;
            removed++;
        }
    }
    
    return removed;
}

int remove_words(WordList *list, const char *targets[], int target_count) {
    if (list == NULL || targets == NULL || target_count <= 0) {
        return -1;
    }
    
    int total_removed = 0;
    int i;
    
    for (i = 0; i < target_count; i++) {
        if (targets[i] != NULL) {
            int result = remove_word(list, targets[i]);
            if (result > 0) {
                total_removed += result;
            }
        }
    }
    
    return total_removed;
}

void print_list(const WordList *list) {
    if (list == NULL) {
        return;
    }
    
    int i;
    for (i = 0; i < list->count; i++) {
        printf("%s", list->words[i]);
        if (i < list->count - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(void) {
    WordList list;
    list.count = 0;
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(list.words[list.count++], "apple");
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(list.words[list.count++], "banana");
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(list.words[list.count++], "cherry");
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(list.words[list.count++], "apple");
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(list.words[list.count++], "date");
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(list.words[list.count++], "elderberry");
    
    printf("Original list: ");
    print_list(&list);
    
    const char *targets[] = {"apple", "date"};
    int target_count = sizeof(targets) / sizeof(targets[0]);
    
    int removed = remove_words(&list, targets, target_count);
    
    printf("Removed %d word(s)\n", removed);
    printf("Updated list: ");
    print_list(&list);
    
    return 0;
}