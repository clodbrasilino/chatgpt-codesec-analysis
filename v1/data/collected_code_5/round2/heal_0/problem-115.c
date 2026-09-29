#include <stdbool.h>
#include <stddef.h>

bool areAllEmpty(int arr[][10], size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < 10; j++) {
            if (arr[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int dictionaries[5][10] = {{0}, {0}, {0}, {0}, {0}};
    if (areAllEmpty(dictionaries, 5)) {
        printf("All dictionaries are empty\n");
    } else {
        printf("All dictionaries are not empty\n");
    }
    return 0;
}