#include <stdio.h>
#include <string.h>

#define MAX_WORD_SIZE 100

int shortestWordLength(const char* sentence) {
    int shortest = MAX_WORD_SIZE;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char word[MAX_WORD_SIZE];
    const char* ptr = sentence;
    int count = 0;
    
    while (*ptr != '\0') {
        if (*ptr != ' ' && count < MAX_WORD_SIZE - 1) {
            word[count++] = *ptr;
        } else {
            word[count] = '\0';
            if (count && count < shortest) {
                shortest = count;
            }
            count = 0;
        }
        ptr++;
    }
    word[count] = '\0';
    if (count && count < shortest) {
        shortest = count;
    }
    return shortest;
}

int main() {
    const char sentence[] = "Write a C function to find the length of the shortest word";
    int length = shortestWordLength(sentence);
    printf("Length of the shortest word: %d\n", length);
    return 0;
}