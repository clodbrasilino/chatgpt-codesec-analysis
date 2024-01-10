#include <stdio.h>

int count_until_tuple(int* list, int size) {
    int count = 0;

    for(int i=0; i<size; i++) {
        if (list[i] == -1) {
            break;
        }
        count++;
    }

    return count;
}

int main() {
    int list[6] = {1, 2, 3, 4, 5, -1};
    int size = sizeof(list)/sizeof(list[0]);
    int count = count_until_tuple(list, size);
    printf("Count: %d\n", count);
    
    return 0;
}