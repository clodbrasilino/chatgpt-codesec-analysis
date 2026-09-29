#include <stdio.h>
#include <stddef.h>

unsigned long long count_sublists_containing_element(const int *list, size_t length, int element) {
    if (list == NULL || length == 0) {
        return 0;
    }

    unsigned long long total_sublists = (unsigned long long)length * ((unsigned long long)length + 1) / 2;
    unsigned long long sublists_without_element = 0;
    size_t segment_length = 0;

    for (size_t i = 0; i < length; ++i) {
        if (list[i] == element) {
            sublists_without_element += (unsigned long long)segment_length * ((unsigned long long)segment_length + 1) / 2;
            segment_length = 0;
        } else {
            ++segment_length;
        }
    }

    sublists_without_element += (unsigned long long)segment_length * ((unsigned long long)segment_length + 1) / 2;

    return total_sublists - sublists_without_element;
}

int main(void) {
    int values[] = {1, 2, 3, 2, 4, 2};
    size_t length = sizeof(values) / sizeof(values[0]);
    int element = 2;

    unsigned long long result = count_sublists_containing_element(values, length, element);

    printf("%llu\n", result);

    return 0;
}