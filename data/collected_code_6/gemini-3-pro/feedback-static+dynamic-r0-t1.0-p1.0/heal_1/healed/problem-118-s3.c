#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char word[256];
    int first = 1;

    printf("[");
    while (scanf("%255s", word) == 1) {
        if (!first) {
            printf(", ");
        }
        printf("'%s'", word);
        first = 0;
    }
    printf("]\n");

    return 0;
}