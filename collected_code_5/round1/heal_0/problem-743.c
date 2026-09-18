#include <stdio.h>
#include <string.h>

void rotate_list(int* array, int len, int rotations) {
    rotations = rotations % len;

    int temp[len];
    memcpy(temp, &array[len - rotations], rotations * sizeof(int));
    memmove(&array[rotations], array, (len - rotations) * sizeof(int));
    memcpy(array, temp, rotations * sizeof(int));
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    int len = sizeof(array) / sizeof(int);
    int rotations = 3;

    rotate_list(array, len, rotations);

    for (int i = 0; i < len; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}