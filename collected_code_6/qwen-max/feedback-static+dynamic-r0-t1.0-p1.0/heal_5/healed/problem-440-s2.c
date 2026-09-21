#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool isAdverb(const char *word, size_t len) {
    if (len < 4) return false;
    return (strncmp(word + len - 4, "ly", 2) == 0);
}

void findAdverbs(const char *sentence, char **adverbs, int *positions, int *count) {
    const char *delimiters = " ,.!?;:";
    char *token;
    char *currentPos = (char *)sentence;
    char *context = NULL;

    token = strtok_r((char *)sentence, delimiters, &context);
    while (token != NULL) {
        size_t len = strlen(token);
        if (isAdverb(token, len)) {
            adverbs[*count] = strdup(token);
            positions[*count] = currentPos - (char *)sentence;
            (*count)++;
        }
        currentPos += len + strspn(currentPos, delimiters);
        token = strtok_r(NULL, delimiters, &context);
    }
}

int main() {
    const char *sentence = "He quickly and quietly walked away from the scene.";
    char *adverbs[100];
    int positions[100];
    int count = 0;

    findAdverbs(sentence, adverbs, positions, &count);

    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Position: %d\n", adverbs[i], positions[i]);
        free(adverbs[i]);
    }

    return 0;
}