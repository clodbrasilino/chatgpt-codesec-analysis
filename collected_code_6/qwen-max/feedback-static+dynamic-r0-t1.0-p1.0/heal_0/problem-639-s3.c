#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int sum_name_lengths(char **names, int count) {
    int total = 0;
    for (int i = 0; i < count; i++) {
        if (islower(names[i][0])) {
            free(names[i]);
            names[i] = NULL;
        } else {
            total += strlen(names[i]);
        }
    }
    return total;
}

int main() {
    char *names[] = {"Alice", "bob", "Charlie", "david"};
    int count = sizeof(names) / sizeof(names[0]);
    int result = sum_name_lengths(names, count);
    printf("Total length: %d\n", result);

    for (int i = 0; i < count; i++) {
        free(names[i]);
    }
    return 0;
}