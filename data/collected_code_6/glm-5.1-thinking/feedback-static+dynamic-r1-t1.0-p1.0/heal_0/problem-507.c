#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_target(const char *word, const char **targets, int target_count) {
    if (!word || !targets) return 0;
    for (int i = 0; i < target_count; i++) {
        if (targets[i] && strcmp(word, targets[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void remove_specific_words(char ***words, int *count, const char **targets, int target_count) {
    if (!words || !count || *count < 0 || !targets || target_count < 0) {
        return;
    }
    if (*count > 0 && !*words) {
        return;
    }

    int new_count = 0;
    for (int i = 0; i < *count; i++) {
        if ((*words)[i] != NULL) {
            if (is_target((*words)[i], targets, target_count)) {
                free((*words)[i]);
                (*words)[i] = NULL;
            } else {
                new_count++;
            }
        }
    }

    int j = 0;
    for (int i = 0; i < *count; i++) {
        if ((*words)[i] != NULL) {
            (*words)[j++] = (*words)[i];
        }
    }

    *count = new_count;

    if (new_count == 0) {
        free(*words);
        *words = NULL;
    } else {
        char **temp = realloc(*words, new_count * sizeof(char *));
        if (temp != NULL) {
            *words = temp;
        }
    }
}

int main(void) {
    int count = 5;
    char **words = malloc(count * sizeof(char *));
    if (!words) return EXIT_FAILURE;
    
    words[0] = strdup("apple");
    words[1] = strdup("banana");
    words[2] = strdup("cherry");
    words[3] = strdup("apple");
    words[4] = strdup("date");
    
    for (int i = 0; i < count; i++) {
        if (!words[i]) {
            for (int j = 0; j < i; j++) free(words[j]);
            free(words);
            return EXIT_FAILURE;
        }
    }
    
    const char *targets[] = {"apple", "date"};
    int target_count = 2;
    
    remove_specific_words(&words, &count, targets, target_count);
    
    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }
    
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
    
    return EXIT_SUCCESS;
}