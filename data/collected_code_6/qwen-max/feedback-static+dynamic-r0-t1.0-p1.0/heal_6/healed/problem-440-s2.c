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

    token = strtok_r((char *)sentcopy, delimiters, &context);
    while (token != NULL) {
        size_t len = strlen(token);
        if (isAdverb(token, len)) {
            *adverbs = realloc(*adverbs, ((*count) + 1) * sizeof(char *));
            (*adverbs)[*count] = strdup(token);
            *positions = realloc(*positions, ((*count) + 1) * sizeof(int));
            (*positions)[*count] = currentPos - (char *)sentence;
            (*count)++;
        }
        currentPos += len + strspn(currentPos, delimiters);
        token = strtok_r(NULL, delimiters, &context);
    }
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