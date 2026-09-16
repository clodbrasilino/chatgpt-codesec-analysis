#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Sublist;

typedef struct {
    Sublist *sublists;
    size_t length;
} SublistCollection;

size_t count_sublists_containing_element(const SublistCollection *collection, int element) {
    if (collection == NULL || collection->sublists == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < collection->length; i++) {
        Sublist current = collection->sublists[i];
        if (current.data == NULL) {
            continue;
        }
        int found = 0;
        for (size_t j = 0; j < current.length; j++) {
            if (current.data[j] == element) {
                found = 1;
                break;
            }
        }
        if (found) {
            count++;
        }
    }
    return count;
}

int main(void) {
    SublistCollection collection;
    collection.length = 3;
    collection.sublists = malloc(collection.length * sizeof(Sublist));
    if (collection.sublists == NULL) {
        return EXIT_FAILURE;
    }

    collection.sublists[0].length = 3;
    collection.sublists[0].data = malloc(collection.sublists[0].length * sizeof(int));
    if (collection.sublists[0].data == NULL) {
        free(collection.sublists);
        return EXIT_FAILURE;
    }
    collection.sublists[0].data[0] = 1;
    collection.sublists[0].data[1] = 2;
    collection.sublists[0].data[2] = 3;

    collection.sublists[1].length = 2;
    collection.sublists[1].data = malloc(collection.sublists[1].length * sizeof(int));
    if (collection.sublists[1].data == NULL) {
        free(collection.sublists[0].data);
        free(collection.sublists);
        return EXIT_FAILURE;
    }
    collection.sublists[1].data[0] = 4;
    collection.sublists[1].data[1] = 5;

    collection.sublists[2].length = 3;
    collection.sublists[2].data = malloc(collection.sublists[2].length * sizeof(int));
    if (collection.sublists[2].data == NULL) {
        free(collection.sublists[1].data);
        free(collection.sublists[0].data);
        free(collection.sublists);
        return EXIT_FAILURE;
    }
    collection.sublists[2].data[0] = 2;
    collection.sublists[2].data[1] = 6;
    collection.sublists[2].data[2] = 7;

    size_t result = count_sublists_containing_element(&collection, 2);
    printf("%zu\n", result);

    for (size_t i = 0; i < collection.length; i++) {
        free(collection.sublists[i].data);
    }
    free(collection.sublists);

    return EXIT_SUCCESS;
}