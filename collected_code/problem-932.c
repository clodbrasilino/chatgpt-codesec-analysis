#include <stdio.h>
#include <string.h>

void removeDuplicates(char *strings[], int count) {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(strings[i], strings[j]) == 0) {
                for (int k = j; k < count - 1; k++) {
                    strings[k] = strings[k + 1];
                }
                count--;
                j--;
            }
        }
    }
}

int main() {
    char *words[] = {
        "hello",
        "world",
        "hello",
        "bye",
        "world"
    };
    int count = sizeof(words) / sizeof(words[0]);

    removeDuplicates(words, count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    return 0;
}