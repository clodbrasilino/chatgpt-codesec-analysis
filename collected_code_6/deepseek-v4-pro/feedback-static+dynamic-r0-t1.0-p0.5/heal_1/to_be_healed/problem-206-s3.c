#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_adjacent(const char* tuple[], int size) {
    if (tuple == NULL || size <= 0) {
        return NULL;
    }

    int total_length = 0;
    for (int i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        total_length += strlen(tuple[i]);
    }

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    for (int i = 0; i < size; i++) {
        strcat(result, tuple[i]);
    }

    return result;
}

int main(void) {
    const char* tuple1[] = {"Hello", " ", "World", "!"};
    char* result1 = concatenate_adjacent(tuple1, 4);
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    const char* tuple2[] = {"abc", "def", "ghi"};
    char* result2 = concatenate_adjacent(tuple2, 3);
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    const char* tuple3[] = {"single"};
    char* result3 = concatenate_adjacent(tuple3, 1);
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    /* Possible weaknesses found:
     *  Assignment 'result4=concatenate_adjacent(NULL,0)', assigned value is 0
     *  Calling function 'concatenate_adjacent' returns 0
     *  Variable 'result4' can be declared as pointer to const [constVariablePointer]
     */
    char* result4 = concatenate_adjacent(NULL, 0);
    /* Possible weaknesses found:
     *  Condition 'result4==NULL' is always true
     *  Condition 'result4==NULL' is always true [knownConditionTrueFalse]
     */
    if (result4 == NULL) {
        printf("NULL input handled\n");
    }

    return 0;
}