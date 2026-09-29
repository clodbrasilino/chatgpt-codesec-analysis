#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *numbers;
    size_t count;
} NumberList;

int productOfFirstEvenAndOdd(NumberList list) {
    int firstEven = -1, firstOdd = -1;
    for (size_t i = 0; i < list.count; ++i) {
        if (firstEven == -1 && list.numbers[i] % 2 == 0) {
            firstEven = list.numbers[i];
        }
        if (firstOdd == -1 && list.numbers[i] % 2 != 0) {
            firstOdd = list.numbers[i];
        }
        if (firstEven != -1 && firstOdd != -1) {
            break;
        }
    }
    if (firstEven != -1 && firstOdd != -1) {
        return firstEven * firstOdd;
    }
    return -1;
}

int main() {
    int data[] = {3, 5, 2, 8, 9};
    NumberList list = {data, 5};
    int result = productOfFirstEvenAndOdd(list);
    if (result != -1) {
        printf("Product: %d\n", result);
    } else {
        printf("No valid pair of even and odd numbers found.\n");
    }
    return 0;
}