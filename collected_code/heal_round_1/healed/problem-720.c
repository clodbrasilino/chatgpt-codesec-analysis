#include <stdio.h>

void addDictionaryToTuple(int *tuple, int tupleSize, const int *dictionary, int dictionarySize) {
    for (int i = 0; i < dictionarySize; i++) {
        tuple[tupleSize + i] = dictionary[i];
    }
}

int main() {
    int tuple[13] = {1, 2, 3, 4, 5};
    int tupleSize = 5;
    
    const int dictionary[3] = {6, 7, 8};
    int dictionarySize = 3;
    
    addDictionaryToTuple(tuple, tupleSize, dictionary, dictionarySize);

    for (int i = 0; i < tupleSize + dictionarySize; i++) {
        printf("%d ", tuple[i]);
    }
    
    return 0;
}
