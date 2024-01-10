#include <stdio.h>
#include <stdlib.h>

char* flattenTuple(int* tuple, int size) {
    const int strSize = 20 * size;
    char *str = (char*) calloc(strSize, sizeof(char));

    if (str == NULL)
        return NULL;

    for (int i = 0; i < size; i++) {
        char num[20];
        snprintf(num, sizeof(num), "%d", tuple[i]);
        strncat(str, num, strlen(num)<(size_t)(strSize-strlen(str)-1)?strlen(num):(strSize-strlen(str)-1));
        if (i < size - 1 && strSize-strlen(str)-1>0) {
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