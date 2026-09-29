#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool isAdverb(const char *word, size_t len) {
    if (len < 4) return false;
    return (strncmp(word + len - 4, "ly", 2) == 0);
}

void findAdverbs(const char *sentence, char ***adverbs, int **positions, int *count) {
    const char *delimiters = " ,.!?;:";
    char *token;
    char *currentPos = (char *)sentence;
    char *context = NULL;

    char *sentcopy = strdup(sentence);
    if (sentcopy == NULL) {
        return;
    }
    
    token = strtok_r(sentcopy, delimiters, &context);
    while (token != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(token);
        if (isAdverb(token, len)) {
            *adverbs = realloc(*adverbs, ((*count) + 1) * sizeof(char *));
            if (*adverbs == NULL) {
                free(sentcopy);
                return;
            }
            (*adverbs)[*count] = strdup(token);
            if ((*adverbs)[*count] == NULL) {
                free(sentcopy);
                for (int i = 0; i < *count; i++) {
                    free((*adverbs)[i]);
                }
                free(*adverbs);
                return;
            }
            *positions = realloc(*positions, ((*count) + 1) * sizeof(int));
            if (*positions == NULL) {
                free(sentcopy);
                for (int i = 0; i <= *count; i++) {
                    free((*adverbs)[i]);
                }
                free(*adverbs);
                return;
            }
            (*positions)[*count] = currentPos - (char *)sentence;
            (*count)++;
        }
        currentPos += len + strspn(currentPos, delimiters);
        token = strtok_r(NULL, delimiters, &context);
    }
    free(sentcopy);
}

int main() {
    const char *sentence = "He quickly and quietly walked away from the scene.";
    char **adverbs = NULL;
    int *positions = NULL;
    int count = 0;

    findAdverbs(sentence, &adverbs, &positions, &count);

    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Position: %d\n", adverbs[i], positions[i]);
        free(adverbs[i]);
    }

    free(adverbs);
    free(positions);

    return 0;
}