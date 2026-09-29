#include <stdio.h>

void printStrings(char *arr[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%s\n", arr[i]);
    }
}

int main() {
    char *strings[] = {"Hello", "World", "This", "Is", "A", "Test"};
    int size = sizeof(strings) / sizeof(strings[0]);

    printStrings(strings, size);

    return 0;
}