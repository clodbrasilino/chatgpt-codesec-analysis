#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_LENGTH 32

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[KEY_LENGTH];
    int value;
} Dict;

int compare_dicts(const void *a, const void *b) {
    const Dict *da = (const Dict *)a;
    const Dict *db = (const Dict *)b;
    return strncmp(da->key, db->key, KEY_LENGTH);
}

void sort_dicts(Dict *dicts, size_t count) {
    if (dicts == NULL || count == 0) {
        return;
    }
    qsort(dicts, count, sizeof(Dict), compare_dicts);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        return EXIT_FAILURE;
    }

    Dict list[4] = {0};
    size_t count = sizeof(list) / sizeof(list[0]);

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(list[0].key, "delta", KEY_LENGTH - 1);
    list[0].key[KEY_LENGTH - 1] = '\0';
    list[0].value = 4;

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(list[1].key, "alpha", KEY_LENGTH - 1);
    list[1].key[KEY_LENGTH - 1] = '\0';
    list[1].value = 1;

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(list[2].key, "charlie", KEY_LENGTH - 1);
    list[2].key[KEY_LENGTH - 1] = '\0';
    list[2].value = 3;

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(list[3].key, "bravo", KEY_LENGTH - 1);
    list[3].key[KEY_LENGTH - 1] = '\0';
    list[3].value = 2;

    sort_dicts(list, count);

    for (size_t i = 0; i < count; ++i) {
        printf("%s: %d\n", list[i].key, list[i].value);
    }

    return EXIT_SUCCESS;
}