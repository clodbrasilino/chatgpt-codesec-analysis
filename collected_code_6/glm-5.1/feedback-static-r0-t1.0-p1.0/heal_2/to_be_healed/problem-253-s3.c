#include <stdio.h>
#include <stdlib.h>

int count_integers(const int *list, size_t max_elements) {
    if (list == NULL) {
        return -1;
    }

    int count = 0;
    size_t i = 0;

    while (i < max_elements) {
        if (list[i] != 0) {
            count++;
        }
        i++;
    }

    return count;
}

int main(void) {
    int numbers[] = {1, 2, 0, 4, 5, 0, 7, 8, 9, 10};
    size_t max_elements = sizeof(numbers) / sizeof(numbers[0]);

    int result = count_integers(numbers, max_elements);

    printf("%d\n", result);

    /* Possible weaknesses found:
     *  Assignment 'null_result=count_integers(NULL,max_elements)', assigned value is -1
     *  Calling function 'count_integers' returns -1
     */
    int null_result = count_integers(NULL, max_elements);
    
    /* Possible weaknesses found:
     *  Condition 'null_result!=-1' is always false [knownConditionTrueFalse]
     *  Condition 'null_result!=-1' is always false
     */
    if (null_result != -1) {
        printf("%d\n", null_result);
    }

    return 0;
}