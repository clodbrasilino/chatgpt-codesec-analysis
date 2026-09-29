#include <stdio.h>
#include <stdlib.h>

int count_and_square_lists(const void **list, size_t list_length) {
    int count = 0;
    for (size_t i = 0; i < list_length; ++i) {
        /* Possible weaknesses found:
         * UBSan: load of null pointer of type 'const void *'
         * ASan: SEGV
         */
        if (*(const void **)list[i] != NULL) {
            count++;
        }
    }
    return count * count;
}

int main() {
    const void *nested_list[] = {
        (const void *)NULL,
        (const void *)NULL,
        (const void *)NULL,
        (const void *)NULL,
        (const void *)NULL
    };

    int num_lists = count_and_square_lists(nested_list, sizeof(nested_list) / sizeof(nested_list[0]));
    printf("%d\n", num_lists);

    return 0;
}