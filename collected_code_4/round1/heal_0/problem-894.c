#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float first;
    float second;
} Tuple;

Tuple string_to_tuple(char* str) {
    Tuple result;
    char* end;
    if (str == NULL) {
        result.first = 0;
        result.second = 0;
        return result;
    }
    else {
        result.first = strtof(str, &end);
        if (*end != ',') {
            result.first = 0;
            result.second = 0;
            return result;
        }
        else {
            result.second = strtof(end + 1, &end);
            if (*end != '\0') {
                result.first = 0;
                result.second = 0;
            }
            return result;
        }
    }
}

int main() {
    char* test = "123.4,567.8";
    Tuple t = string_to_tuple(test);
    printf("(%f, %f)\n", t.first, t.second);
    return 0;
}