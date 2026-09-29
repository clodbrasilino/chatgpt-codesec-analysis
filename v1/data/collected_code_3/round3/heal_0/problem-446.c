#include <stdio.h>

#define MAX_SIZE 100

struct Tuple {
    int element;
    int count;
};

void count_elements(int arr[], int size, struct Tuple tuple[]) {
    int i, j, count;

    for(i = 0; i < size; i++) {
        count = 1;
        if(arr[i] != -1) {
            for(j = i + 1; j < size; j++) {
                if(arr[i] == arr[j]) {
                    count++;
                    arr[j] = -1;
                }
            }
            tuple[i].element = arr[i];
            tuple[i].count = count;
        }
    }
}

int main() {
    int arr[MAX_SIZE] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int size = 10;
    struct Tuple tuple[MAX_SIZE];
    int i;

    count_elements(arr, size, tuple);

    for(i = 0; i < size; i++) {
        if(arr[i] != -1) {
            printf("Element: %d, Count: %d\n", tuple[i].element, tuple[i].count);
        }
    }

    return 0;
}