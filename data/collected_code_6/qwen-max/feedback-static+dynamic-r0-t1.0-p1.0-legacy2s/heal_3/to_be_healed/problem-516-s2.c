#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
#define DIGIT_COUNT 10

void countingSort(int array[], int size, int place) {
    int output[MAX];
    int count[DIGIT_COUNT] = {0};

    for (int i = 0; i < size; ++i)
        count[(array[i] / place) % 10]++;

    for (int i = 1; i < 10; ++i)
        count[i] += count[i - 1];

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = size - 1; i >= 0; --i) {
        output[count[(array[i] / place) % 10] - 1] = array[i];
        --count[(array[i] / place) % 10];
    }

    for (int i = 0; i < size; ++i)
        /* Possible weaknesses found:
         *  Uninitialized variable: output [uninitvar]
         *  Uninitialized variable: output
         */
        array[i] = output[i];
}

/* Possible weaknesses found:
 *  conflicting types for 'radixsort'; have 'void(int *, int)'
 *  conflicting types for 'radixsort'
 */
void radixsort(int array[], int size) {
    int max = array[0];
    for (int i = 1; i < size; ++i)
        if (array[i] > max)
            max = array[i];

    for (int place = 1; max / place > 0; place *= 10)
        countingSort(array, size, place);
}

int main() {
    int data[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(data) / sizeof(data[0]);
    /* Possible weaknesses found:
     *  too few arguments to function call, expected 4, have 2
     */
    radixsort(data, n);
    for (int i = 0; i < n; ++i)
        printf("%d ", data[i]);
    return 0;
}