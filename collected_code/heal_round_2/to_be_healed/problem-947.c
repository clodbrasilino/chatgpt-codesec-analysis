#include <stdio.h>
#include <string.h>

int shortestWordLength(const char* sentence) {
    int shortest = 9999;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char word[100];
    const char* ptr = sentence;
    int count = 0;
    
    while (*ptr != '\0') {
        if (*ptr != ' ') {
            word[count++] = *ptr;
        } else {
            word[count] = '\0';
            if (count < shortest) {
                shortest = count;
            }
            count = 0;
        }
        ptr++;
    }
    word[count] = '\0';
    /* Possible weaknesses found:
     *  'counts' undeclared (first use in this function); did you mean 'count'?
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (counts < shortest) {
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