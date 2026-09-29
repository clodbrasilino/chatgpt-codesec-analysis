#include <stdio.h>
#include <stdbool.h>

bool checkNoneValue(int tuple[], int size) {
    for(int i = 0; i < size; i++) {
        if(tuple[i] == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    int tuple[] = {1, 2, 3, 0, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);

    if(checkNoneValue(tuple, size)) {
        printf("Tuple has none value.\n");
    } else {
        printf("Tuple has no none value.\n");
    }

    return 0;
}