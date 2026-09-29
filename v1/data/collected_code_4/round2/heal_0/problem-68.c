#include <stdbool.h>
#include <stdio.h>

bool isMonotonic(int* A, int ASize) {
    bool increasing = true;
    bool decreasing = true;

    for (int i = 0; i < ASize - 1; ++i) {
        if(A[i] > A[i+1])
            increasing = false;
        if(A[i] < A[i+1])
            decreasing = false;
    }
    return increasing || decreasing;
}

int main() {
    int array1[] = {1, 2, 3, 4};
    int array2[] = {4, 3, 2, 1};
    int array3[] = {1, 2, 3, 2};

    printf("%s\n", isMonotonic(array1, 4) ? "True" : "False");
    printf("%s\n", isMonotonic(array2, 4) ? "True" : "False");
    printf("%s\n", isMonotonic(array3, 4) ? "True" : "False");

    return 0;
}