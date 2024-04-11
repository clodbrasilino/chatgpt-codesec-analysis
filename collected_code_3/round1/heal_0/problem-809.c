#include <stdio.h>
#include <stdbool.h>

bool check_tuples(int tuple1[], int tuple2[], int size) {
    for(int i = 0; i < size; i++) {
        if(tuple2[i] >= tuple1[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int tuple1[] = {10, 20, 30, 40, 50};
    int tuple2[] = {5, 15, 25, 35, 45};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);

    if(check_tuples(tuple1, tuple2, size)) {
        printf("Each element of second tuple is smaller than its corresponding index in first tuple.\n");
    } else {
        printf("Each element of second tuple is not smaller than its corresponding index in first tuple.\n");
    }

    return 0;
}