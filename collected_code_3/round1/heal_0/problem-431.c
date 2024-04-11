#include <stdbool.h>
#include <stdio.h>

bool has_common_element(int* list1, int len1, int* list2, int len2) {
    for(int i = 0; i < len1; i++) {
        for(int j = 0; j < len2; j++) {
            if(list1[i] == list2[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {6, 7, 8, 9, 10};
    int len1 = sizeof(list1) / sizeof(list1[0]);
    int len2 = sizeof(list2) / sizeof(list2[0]);

    if(has_common_element(list1, len1, list2, len2)) {
        printf("The lists have at least one common element.\n");
    } else {
        printf("The lists do not have any common elements.\n");
    }

    return 0;
}