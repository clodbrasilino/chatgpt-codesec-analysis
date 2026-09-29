#include <stdio.h>

void cubeElements(int *list, int size) {
    for (int i = 0; i < size; i++) {
        list[i] = list[i] * list[i] * list[i];
    }
}

int main() {
    int size;
    printf("Enter the size of the list: ");
    scanf("%d", &size);
    
    int list[size];
    printf("Enter the elements of the list: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &list[i]);
    }
    
    cubeElements(list, size);
    
    printf("Cubes of individual elements in the list:\n");
    for (int i = 0; i < size; i++) {
        printf("%d\n", list[i]);
    }
    
    return 0;
}