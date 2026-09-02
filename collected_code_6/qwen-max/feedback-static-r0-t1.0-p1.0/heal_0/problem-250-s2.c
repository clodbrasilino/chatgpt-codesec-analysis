#include <stdio.h>
#include <stddef.h>

size_t count_element(const int *tuple, size_t length, int element) {
    size_t count = 0;
    for (size_t i = 0; i < length; ++i) {
        if (tuple[i] == element) {
            ++count;
        }
    }
    return count;
}

int main(void) {
    const int tuple[] = {1, 2, 3, 4, 2, 2, 5};
    const size_t length = sizeof(tuple) / sizeof(tuple[0]);
    const int element = 2;
    size_t count = count_element(tuple, length, element);
    printf("Element %d occurs %zu times in the tuple.\n", element, count);
    return 0;
}