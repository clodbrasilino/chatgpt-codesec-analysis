#include <stdio.h>
#include <stdlib.h>

int compare_tuples(const void* tuple1, const void* tuple2) {
    const int* t1 = *(const int**)tuple1;
    const int* t2 = *(const int**)tuple2;

    if (t1[0] > t2[0])
        return 1;
    else if (t1[0] < t2[0])
        return -1;
    
    return 0;
}

int main() {
    int tuple1[] = {5, 10};
    int tuple2[] = {3, 7};
    int tuple3[] = {1, 2};

    int* tuples[] = {tuple1, tuple2, tuple3};

    int num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    
    qsort(tuples, num_tuples, sizeof(tuples[0]), compare_tuples);

    for (int i = 0; i < num_tuples; i++) {
        printf("(%d, %d)\n", tuples[i][0], tuples[i][1]);
    }

    return 0;
}