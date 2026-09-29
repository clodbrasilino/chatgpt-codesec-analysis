#include <stdio.h>
#include <string.h>

void removeWords(const char** strings, int size, const char* characterOrString) {
    int i, j, k;
    for(i = 0; i < size; i++) {
        char* token = strtok(strings[i], characterOrString);
        while (token != NULL) {
             printf("%s\n", token);
             token = strtok(NULL, characterOrString);
        }
    }
}

int main() {
    const char* strings[] = {"hello", "world", "example"};
    int size = sizeof(strings) / sizeof(strings[0]);
    const char* characterOrString = "o";

    removeWords(strings, size, characterOrString);

    return 0;
}