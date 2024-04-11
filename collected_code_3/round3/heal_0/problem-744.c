#include <stdio.h>
#include <stdbool.h>

bool checkNone(int tuple[], int size) {
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

    if(checkNone(tuple, size)) {
        printf("The tuple contains a None value.\n");
    } else {
        printf("The tuple does not contain a None value.\n");
    }

    return 0;
}