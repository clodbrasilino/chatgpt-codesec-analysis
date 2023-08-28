#include <stdio.h>

// Function to compare two tuples using lambda expression
int compare_tuples(const void* tuple1, const void* tuple2) {
    // Typecast the tuples to the correct type
    const int* t1 = *(const int**)tuple1;
    const int* t2 = *(const int**)tuple2;

    // Compare the first element of the tuples
    if (t1[0] > t2[0])
        return 1;
    else if (t1[0] < t2[0])
        return -1;
    else
        return 0;
}

int main() {
    // List of tuples
    int tuple1[] = {5, 10};
    int tuple2[] = {3, 7};
    int tuple3[] = {1, 2};

    // Array of pointers to tuples
    int* tuples[] = {tuple1, tuple2, tuple3};

    // Sort the list of tuples
    int num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    qsort(tuples, num_tuples, sizeof(tuples[0]), compare_tuples);

    // Print the sorted list of tuples
    for (int i = 0; i < num_tuples; i++) {
        printf("(%d, %d)\n", tuples[i][0], tuples[i][1]);
    }

    return 0;
}
