#include <stdio.h>
#include <stddef.h>

size_t tuple_size(void *t, size_t elem_size) {
    if (elem_size == 0) {
        return 0;
    }
    return sizeof(t) / elem_size;
}

int main(void) {
    int t1[] = {1, 2, 3};
    double t2[] = {1.5, 2.5, 3.5, 4.5};
    char t3[] = {'a', 'b'};

    size_t s1 = tuple_size(t1, sizeof(int));
    size_t s2 = tuple_size(t2, sizeof(double));
    size_t s3 = tuple_size(t3, sizeof(char));

    printf("%zu\n", s1);
    printf("%zu\n", s2);
    printf("%zu\n", s3);

    return 0;
}