#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isWordPresent(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return 0;
    }

    size_t wordLen = strlen(word);
    if (wordLen == 0) {
        return 0;
    }

    const char *current = sentence;
    while ((current = strstr(current, word)) != NULL) {
        if ((current == sentence || !isalnum((unsigned char)current[-1])) &&
            !isalnum((unsigned char)current[wordLen])) {
            return 1;
        }
        current++;
    }

    return 0;
}

int main(void) {
    char sentence[256];
    char word[256];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading sentence\n");
        return 1;
    }

    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word\n");
        return 1;
    }

    sentence[strcspn(sentence, "\n")] = '\0';
    word[strcspn(word, "\n")] = '\0';

    if (isWordPresent(sentence, word)) {
        printf("The word is present in the sentence.\n");
    } else {
        printf("The word is not present in the sentence.\n");
    }

    return 0;
}