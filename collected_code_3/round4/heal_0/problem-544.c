#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flattenTupleList(char *tupleList[], int size) {
    int i;
    int totalLength = 0;
    for(i = 0; i < size; i++) {
        totalLength += strlen(tupleList[i]);
    }
    char *result = (char*)malloc(sizeof(char) * (totalLength + size + 1));
    strcpy(result, tupleList[0]);
    for(i = 1; i < size; i++) {
        strcat(result, ",");
        strcat(result, tupleList[i]);
    }
    return result;
}

int main() {
    char *tupleList[] = {"(1,2)", "(3,4)", "(5,6)"};
    int size = sizeof(tupleList) / sizeof(tupleList[0]);
    char *result = flattenTupleList(tupleList, size);
    printf("%s\n", result);
    free(result);
    return 0;
}