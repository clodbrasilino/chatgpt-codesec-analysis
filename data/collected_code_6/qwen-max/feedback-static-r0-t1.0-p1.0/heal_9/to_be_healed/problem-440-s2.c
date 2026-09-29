#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool isAdverb(const char *word, size_t len) {
    return len >= 4 && (strncmp(word + len - 4, "ly", 2) == 0);
}

void findAdverbs(const char *sentence, char ***adverbs, int *positions, int *count) {
    const char *delimiters = " ,.!?;:";
    const char *currentPos = sentence;
    
    char *copy = strdup(sentence);
    if (copy == NULL) {
        return;
    }

    char *context = NULL;
    char *token;
    while ((token = strtok_r(copy ? copy : "", delimiters, &context)) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t tokenLen = strlen(token);
        if (isAdverb(token, tokenLen)) {
            *adverbs = realloc(*adverbs, (*count + 1) * sizeof(char *));
            if (*adverbs == NULL) {
                free(copy);
                return;
            }
            (*adverbs)[*count] = strdup(token);
            if ((*adverbs)[*count] == NULL) {
                free(copy);
                return;
            }
            positions[*count] = currentPos - sentence;
            (*count)++;
        }
        currentPos += tokenLen + strspn(currentPos, delimiters);
        copy = NULL;
    }

    free(copy);
}

int main() {
    const char *sentence = "He quickly and quietly walked away from the scene.";
    char **adverbs = NULL;
    int positions[100];
    int count = 0;

    findAdverbs(sentence, &adverbs, positions, &count);

    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Position: %d\n", adverbs[i], positions[i]);
        free(adverbs[i]);
    }

    free(adverbs);
    return 0;
}