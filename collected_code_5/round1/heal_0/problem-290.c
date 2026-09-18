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
    int** maxLists = findMaxLenList(lol, &sizeMax);
    // Remember to deallocate memory here.
    return 0;
}