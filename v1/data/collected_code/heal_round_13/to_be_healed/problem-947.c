#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_WORD_SIZE 100

int shortestWordLength(const char* sentence) {
    int shortest = INT_MAX;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char word[MAX_WORD_SIZE];
    int i = 0, j = 0, length = 0;

    while (1) {
        if (sentence[i] == ' ' || sentence[i] == '\0') {
            if (length > 0) {
                shortest = length < shortest ? length : shortest;
                length = 0;
            }
            if (sentence[i] == '\0') break;
        } 
        else if (j < MAX_WORD_SIZE - 1) {
            word[j++] = sentence[i];
            length++;
        }
        i++;
    }
     
    return (shortest == INT_MAX) ? -1 : shortest;
}

int main() {
    const char sentence[] = "Write a C function to find the length of the shortest word";
    int length = shortestWordLength(sentence);
    printf("Length of the shortest word: %d\n", length);
    return 0;
}