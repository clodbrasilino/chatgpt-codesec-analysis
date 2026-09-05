#include <stddef.h>
#include <stdio.h>

#define TUPLE_SIZE(tuple) (sizeof(tuple) / sizeof((tuple)[0]))

int main(void) {
    int tuple1[] = {1, 2, 3, 4, 5};
    double tuple2[] = {1.1, 2.2, 3.3};
    char tuple3[] = {'a', 'b', 'c', 'd'};

    size_t size1 = TUPLE_SIZE(tuple1);
    size_t size2 = TUPLE_SIZE(tuple2);
    size_t size3 = TUPLE_SIZE(tuple3);

    printf("%zu\n", size1);
    printf("%zu\n", size2);
    printf("%zu\n", size3);

    return 0;
}