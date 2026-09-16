#include <stdio.h>
#include <stdlib.h>

int tuple_to_int(const int *tuple, size_t length) {
    int result = 0;
    for (size_t i = 0; i < length; ++i) {
        result += tuple[i] * pow(10, 3 * (length - i - 1));
    }
    return result;
}

int main() {
    int tuple[] = {1, 2, 3};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    int result = tuple_to_int(tuple, length);
    printf("%d\n", result);
    return 0;
}