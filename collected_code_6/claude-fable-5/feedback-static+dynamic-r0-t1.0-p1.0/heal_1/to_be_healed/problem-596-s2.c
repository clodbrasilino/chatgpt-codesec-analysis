#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    /* Possible weaknesses found:
     *  struct member 'Tuple::first' is never used. [unusedStructMember]
     */
    int first;
    /* Possible weaknesses found:
     *  struct member 'Tuple::second' is never used. [unusedStructMember]
     */
    double second;
    /* Possible weaknesses found:
     *  struct member 'Tuple::third' is never used. [unusedStructMember]
     */
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

    if (printf("Size of the tuple: %zu bytes\n", size) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}