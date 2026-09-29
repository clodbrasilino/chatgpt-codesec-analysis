#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
} NestedRecord;

typedef struct {
    int id;
    NestedRecord record;
} Tuple;

void removeNestedRecord(Tuple* tuple) {
    strcpy(tuple->record.name, "");
    tuple->record.age = 0;
}

int main() {
    Tuple tuple;
    tuple.id = 1;
    strcpy(tuple.record.name, "John Doe");
    tuple.record.age = 30;

    printf("Before removing nested record: %s, %d\n", tuple.record.name, tuple.record.age);

    removeNestedRecord(&tuple);

    printf("After removing nested record: %s, %d\n", tuple.record.name, tuple.record.age);

    return 0;
}