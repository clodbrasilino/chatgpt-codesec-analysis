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
    const char* ptr = sentence;
    int count = 0;
    
    while (*ptr != '\0') {
        if (*ptr != ' ') {
            if (count < MAX_WORD_SIZE - 1) {
                word[count++] = *ptr;
            } else {
                break;
            }
        } else if (count > 0) {
            if (count < shortest) {
                shortest = count;
            }
            count = 0;
        }
        ptr++;
    }
    
    if (count > 0 && count < shortest) {
        shortest = count;
    }
    
    return (shortest == INT_MAX ? -1 : shortest);
}

int main() {
    const char sentence[] = "Write a C function to find the length of the shortest word";
    int length = shortestWordLength(sentence);
    printf("Length of the shortest word: %d\n", length);
    return 0;
}