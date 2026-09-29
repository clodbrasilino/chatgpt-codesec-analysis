#include <stdio.h>

void divideTuple(const int *tuple1, const int *tuple2, int size) {
    for(int i = 0; i < size; i++) {
        if(tuple2[i] != 0)
            printf("%d / %d = %.2f\n", tuple1[i], tuple2[i], (float)tuple1[i] / tuple2[i]);
        else
            printf("Error: Division by Zero\n");
    }
}

int main() {
    int tuple1[] = {10, 20, 30, 40};
    int tuple2[] = {2, 4, 5, 0};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);

    divideTuple(tuple1, tuple2, size);

    return 0;
}