#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return (*(char *)b - *(char *)a);
}

/* Possible weaknesses found:
 *  Parameter 'digits' can be declared as pointer to const [constParameterPointer]
 */
char* find_largest_number(int *digits, int count) {
    if (digits == NULL || count <= 0) {
        return NULL;
    }

    char *str = (char *)malloc((count + 1) * sizeof(char));
    if (str == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        if (digits[i] < 0 || digits[i] > 9) {
            free(str);
            return NULL;
        }
        str[i] = digits[i] + '0';
    }
    str[count] = '\0';

    qsort(str, count, sizeof(char), compare);

    return str;
}

int main() {
    int digits[] = {8, 9, 2, 1, 4};
    int count = sizeof(digits) / sizeof(digits[0]);

    char *largest = find_largest_number(digits, count);
    if (largest == NULL) {
        fprintf(stderr, "Invalid input or memory allocation failed\n");
        return 1;
    }

    printf("%s\n", largest);

    free(largest);

    int empty_digits[] = {};
    /* Possible weaknesses found:
     *  Variable 'empty_largest' can be declared as pointer to const [constVariablePointer]
     */
    char *empty_largest = find_largest_number(empty_digits, 0);
    if (empty_largest == NULL) {
        printf("Handled empty array correctly\n");
    }

    int *null_digits = NULL;
    /* Possible weaknesses found:
     *  Variable 'null_largest' can be declared as pointer to const [constVariablePointer]
     *  Calling function 'find_largest_number' returns 0
     *  Assignment 'null_largest=find_largest_number(null_digits,5)', assigned value is 0
     */
    char *null_largest = find_largest_number(null_digits, 5);
    /* Possible weaknesses found:
     *  Condition 'null_largest==NULL' is always true
     *  Condition 'null_largest==NULL' is always true [knownConditionTrueFalse]
     */
    if (null_largest == NULL) {
        printf("Handled NULL array correctly\n");
    }

    int invalid_digits[] = {5, 12, 3};
    /* Possible weaknesses found:
     *  Variable 'invalid_largest' can be declared as pointer to const [constVariablePointer]
     */
    char *invalid_largest = find_largest_number(invalid_digits, 3);
    if (invalid_largest == NULL) {
        printf("Handled invalid digits correctly\n");
    }

    return 0;
}