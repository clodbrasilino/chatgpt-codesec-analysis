#include <stdio.h>

int find_first_odd(int* array, int length) {
    for (int i = 0; i < length; i++) {
        if(array[i] % 2 != 0) {
            return array[i];
        }
    }
    return 0;  // Returns zero if no odd number is found
}

int main() {
    int array[] = {2, 4, 6, 7, 5, 8};
    int length = sizeof(array) / sizeof(array[0]);

    int first_odd = find_first_odd(array, length);
  
    if(first_odd)
        printf("The first odd number is %d\n", first_odd);
    else
        printf("No odd number found in the array\n");

    return 0;
}