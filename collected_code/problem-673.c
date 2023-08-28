#include <stdio.h>

int convertToList(int *list, int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result = result * 10 + list[i];
    }
    return result;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);
    int converted = convertToList(list, size);
    printf("%d\n", converted);
    return 0;
}