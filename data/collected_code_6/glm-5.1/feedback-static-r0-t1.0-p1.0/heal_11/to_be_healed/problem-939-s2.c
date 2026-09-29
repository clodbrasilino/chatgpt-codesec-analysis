#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[32];
    int value;
} Dict;

int compare_dicts(const void *a, const void *b) {
    const Dict *da = (const Dict *)a;
    const Dict *db = (const Dict *)b;
    if (da->key[0] == '\0' && db->key[0] != '\0') return -1;
    if (da->key[0] != '\0' && db->key[0] == '\0') return 1;
    return strncmp(da->key, db->key, sizeof(da->key));
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

    snprintf(list[0].key, sizeof(list[0].key), "delta");
    list[0].value = 4;

    snprintf(list[1].key, sizeof(list[1].key), "alpha");
    list[1].value = 1;

    snprintf(list[2].key, sizeof(list[2].key), "charlie");
    list[2].value = 3;

    snprintf(list[3].key, sizeof(list[3].key), "bravo");
    list[3].value = 2;

    sort_dicts(list, count);

    for (size_t i = 0; i < count; ++i) {
        printf("%s: %d\n", list[i].key, list[i].value);
    }

    return EXIT_SUCCESS;
}