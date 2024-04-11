#include <stdio.h>

struct Tuple {
    int a;
    float b;
    double c;
    char d;
};

int findSize(struct Tuple tuple) {
    return sizeof(tuple);
}

int main() {
    struct Tuple tuple = {1, 2.0f, 3.0, 'a'};
    printf("Size of tuple: %d bytes\n", findSize(tuple));
    return 0;
}