#include <stdio.h>

void accessElements(int list[], int index[], int numElements, int numIndices) {
    int i;
    for (i = 0; i < numIndices; i++) {
        if (index[i] >= 0 && index[i] < numElements) {
            printf("Value at index %d: %d\n", index[i], list[index[i]]);
        } else {
            printf("Invalid index %d\n", index[i]);
        }
    }
}

int main() {
    int list[] = {10, 20, 30, 40, 50};
    int indices[] = {0, 2, 4};
    int numElements = sizeof(list) / sizeof(list[0]);
    int numIndices = sizeof(indices) / sizeof(indices[0]);
    
    accessElements(list, indices, numElements, numIndices);
    
    return 0;
}