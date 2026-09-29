#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NO_OF_CHARS 256

char firstRepeating(char *str) {
    int *count = (int *)calloc(NO_OF_CHARS, sizeof(int));
    int i;
    for (i = 0; *(str+i); i++)
        count[*(str+i)]++;
    for (i = 0; *(str+i); i++) {
        if (count[*(str+i)] > 1) {
            char result = str[i];
            free(count);
            return result;
        }
    }
    free(count);
    return '\0';
}

int main() {
    char str[] = "heleworld";
    printf("%c", firstRepeating(str));
    return 0;
}