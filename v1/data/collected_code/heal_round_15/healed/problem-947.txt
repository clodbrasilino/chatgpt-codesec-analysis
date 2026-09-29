#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_WORD_SIZE 100

int shortestWordLength(const char* sentence) {
    int shortest = INT_MAX;
    char word[MAX_WORD_SIZE];
    int i = 0, j = 0, length = 0;

    while (sentence[i] != '\0') {
        if (sentence[i] == ' ' || sentence[i] == '\0') {
            if (length > 0 && length < shortest) {
                shortest = length;
                length = 0;
            }
            if (sentence[i] == '\0') {
                break;
            }
        } else {
            if (j < MAX_WORD_SIZE - 1) {
                word[j++] = sentence[i];
                length++;
            } else {
                return -1;
            }
        }
        i++;
    }

    if (j < MAX_WORD_SIZE) {
        word[j] = '\0';
    }

    return (shortest == INT_MAX) ? -1 : shortest;
}

int main() {
    const char sentence[] = "Write a C function to find the length of the shortest word";
    int length = shortestWordLength(sentence);
    printf("Length of the shortest word: %d\n", length);
    return 0; 
}