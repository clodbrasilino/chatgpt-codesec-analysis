#include <stdio.h>

void findDissimilarElements(const int* tuple1, const int* tuple2, int size1, int size2) {
    int i, j;
    int found;

    for(i = 0; i < size1; i++) {
        found = 0;
        for(j = 0; j < size2; j++) {
            if(tuple1[i] == tuple2[j]) {
                found = 1;
                break;
            }
        }
        if(found == 0) {
            printf("%d ", tuple1[i]);
        }
    }

    for(i = 0; i < size2; i++) {
        found = 0;
        for(j = 0; j < size1; j++) {
            if(tuple2[i] == tuple1[j]) {
                found = 1;
                break;
            }
        }
        if(found == 0) {
            printf("%d ", tuple2[i]);
        }
    }
}

int main() {
    const int tuple1[] = {1, 2, 3, 4, 5};
    const int tuple2[] = {4, 5, 6, 7, 8};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    findDissimilarElements(tuple1, tuple2, size1, size2);

    return 0;
}