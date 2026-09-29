#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int first;
    double second;
    char third;
};

size_t tuple_size(const struct Tuple *t)
{
    if (t == NULL) {
        return 0U;
    }
    return sizeof(*t);
}

int main(void)
{
    struct Tuple t = { 10, 3.14, 'a' };
    size_t size = tuple_size(&t);

    if (size == 0U) {
        fprintf(stderr, "Invalid tuple\n");
        return EXIT_FAILURE;
    }

    printf("Size of the tuple: %zu bytes\n", size);
    return EXIT_SUCCESS;
}