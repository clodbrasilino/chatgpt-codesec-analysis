#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_DIGITS 10

struct IntTuple {
    int len;
    int* values;
};

int charToInt(char c) {
    return c - '0';
}

struct IntTuple parseTuple(char *str) {
    int strLength = strlen(str);

    struct IntTuple tuple;
    tuple.values = (int*)calloc(strLength , sizeof(int));

    for(int i = 0, tupleIndex = 0; i < strLength; ++i) {
        if(isdigit(str[i])) {
            int num = 0, digits = 0;
            while(i < strLength && isdigit(str[i])) {
                num = num * 10 + charToInt(str[i]);
                i += 1;
                digits += 1;
                if(digits >= MAX_DIGITS) {
                    break;
                }
            }
            tuple.values[tupleIndex] = num;
            tupleIndex += 1;
        }
    }

    return tuple;
}

void printTuple(struct IntTuple tuple) {
    putchar('(');
    for(int i = 0; i < tuple.len; ++i) {
        if(i != 0) {
            printf(", ");
        }
        printf("%d", tuple.values[i]);
    }
    printf(")\n");
}

void freeTuple(struct IntTuple *tuple) {
    free(tuple->values);
    tuple->values = NULL;
    tuple->len = 0;
}

int main() {
    char* tupleStr = "(32, 52, 76, 18, 90, 15)";
    struct IntTuple tuple = parseTuple(tupleStr);
    printTuple(tuple);
    freeTuple(&tuple);
    return 0;
}