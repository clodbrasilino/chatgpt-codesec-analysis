#include <stdio.h>

#define SIZE 10

void remove_int_elements(int arr[], char char_arr[], int *size) {
    int i, j = 0;
    for(i = 0; i < *size; i++) {
        if(arr[i] != (int)arr[i]) {
            arr[j] = arr[i];
            char_arr[j] = char_arr[i];
            j++;
        }
    }
    *size = j;
}

int main() {
    int i, size = SIZE;
    int arr[SIZE] = {1, 'a', 2, 'b', 3, 'c', 4, 'd', 5, 'e'};
    char char_arr[SIZE] = {'1', 'a', '2', 'b', '3', 'c', '4', 'd', '5', 'e'};

    remove_int_elements(arr, char_arr, &size);

    for(i = 0; i < size; i++) {
        printf("%c ", char_arr[i]);
    }

    return 0;
}