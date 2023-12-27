#include <stdio.h>
#include <stdbool.h>

void filterDictionary(const int dictionary[], int size, int value) {
    for(int i = 0; i < size; i++) {
        if(dictionary[i] == value) {
            printf("%d\n", dictionary[i]);
        }
    }
}

int main() {
    int dictionary[] = {1, 2, 3, 4, 5};
    int size = sizeof(dictionary) / sizeof(dictionary[0]);
    int value = 4;

    filterDictionary(dictionary, size, value);

    return 0;
}