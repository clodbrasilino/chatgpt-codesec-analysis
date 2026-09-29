#include <stdio.h>
#include <stdlib.h>

typedef struct Record {
    int id;
    struct Record *nestedRecord;
} Record; 

Record* removeNestedRecord(Record* root) { 
    if(root == NULL) {
        return root;
    } else if(root->nestedRecord != NULL) {
        free(root->nestedRecord);
        root->nestedRecord = NULL;
    }
    return root;
}

int main() {
    Record* testRecord = (Record*)malloc(sizeof(Record));
    testRecord->id = 1;

    Record* nestedRecord = (Record*)malloc(sizeof(Record));
    nestedRecord->id = 2;

    testRecord->nestedRecord = nestedRecord;

    printf("Before removal: Root ID = %d, Nested ID = %d\n", testRecord->id, 
        testRecord->nestedRecord != NULL ? testRecord->nestedRecord->id : -1);

    testRecord = removeNestedRecord(testRecord);
    
    printf("After removal: Root ID = %d, Nested ID = %d\n", testRecord->id, 
        testRecord->nestedRecord != NULL ? testRecord->nestedRecord->id : -1);

    free(testRecord);

    return 0;
}