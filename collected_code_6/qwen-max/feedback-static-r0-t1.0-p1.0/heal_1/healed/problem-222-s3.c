#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#define MAX_ELEMENTS 10

enum DataType {
    UNKNOWN,
    INTEGER,
    FLOAT,
    STRING
};

enum DataType getDataType(const void *data) {
    if (data == NULL) return UNKNOWN;

    long intTest = *(const long *)data;
    double floatTest = *(const double *)data;
    const char *stringTest = (const char *)data;

    if (stringTest[0] != '\0' && !isdigit(stringTest[0])) return STRING;
    if (intTest == (long)floatTest) return INTEGER;
    return FLOAT;
}

bool areAllElementsSameType(int count, ...) {
    va_list args;
    va_start(args, count);
    enum DataType firstType = UNKNOWN;
    bool result = true;

    for (int i = 0; i < count; ++i) {
        const void *elem = va_arg(args, const void *);
        enum DataType currentType = getDataType(elem);

        if (i == 0) {
            firstType = currentType;
            if (firstType == UNKNOWN) {
                result = false;
                break;
            }
        } else {
            if (currentType != firstType || currentType == UNKNOWN) {
                result = false;
                break;
            }
        }
    }

    va_end(args);
    return result;
}

int main() {
    int a = 10;
    int b = 20;
    double c = 30.5;
    double d = 40.5;
    char e[] = "example";
    char f[] = "example2";

    if (areAllElementsSameType(2, &a, &b)) printf("First test: All elements have the same type\n");
    else printf("First test: Elements have different types\n");

    if (areAllElementsSameType(2, &c, &d)) printf("Second test: All elements have the same type\n");
    else printf("Second test: Elements have different types\n");

    if (areAllElementsSameType(2, &c, &a)) printf("Third test: All elements have the same type\n");
    else printf("Third test: Elements have different types\n");

    if (areAllElementsSameType(2, &e, &f)) printf("Fourth test: All elements have the same type\n");
    else printf("Fourth test: Elements have different types\n");

    if (areAllElementsSameType(3, &a, &c, &e)) printf("Fifth test: All elements have the same type\n");
    else printf("Fifth test: Elements have different types\n");

    return 0;
}