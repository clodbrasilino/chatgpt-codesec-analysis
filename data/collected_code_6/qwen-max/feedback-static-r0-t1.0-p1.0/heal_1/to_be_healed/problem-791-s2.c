#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char *name;
} Record;

typedef struct {
    Record *record;
    int size;
} Tuple;

void removeNestedRecord(Tuple *tuple, int index) {
    if (index < 0 || index >= tuple->size) return;
    free(tuple->record[index].name);
    for (int i = index; i < tuple->size - 1; ++i) {
        tuple->record[i] = tuple->record[i + 1];
    }
    --tuple->size;
}

int main() {
    Tuple myTuple = { .size = 3 };
    myTuple.record = (Record *)malloc(myTuple.size * sizeof(Record));
    
    myTuple.record[0].id = 1;
    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strdup'
     *  call to undeclared library function 'strdup' with type 'char *(const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strdup' [-Wimplicit-function-declaration]
     */
    myTuple.record[0].name = strdup("RecordOne");
    
    myTuple.record[1].id = 2;
    myTuple.record[1].name = strdup("RecordTwo");
    
    myTuple.record[2].id = 3;
    myTuple.record[2].name = strdup("RecordThree");

    removeNestedRecord(&myTuple, 1);

    for (int i = 0; i < myTuple.size; ++i) {
        printf("ID: %d, Name: %s\n", myTuple.record[i].id, myTuple.record[i].name);
    }

    for (int i = 0; i < myTuple.size; ++i) {
        free(myTuple.record[i].name);
    }
    free(myTuple.record);

    return 0;
}