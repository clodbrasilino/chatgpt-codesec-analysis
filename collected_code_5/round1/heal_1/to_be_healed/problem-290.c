#include <stdio.h>
#include <stdlib.h>

struct ListOfLists {
    int** list;
    int* sizeList;
    int size;
};

int** findMaxLenList(struct ListOfLists lol, int* sizeMax) {
    int max = 0;
    for (int i = 0; i < lol.size; i++) {
        if (lol.sizeList[i] > max)
            max = lol.sizeList[i];
    }
    *sizeMax = 0;
    for (int i = 0; i < lol.size; i++) {
        if (lol.sizeList[i] == max)
            (*sizeMax)++;
    }
    int** result = (int**)malloc(*sizeMax * sizeof(int*));
    if(!result) exit(1);
    int count = 0;
    for (int i = 0; i < lol.size; i++) {
        if (lol.sizeList[i] == max) {
            /* Possible weaknesses found:
             *  Use of memory allocated with size zero [unix.Malloc]
             */
            result[count] = lol.list[i];
            count++;
        }
    }
    return result;
}

int main() {
    struct ListOfLists lol;
    // Remember to initialize the structure here.
    int sizeMax;
    /* Possible weaknesses found:
     *  Value stored to 'maxLists' during its initialization is never read [deadcode.DeadStores]
     */
    int** maxLists = findMaxLenList(lol, &sizeMax);
    // Remember to deallocate memory here.
    /* Possible weaknesses found:
     *  Potential leak of memory pointed to by 'maxLists' [unix.Malloc]
     */
    return 0;
}