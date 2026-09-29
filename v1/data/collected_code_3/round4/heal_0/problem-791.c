#include <stdio.h>

typedef struct {
    int x;
    int y;
} NestedRecord;

typedef struct {
    int a;
    int b;
    NestedRecord record;
} Tuple;

void removeNestedRecord(Tuple *tuple) {
    tuple->record.x = 0;
    tuple->record.y = 0;
}

int main() {
    Tuple tuple;
    tuple.a = 1;
    tuple.b = 2;
    tuple.record.x = 3;
    tuple.record.y = 4;

    printf("Before removal: a=%d, b=%d, x=%d, y=%d\n", tuple.a, tuple.b, tuple.record.x, tuple.record.y);

    removeNestedRecord(&tuple);

    printf("After removal: a=%d, b=%d, x=%d, y=%d\n", tuple.a, tuple.b, tuple.record.x, tuple.record.y);

    return 0;
}