#include <stdio.h>
#include <stdbool.h>

struct Tuple {
    int key;
    int value;
};

bool checkIdentical(struct Tuple* list1, int size1, struct Tuple* list2, int size2) {
    if (size1 != size2) {
        return false;
    }
    
    for (int i = 0; i < size1; i++) {
        if (list1[i].key != list2[i].key || list1[i].value != list2[i].value) {
            return false;
        }
    }
    
    return true;
}

int main() {
    // Example usage
    struct Tuple list1[] = {{1, 10}, {2, 20}, {3, 30}};
    struct Tuple list2[] = {{1, 10}, {2, 20}, {3, 30}};
    int size1 = sizeof(list1) / sizeof(struct Tuple);
    int size2 = sizeof(list2) / sizeof(struct Tuple);

    if (checkIdentical(list1, size1, list2, size2)) {
        printf("Lists are identical\n");
    } else {
        printf("Lists are not identical\n");
    }

    return 0;
}