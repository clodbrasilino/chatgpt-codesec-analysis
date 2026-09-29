#include <stdio.h>
#include <stdlib.h>

long long tupleToInt(const int *tuple, int size) {
    long long result = 0;
    for (int i = 0; i < size; ++i) {
        result = result * 10 + tuple[i];
    }
    return result;
}

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {4, 5, 6};
    int tuple3[] = {5, 6, 7};

    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    int size3 = sizeof(tuple3) / sizeof(tuple3[0]);

    long long result1 = tupleToInt(tuple1, size1);
    long long result2 = tupleToInt(tuple2, size2);
    long long result3 = tupleToInt(tuple3, size3);

    printf("%lld\n", result1);
    printf("%lld\n", result2);
    printf("%lld\n", result3);

    return 0;
}