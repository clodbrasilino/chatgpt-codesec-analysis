#include <stdio.h>
#include <stdlib.h>

void convertToFloat(int* intArr, float* floatArr, int len) {
    for (int i = 0; i < len; i++) {
        floatArr[i] = (float) intArr[i];
    }
}

int main() {
    int len = 5;
    int intArr[] = {1, 2, 3, 4, 5};
    float floatArr[len];

    convertToFloat(intArr, floatArr, len);

    for (int i = 0; i < len; i++) {
        printf("%.2f ", floatArr[i]);
    }

    return 0;
}