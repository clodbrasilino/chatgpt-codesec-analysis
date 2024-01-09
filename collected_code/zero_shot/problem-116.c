#include<stdio.h>
#include<math.h>

int convertTupleToInt(int tuple[], int size) {
    int result = 0;
    for(int i = 0; i < size; i++) {
        result += tuple[i] * pow(10, size - i - 1);
    }
    return result;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    int number = convertTupleToInt(tuple, size);
    printf("Converted integer: %d\n", number);
    return 0;
}