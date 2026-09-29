#include <stdio.h>
#include <stdbool.h>

bool areBitsUnsetInRange(int n, int l, int r) {
    int mask = ((1 << (r - l + 1)) - 1 ) << l;
    return (n & mask) == 0;  
}

int main() {
    int n = 15;
    int l = 1;
    int r = 3;
    if(areBitsUnsetInRange(n, l, r)){
        printf("All bits in range are unset \n");
    } else {
        printf("All bits in range are not unset \n");
    }
    return 0;
}