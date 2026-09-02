#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char *name;
} Record;

void remove_nested_record(Record *tuple, int index) {
    if (index < 0 || index >= 10) return; // Assuming a fixed size for demonstration
    free(tuple[index].name);
    for (int i = index; i < 9; ++i) {
        tuple[i] = tuple[i + 1];
    }
}

int main() {
    Record records[10] = {
        {1, strdup("Alice")},
        {2, strdup("Bob")},
        {3, strdup("Charlie")},
        {4, strdup("David")},
        {5, strdup("Eve")},
        {6, strdup("Frank")},
        {7, strdup("Grace")},
        {8, strdup("Hank")},
        {9, strdup("Isabel")},
        {10, strdup("Jack")}
    };

    int index_to_remove = 3;
    remove_nested_record(records, index_to_remove);

    for (int i = 0; i < 9; ++i) {
        printf("%d: %s\n", records[i].id, records[i].name);
        free(records[i].name);
    }

    return 0;
}