#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_adverb(const char *word) {
    size_t len = strlen(word);
    if (len > 3 && (strcmp(word + len - 4, "ly") == 0)) {
        return true;
    }
    return false;
}

void find_adverbs(const char *sentence, char adverbs[50][50], int *positions, int *count) {
    const char delimiters[] = " ,.!?;:()[]{}<>-\"'`«»“”‘’„‚";
    char *token;
    const char *saveptr;
    int pos = 0;

    /* Possible weaknesses found:
     *  passing argument 3 of 'strtok_r' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    while ((token = strtok_r((char *)sentence, delimiters, &saveptr)) != NULL) {
        if (is_adverb(token)) {
            strcpy(adverbs[*count], token);
            positions[*count] = pos;
            (*count)++;
        }
        pos += strlen(token) + strspn(saveptr, delimiters);
        sentence = NULL;
    }
}

int main() {
    const char *sentence = "He quickly and quietly opened the window.";
    char adverbs[50][50];
    int positions[50] = {0};
    int count = 0;

    find_adverbs(sentence, adverbs, positions, &count);

    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Position: %d\n", adverbs[i], positions[i]);
    }

    return 0;
}