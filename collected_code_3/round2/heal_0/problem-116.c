#include <stdio.h>
#include <stdlib.h>

int convert_tuple_to_int(int *tuple, int size) {
    int result = 0;
    for(int i = 0; i < size; i++) {
        result = result * 10 + tuple[i];
    }
    return result;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    int result = convert_tuple_to_int(tuple, size);
    printf("%d\n", result);
    return 0;
}