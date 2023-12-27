#include<stdio.h>

int countOccurences(const int* tuple, int size, int element) {
    int count = 0;
    
    for (int i = 0; i < size; i++) {
        if (tuple[i] == element) {
            count++;
        }
    }
    
    return count;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 3, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    int element = 3;
    
    int occurrences = countOccurences(tuple, size, element);
    
    printf("Occurrences of element %d: %d\n", element, occurrences);
    
    return 0;
}