#include<stdio.h>

int countSublists(int array[], int size, int element) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            for (int k = i; k <= j; k++) {
                if(array[k] == element){
                    count++;
                    break;
                }
            }
        }
    }
    return count;
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    int size = sizeof(array)/sizeof(array[0]);
    int element = 3;
    printf("%d sublists contain the element %d\n", countSublists(array, size, element), element);
    return 0;
}