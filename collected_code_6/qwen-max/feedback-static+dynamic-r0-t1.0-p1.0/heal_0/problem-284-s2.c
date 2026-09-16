#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areAllElementsEqual(char **list, int size, const char *str) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(list[i], str) != 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char *list[] = {"test", "test", "test"};
    int size = sizeof(list) / sizeof(list[0]);
    const char *str = "test";

    if (areAllElementsEqual(list, size, str)) {
        printf("All elements are equal to %s\n", str);
    } else {
        printf("Not all elements are equal to %s\n", str);
    }

    return 0;
}