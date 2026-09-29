#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256
#define ASCII_SIZE 256

void mostCommon(char *str) {
    int count[ASCII_SIZE] = {0};
    int max = 0;
    int result = -1;
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        count[str[i]]++;
        if (max < count[str[i]]) {
            max = count[str[i]];
            result = str[i];
        }
    }
    if(result != -1)
        printf("Most common character: %c, Occurrences: %d\n", result, max);
    else
        printf("Empty String\n");
}

int main() {
    char str[MAX_CHAR];
    printf("Enter a string: ");
    fgets(str, MAX_CHAR, stdin);
    str[strcspn(str, "\n")] = 0;
    mostCommon(str);
    return 0;
}