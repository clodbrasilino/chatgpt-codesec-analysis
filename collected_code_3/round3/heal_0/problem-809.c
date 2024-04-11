#include <stdio.h>
#include <stdbool.h>

bool check_tuples(int first[], int second[], int size) {
    for(int i = 0; i < size; i++) {
        if(second[i] >= first[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int first[] = {5, 10, 15, 20, 25};
    int second[] = {1, 2, 3, 4, 5};
    int size = sizeof(first) / sizeof(first[0]);

    if(check_tuples(first, second, size)) {
        printf("Each element of the second tuple is smaller than its corresponding index in the first tuple.\n");
    } else {
        printf("Not all elements of the second tuple are smaller than their corresponding index in the first tuple.\n");
    }

    return 0;
}