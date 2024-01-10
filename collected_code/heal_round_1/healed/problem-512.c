#include <stdio.h>

int countElement(void* tuple, int size, void* element) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (tuple == NULL || element == NULL) {
            return count;
        }
        
        if (*(int*)tuple == *(int*)element) {
            count++;
        } else if (*(void**)tuple) {
            count += countElement(*(void**)tuple, *(int*)((char*)tuple + sizeof(void*)), element);
        }
        tuple = (char*)tuple + sizeof(void*);
    }
    return count;
}

int main() {
    int tuple1 = 1;
    int tuple2 = 2;
    int tuple3 = 3;
    int tuple4 = 4;
    void* nestedTuple1[] = {&tuple1, &tuple2, &tuple3};
    void* nestedTuple2[] = {&tuple4, nestedTuple1};
    void* mixedNestedTuple[] = {nestedTuple1, &tuple1, nestedTuple2};
    void* element = &tuple1;
    int elementCount = countElement(mixedNestedTuple, sizeof(mixedNestedTuple)/sizeof(mixedNestedTuple[0]), element);
    printf("Frequency of element: %d\n", elementCount);
    
    return 0;
}