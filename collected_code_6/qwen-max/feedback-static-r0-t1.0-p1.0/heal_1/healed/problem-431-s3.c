#include <stdio.h>
#include <stdbool.h>

bool has_common_element(const int *list1, int list1_size, const int *list2, int list2_size) {
    for (int i = 0; i < list1_size; i++) {
        for (int j = 0; j < list2_size; j++) {
            if (list1[i] == list2[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {4, 5, 6, 7, 8};

    int list1_size = sizeof(list1) / sizeof(list1[0]);
    int list2_size = sizeof(list2) / sizeof(list2[0]);

    bool result = has_common_element(list1, list1_size, list2, list2_size);
    printf("%s\n", result ? "True" : "False");

    return 0;
}