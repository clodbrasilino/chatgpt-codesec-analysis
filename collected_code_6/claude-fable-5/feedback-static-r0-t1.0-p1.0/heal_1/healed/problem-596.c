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

void tuple_print(const struct Tuple *t)
{
    if (t == NULL) {
        return;
    }
    printf("Tuple contents: first=%d, second=%f, third=%c\n",
           t->first, t->second, t->third);
}

int main(void)
{
    struct Tuple t = { 10, 3.14, 'a' };
    size_t size = tuple_size(&t);

    if (size == 0U) {
        fprintf(stderr, "Invalid tuple\n");
        return EXIT_FAILURE;
    }

    tuple_print(&t);
    printf("Size of the tuple: %zu bytes\n", size);
    return EXIT_SUCCESS;
}