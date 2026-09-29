#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ValueHash {
    int value;
    /* Possible weaknesses found:
     *  unknown type name 'UT_hash_handle'
     */
    UT_hash_handle hh;
};

bool add_value(struct ValueHash **table, int value) {
    struct ValueHash *s = NULL;
    /* Possible weaknesses found:
     *  call to undeclared function 'HASH_FIND_INT'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'HASH_FIND_INT' [-Wimplicit-function-declaration]
     */
    HASH_FIND_INT(*table, &value, s);
    if (s == NULL) {
        s = (struct ValueHash *)malloc(sizeof(struct ValueHash));
        if (s == NULL) return false;
        s->value = value;
        /* Possible weaknesses found:
         *  implicit declaration of function 'HASH_ADD_INT' [-Wimplicit-function-declaration]
         *  call to undeclared function 'HASH_ADD_INT'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        HASH_ADD_INT(*table, value, s);
        return true;
    }
    return false;
}

void free_table(struct ValueHash **table) {
    struct ValueHash *current, *tmp;
    /* Possible weaknesses found:
     *  expected ';' before '{' token
     *  each undeclared identifier is reported only once for each function it appears in
     *  'hh' undeclared (first use in this function)
     *  call to undeclared function 'HASH_ITER'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  use of undeclared identifier 'hh'
     *  expected ';' after expression
     *  implicit declaration of function 'HASH_ITER' [-Wimplicit-function-declaration]
     */
    HASH_ITER(hh, *table, current, tmp) {
        /* Possible weaknesses found:
         *  call to undeclared function 'HASH_DEL'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        HASH_DEL(*table, current);
        free(current);
    }
}

int* extract_unique_values(int** dict, int dictSize, const int* dictColSize, int* returnSize) {
    struct ValueHash *table = NULL;
    for (int i = 0; i < dictSize; i++) {
        for (int j = 0; j < dictColSize[i]; j++) {
            add_value(&table, dict[i][j]);
        }
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'HASH_COUNT'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'HASH_COUNT' [-Wimplicit-function-declaration]
     */
    *returnSize = HASH_COUNT(table);
    int *result = (int*)malloc(*returnSize * sizeof(int));
    if (result == NULL) return NULL;

    int index = 0;
    struct ValueHash *s, *tmp;
    /* Possible weaknesses found:
     *  expected ';' before '{' token
     *  'hh' undeclared (first use in this function)
     *  call to undeclared function 'HASH_ITER'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  use of undeclared identifier 'hh'
     *  expected ';' after expression
     */
    HASH_ITER(hh, table, s, tmp) {
        result[index++] = s->value;
    }

    free_table(&table);
    return result;
}

int main() {
    int dict[][5] = {{1, 2, 2, 3}, {4, 5, 1}, {6, 7, 8, 9, 2}};
    int dictSize = 3;
    const int dictColSize[] = {4, 3, 5};
    int returnSize;
    int *uniqueValues = extract_unique_values((int**)dict, dictSize, dictColSize, &returnSize);

    for (int i = 0; i < returnSize; ++i) {
        printf("%d ", uniqueValues[i]);
    }
    free(uniqueValues);
    return 0;
}