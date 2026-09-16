#include <stdio.h>
#include <stdbool.h>

bool is_even_at_even_index(const int *list, int length) {
    for (int i = 0; i < length; i += 2) {
        if (list[i] % 2 != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int list[] = {2, 3, 4, 5, 6};
    int length = sizeof(list) / sizeof(list[0]);
    bool result = is_even_at_even_index(list, length);
    
    if (result) {
        printf("Every even index contains an even number.\n");
    } else {
        printf("Not every even index contains an even number.\n");
    }
    
    return 0;
}