#include <stdio.h>
#include <string.h>

void shortlistWords(char* words[], int numWords, int n) {
    printf("Shortlisted words longer than %d characters:\n", n);
    
    for (int i = 0; i < numWords; i++) {
        if (strlen(words[i]) > n) {
            printf("%s\n", words[i]);
        }
    }
}

int main() {
    char* words[] = {"apple", "banana", "carrot", "pineapple", "grape"};
    int numWords = sizeof(words) / sizeof(words[0]);
    int n = 6;
    
    shortlistWords(words, numWords, n);
    
    return 0;
}