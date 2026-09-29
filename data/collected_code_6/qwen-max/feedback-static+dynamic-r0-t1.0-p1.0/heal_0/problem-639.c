#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int sumLength(const char *names[], int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        if (isupper(names[i][0])) {
            sum += strlen(names[i]);
        }
    }
    return sum;
}

int main() {
    const char *names[] = {"Alice", "bob", "Charlie", "david", "Eve"};
    int count = sizeof(names) / sizeof(names[0]);

    int result = sumLength(names, count);
    printf("Sum of lengths: %d\n", result);

    return 0;
}