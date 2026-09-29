#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char *str, int left, int right) {
    if (left == right) {
        printf("%s\n", str);
        return;
    }
    for (int i = left; i <= right; i++) {
        swap(&str[left], &str[i]);
        permute(str, left + 1, right);
        swap(&str[left], &str[i]);
    }
}

int main(void) {
    char *str = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    printf("Enter a string: ");
    characters = getline(&str, &bufsize, stdin);
    if (characters == -1) {
        free(str);
        return 1;
    }

    if (characters > 0 && str[characters - 1] == '\n') {
        str[characters - 1] = '\0';
        characters--;
    }

    if (characters == 0) {
        free(str);
        return 0;
    }

    if ((size_t)characters > (size_t)INT_MAX) {
        free(str);
        return 1;
    }

    permute(str, 0, (int)characters - 1);

    free(str);
    return 0;
}