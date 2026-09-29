#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flattenTuple(int* tuple, int size) {
    char *str = (char*) calloc(20 * size, sizeof(char));

    if (str == NULL)
        return NULL;

    for (int i = 0; i < size; i++) {
        char num[20] = {0};
        snprintf(num, 20, "%d", tuple[i]);
        strncat(str, num, 20);
        if (i < size - 1) {
            strncat(str, ",", 1);
        }
    }
    return str;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    char* result = flattenTuple(tuple, size);

    if (result == NULL) {
        printf("Memory allocation failed");
        return -1;
    }
    
    printf("%s\n", result);
    free(result);
    return 0;
}