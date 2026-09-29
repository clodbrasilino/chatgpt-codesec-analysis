#include <stdbool.h>

bool isSubset(int list1[], int n1, int list2[], int n2) {
    if (n1 == 0) {
        return true;
    }
    if (n2 == 0) {
        return false;
    }
    if (list1[0] == list2[0]) {
        return isSubset(list1 + 1, n1 - 1, list2 + 1, n2 - 1);
    }
    return isSubset(list1, n1, list2 + 1, n2 - 1);
}