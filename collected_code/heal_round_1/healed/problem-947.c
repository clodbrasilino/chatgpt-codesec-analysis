#include <stdio.h>
#include <string.h>

int shortestWordLength(const char* sentence) {
    int shortest = 9999;
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