#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    int first;
    double second;
    const char *third;
} Tuple;

static bool tuple_is_valid(const Tuple *tuple)
{
    return tuple != NULL &&
           tuple->first >= 0 &&
           tuple->second >= 0.0 &&
           tuple->third != NULL &&
           tuple->third[0] != '\0';
}

int main(void)
{
    const Tuple tuple = {42, 3.14, "valid"};

    if (printf("%s\n", tuple_is_valid(&tuple) ? "Valid" : "Invalid") < 0) {
        return 1;
    }

    return 0;
}