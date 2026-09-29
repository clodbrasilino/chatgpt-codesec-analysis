#include <stdbool.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

bool is_sublist(const int *list, int list_size, const int *sublist, int sublist_size) {
    for (int i = 0; i <= list_size - sublist_size; ++i) {
        bool match = true;
        for (int j = 0; j < sublist_size; ++j) {
            if (list[i + j] != sublist[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6};
    int sublist[] = {4, 5, 6};
    int list_size = sizeof(list) / sizeof(list[0]);
    int sublist_size = sizeof(sublist) / sizeof(sublist[0]);

    bool result = is_sublist(list, list_size, sublist, sublist_size);
    if (result) {
        printf("Sublist found.\n");
    } else {
        printf("Sublist not found.\n");
    }

    return 0;
}