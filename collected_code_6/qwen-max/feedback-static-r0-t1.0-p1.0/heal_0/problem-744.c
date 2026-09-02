#include <stdio.h>
#include <stdbool.h>

bool has_none(const int *tuple, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (tuple[i] == -1) { // Assume -1 represents 'None'
            return true;
        }
    }
    return false;
}

int main() {
    int tuple1[] = {1, 2, 3, -1};
    int tuple2[] = {4, 5, 6, 7};
    
    size_t len1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t len2 = sizeof(tuple2) / sizeof(tuple2[0]);

    bool result1 = has_none(tuple1, len1);
    bool result2 = has_none(tuple2, len2);

    printf("Tuple1 has None: %s\n", result1 ? "Yes" : "No");
    printf("Tuple2 has None: %s\n", result2 ? "Yes" : "No");

    return 0;
}