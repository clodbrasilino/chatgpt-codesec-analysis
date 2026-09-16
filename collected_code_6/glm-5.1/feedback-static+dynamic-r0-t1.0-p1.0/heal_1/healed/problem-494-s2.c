#include <stdio.h>
#include <stdlib.h>

int binary_tuple_to_int(const unsigned char *tuple, size_t size) {
    if (tuple == NULL) {
        return 0;
    }
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        if (tuple[i] > 1) {
            return 0;
        }
        result = (result << 1) | tuple[i];
    }
    return result;
}

int main(void) {
    unsigned char t1[] = {1, 0, 1, 1};
    unsigned char t2[] = {0, 0, 0, 1};
    unsigned char t3[] = {1, 1, 1};
    const unsigned char *t4 = NULL;

    printf("%d\n", binary_tuple_to_int(t1, sizeof(t1) / sizeof(t1[0])));
    printf("%d\n", binary_tuple_to_int(t2, sizeof(t2) / sizeof(t2[0])));
    printf("%d\n", binary_tuple_to_int(t3, sizeof(t3) / sizeof(t3[0])));
    printf("%d\n", binary_tuple_to_int(t4, 0));

    return 0;
}