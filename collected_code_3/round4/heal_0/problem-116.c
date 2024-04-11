#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertTupleToInt(int *tuple, int size) {
    char buffer[256] = "";
    for(int i = 0; i < size; i++) {
        char temp[10];
        sprintf(temp, "%d", tuple[i]);
        strcat(buffer, temp);
    }
    return atoi(buffer);
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    int result = convertTupleToInt(tuple, size);
    printf("%d\n", result);
    return 0;
}