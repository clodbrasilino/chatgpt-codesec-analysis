#include <string.h>
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct {
    char* key;
    char* value;
} Dictionary;

Tuple addDictionaryToTuple(Tuple tuple, Dictionary* dict, size_t dictSize) {
    for (size_t i = 0; i < dictSize; ++i) {
        if (!dict[i].key || !dict[i].value) {
            continue;
        }

        tuple.x += strlen(dict[i].key);
        tuple.y += strlen(dict[i].value);
    }

    return tuple;
}

int main() {
    Tuple t = {5, 10};

    Dictionary dict[] = { {"hello", "world"}, {"foo", "bar"} };

    t = addDictionaryToTuple(t, dict, 2);

    printf("New Tuple: (%d, %d)\n", t.x, t.y);
    return 0;
}