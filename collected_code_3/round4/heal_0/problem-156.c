#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* first;
    char* second;
} StringTuple;

typedef struct {
    int first;
    int second;
} IntTuple;

IntTuple convertTuple(StringTuple st) {
    IntTuple it;
    it.first = atoi(st.first);
    it.second = atoi(st.second);
    return it;
}

int main() {
    StringTuple st = {"123", "456"};
    IntTuple it = convertTuple(st);
    printf("First: %d, Second: %d\n", it.first, it.second);
    return 0;
}