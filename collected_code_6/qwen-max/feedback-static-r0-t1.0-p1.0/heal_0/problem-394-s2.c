#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TUPLE_SIZE 100

bool is_distinct(const char *tuple[], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (strcmp(tuple[i], tuple[j]) == 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    const char *tuple1[] = {"a", "b", "c"};
    const char *tuple2[] = {"a", "b", "a"};

    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    bool result1 = is_distinct(tuple1, size1);
    bool result2 = is_distinct(tuple2, size2);

    printf("Tuple1 is %s\n", result1 ? "distinct" : "not distinct");
    printf("Tuple2 is %s\n", result2 ? "distinct" : "not distinct");

    return 0;
}