#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 64
#define MAX_VAL_LEN 128

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VAL_LEN];
} Dictionary;

int compare_dicts(const void *a, const void *b) {
    const Dictionary *dictA = (const Dictionary *)a;
    const Dictionary *dictB = (const Dictionary *)b;
    return strcmp(dictA->key, dictB->key);
}

void sort_dictionaries(Dictionary *list, size_t count) {
    if (list == NULL || count == 0) {
        return;
    }
    qsort(list, count, sizeof(Dictionary), compare_dicts);
}

int main(void) {
    size_t num_dicts = 3;
    Dictionary *list = (Dictionary *)malloc(num_dicts * sizeof(Dictionary));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(list[0].key, "cherry", MAX_KEY_LEN - 1);
    list[0].key[MAX_KEY_LEN - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(list[0].value, "red", MAX_VAL_LEN - 1);
    list[0].value[MAX_VAL_LEN - 1] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(list[1].key, "apple", MAX_KEY_LEN - 1);
    list[1].key[MAX_KEY_LEN - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(list[1].value, "green", MAX_VAL_LEN - 1);
    list[1].value[MAX_VAL_LEN - 1] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(list[2].key, "banana", MAX_KEY_LEN - 1);
    list[2].key[MAX_KEY_LEN - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(list[2].value, "yellow", MAX_VAL_LEN - 1);
    list[2].value[MAX_VAL_LEN - 1] = '\0';

    sort_dictionaries(list, num_dicts);

    for (size_t i = 0; i < num_dicts; i++) {
        printf("%s: %s\n", list[i].key, list[i].value);
    }

    free(list);
    return EXIT_SUCCESS;
}