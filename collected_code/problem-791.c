#include <stdio.h>

struct InnerRecord {
    int data;
};

struct OuterRecord {
    struct InnerRecord inner;
};

void removeNestedRecord(struct OuterRecord* tuple) {
    tuple->inner.data = 0;
}

int main() {
    struct OuterRecord tuple;

    // Accessing nested record before removal
    tuple.inner.data = 5;
    printf("Before removal: %d\n", tuple.inner.data);

    // Removing nested record
    removeNestedRecord(&tuple);

    // Accessing nested record after removal
    printf("After removal: %d\n", tuple.inner.data);

    return 0;
}
