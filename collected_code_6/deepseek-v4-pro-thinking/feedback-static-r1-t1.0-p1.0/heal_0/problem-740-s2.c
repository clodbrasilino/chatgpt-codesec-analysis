#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

KeyValuePair *tuple_to_dict(char *tuple[], int length, int *pair_count) {
    if (tuple == NULL || length <= 0 || length % 2 != 0 || pair_count == NULL) {
        if (pair_count != NULL) {
            *pair_count = 0;
        }
        return NULL;
    }

    int count = length / 2;
    KeyValuePair *dict = malloc((size_t)count * sizeof(KeyValuePair));
    if (dict == NULL) {
        *pair_count = 0;
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        dict[i].key = tuple[i * 2];
        dict[i].value = tuple[i * 2 + 1];
    }

    *pair_count = count;
    return dict;
}

int main(void) {
    char *tuple[] = {"name", "Alice", "age", "30", "city", "Paris"};
    int length = (int)(sizeof(tuple) / sizeof(tuple[0]));
    int pair_count = 0;

    KeyValuePair *dict = tuple_to_dict(tuple, length, &pair_count);
    if (dict == NULL) {
        return 1;
    }

    for (int i = 0; i < pair_count; i++) {
        printf("%s: %s\n", dict[i].key, dict[i].value);
    }

    free(dict);
    return 0;
}