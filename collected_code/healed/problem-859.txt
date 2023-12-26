#include <stdio.h>

void generateSublists(const int list[], int size) {
    int numSublists = 1 << size;

    for (int i = 0; i < numSublists; i++) {
        printf("{");
        for (int j = 0; j < size; j++) {
            if ((i & (1 << j)) != 0) {
                printf("%d ", list[j]);
            }
        }
        printf("}\n");
    }
}

int main() {
    const int list[] = {1, 2, 3};
    int size = sizeof(list) / sizeof(list[0]);

    generateSublists(list, size);

    return 0;
}