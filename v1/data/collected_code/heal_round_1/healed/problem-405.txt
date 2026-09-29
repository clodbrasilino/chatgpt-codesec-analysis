#include <stdio.h>

int checkElement(const int tup[], int n, int element) {
    for (int i = 0; i < n; i++) {
        if (tup[i] == element) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int element = 3;
    int exists = checkElement(tuple, sizeof(tuple) / sizeof(tuple[0]), element);
    if (exists) {
        printf("Element exists in the tuple.\n");
    } else {
        printf("Element does not exist in the tuple.\n");
    }
    return 0;
}