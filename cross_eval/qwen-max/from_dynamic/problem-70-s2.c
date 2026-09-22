#include <stdio.h>
#include <stdlib.h>

int all_tuples_equal_length(const int *lengths, size_t count) {
    if (count == 0) return 1;
    for (size_t i = 1; i < count; ++i) {
        if (lengths[i] != lengths[0]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int lengths[] = {2, 2, 2};  // Example tuple lengths
    size_t count = sizeof(lengths) / sizeof(lengths[0]);
    if (all_tuples_equal_length(lengths, count)) {
        printf("All tuples have equal length.\n");
    } else {
        printf("Not all tuples have equal length.\n");
    }
    return 0;
}