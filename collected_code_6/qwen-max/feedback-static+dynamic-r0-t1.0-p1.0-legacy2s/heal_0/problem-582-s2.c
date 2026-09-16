#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t count;
} Dictionary;

bool isDictionaryEmpty(const Dictionary *dict) {
    return dict->count == 0;
}

int main() {
    Dictionary myDict = {0};
    if (isDictionaryEmpty(&myDict)) {
        return 0;
    } else {
        return 1;
    }
}