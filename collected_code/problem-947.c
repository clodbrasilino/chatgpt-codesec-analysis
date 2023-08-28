#include <stdio.h>
#include <string.h>

int shortestWordLength(char* sentence) {
    int shortest = 9999;
    char* token = strtok(sentence, " ");
    while (token != NULL) {
        int length = strlen(token);
        if (length < shortest) {
            shortest = length;
        }
        token = strtok(NULL, " ");
    }
    return shortest;
}

int main() {
    char sentence[] = "Write a C function to find the length of the shortest word";
    int length = shortestWordLength(sentence);
    printf("Length of the shortest word: %d\n", length);
    return 0;
}