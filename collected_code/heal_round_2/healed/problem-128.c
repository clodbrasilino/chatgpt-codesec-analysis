#include <stdio.h>
#include <string.h>

void shortlistWords(const char* const words[], int numWords, int n) {
    printf("Shortlisted words longer than %d characters:\n", n);
    
    for (int i = 0; i < numWords; i++) {
        if (words[i] != NULL) {
            int len = 0;
            const char* word = words[i];

            while (word[len] != '\0') {
                len++;
            }

            if (len > n) {
                printf("%s\n", word);
            }
        }
    }
}

int main() {
    const char* words[] = {"apple", "banana", "carrot", "pineapple", "grape"};
    int numWords = sizeof(words) / sizeof(words[0]);
    int n = 6;

    shortlistWords(words, numWords, n);
    
    return 0;
}