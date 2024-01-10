#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeWords(char** strings, int size, const char* characterOrString) {
    int i;
    for(i = 0; i < size; i++) {
        char* mutableString = strdup(strings[i]);
        char* token = strtok(mutableString, characterOrString);
        while (token != NULL) {
            printf("%s\n", token);
            token = strtok(NULL, characterOrString);
        }
        free(mutableString);
    }
}

int main() {
    char* strings[] = {"hello", "world", "example"};
    int size = sizeof(strings) / sizeof(strings[0]);
    const char* characterOrString = "o";
    removeWords(strings, size, characterOrString);
    return 0;
}