#include <stdio.h>
#include <string.h>

int evenWordMaxLength(char *sentence) {
    int maxLength = 0;
    char *word = strtok(sentence, " ");

    while (word != NULL) {
        int length = strlen(word);

        if (length % 2 == 0 && length > maxLength) {
            maxLength = length;
        }

        word = strtok(NULL, " ");
    }

    return maxLength;
}

int main() {
    char sentence[100];
    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);

    sentence[strcspn(sentence, "\n")] = '\0';

    int maxLength = evenWordMaxLength(sentence);
    printf("The maximum length of an even word is: %d\n", maxLength);

    return 0;
}