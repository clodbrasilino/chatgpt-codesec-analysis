#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool checkEquality(const char *list[], int size, const char *str) {
    for (int i = 0; i < size; i++) {
        if (strcmp(list[i], str) != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    const char *list[] = {"apple", "apple", "apple"};
    const char *str = "apple";
    int size = sizeof(list) / sizeof(list[0]);

    if(checkEquality(list, size, str))
        printf("All elements are equal to %s\n", str);
    else
        printf("Not all elements are equal to %s\n", str);

    return 0;
}