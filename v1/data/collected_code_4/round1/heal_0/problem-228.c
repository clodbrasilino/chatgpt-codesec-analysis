#include <stdio.h>
#include <stdbool.h>

bool areBitsUnset(int num, int begin, int end) {
    int mask = ((1 << (end - begin + 1)) - 1) << begin;
    return (num & mask) == 0;
}

//Main function
int main() {
    int num, begin, end;

    printf("Enter the number: ");
    scanf("%d", &num);

    printf("Enter the beginning of range: ");
    scanf("%d", &begin);

    printf("Enter the end of range: ");
    scanf("%d", &end);

    if(begin >= 0 && end >= begin && end < (8 * sizeof(num))) {
        if(areBitsUnset(num, begin, end)) {
            printf("All bits are unset in the given range.\n");
        } else {
            printf("Some bits are set in the given range.\n");
        }
    } else {
        printf("Invalid range input.\n");
    }

    return 0;
}