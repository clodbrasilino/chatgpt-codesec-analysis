#include <stdio.h>
#include <stdbool.h>

bool check_tuples(int tuple1[], int tuple2[], int size) {
    for(int i = 0; i < size; i++) {
        if(tuple2[i] <= tuple1[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {2, 3, 4, 5, 6};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);

    if(check_tuples(tuple1, tuple2, size)) {
        printf("Each element of the second tuple is greater than its corresponding index in the first tuple.\n");
    } else {
        printf("Not all elements of the second tuple are greater than their corresponding index in the first tuple.\n");
    }

    return 0;
}