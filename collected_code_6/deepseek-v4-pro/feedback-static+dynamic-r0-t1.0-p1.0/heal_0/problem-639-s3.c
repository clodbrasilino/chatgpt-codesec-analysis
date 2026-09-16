#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int sum_name_lengths(char *names[], int count) {
    int total = 0;
    for (int i = 0; i < count; i++) {
        if (names[i] != NULL && isupper((unsigned char)names[i][0])) {
            total += strlen(names[i]);
        }
    }
    return total;
}

int main(void) {
    char *names[] = {"Alice", "bob", "Charlie", "david", "Eve"};
    int count = sizeof(names) / sizeof(names[0]);
    int result = sum_name_lengths(names, count);
    printf("%d\n", result);
    return 0;
}