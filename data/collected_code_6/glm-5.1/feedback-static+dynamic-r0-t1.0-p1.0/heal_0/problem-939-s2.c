#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[32];
    int value;
} Dict;

int compare_dicts(const void *a, const void *b) {
    const Dict *da = (const Dict *)a;
    const Dict *db = (const Dict *)b;
    return strcmp(da->key, db->key);
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

    Dict list[4];
    size_t count = sizeof(list) / sizeof(list[0]);

    strncpy(list[0].key, "delta", sizeof(list[0].key) - 1);
    list[0].key[sizeof(list[0].key) - 1] = '\0';
    list[0].value = 4;

    strncpy(list[1].key, "alpha", sizeof(list[1].key) - 1);
    list[1].key[sizeof(list[1].key) - 1] = '\0';
    list[1].value = 1;

    strncpy(list[2].key, "charlie", sizeof(list[2].key) - 1);
    list[2].key[sizeof(list[2].key) - 1] = '\0';
    list[2].value = 3;

    strncpy(list[3].key, "bravo", sizeof(list[3].key) - 1);
    list[3].key[sizeof(list[3].key) - 1] = '\0';
    list[3].value = 2;

    sort_dicts(list, count);

    for (size_t i = 0; i < count; ++i) {
        printf("%s: %d\n", list[i].key, list[i].value);
    }

    return EXIT_SUCCESS;
}