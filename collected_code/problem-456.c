#include <stdio.h>
#include <string.h>

void reverseStrings(char** strings, int numStrings) {
    for (int i = 0; i < numStrings; i++) {
        char* str = strings[i];
        int len = strlen(str);
        for (int j = 0; j < len / 2; j++) {
            char temp = str[j];
            str[j] = str[len - j - 1];
            str[len - j - 1] = temp;
        }
    }
}

int main() {
    char* strings[] = {"hello", "world", "example"};
    int numStrings = sizeof(strings) / sizeof(strings[0]);

    reverseStrings(strings, numStrings);
    for (int i = 0; i < numStrings; i++) {
        printf("%s\n", strings[i]);
    }
    
    return 0;
}