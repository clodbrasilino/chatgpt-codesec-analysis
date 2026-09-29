#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float part1;
    float part2;
} FloatTuple;

FloatTuple string_to_float_tuple(const char* input_string) {
    FloatTuple result = {0.0f, 0.0f};
    char* string_copy = NULL;
    char* token = NULL;
    char* endptr = NULL;

    if (input_string == NULL) {
        return result;
    }

    string_copy = strdup(input_string);
    if (string_copy == NULL) {
        return result;
    }

    token = strtok(string_copy, ", ");
    if (token != NULL) {
        result.part1 = strtof(token, &endptr);
        if (*endptr != '\0') {
            result.part1 = 0.0f; 
        } else {
            token = strtok(NULL, ", ");
            if (token != NULL) {
                result.part2 = strtof(token, &endptr);
                if (*endptr != '\0') {
                    result.part2 = 0.0f;
                }
            }
        }
    }

    free(string_copy);
    return result;
}

int main(void) {
    const char* float_str1 = "3.14, 2.71";
    FloatTuple tuple1 = string_to_float_tuple(float_str1);
    printf("Tuple 1: (%f, %f)\n", tuple1.part1, tuple1.part2);

    const char* float_str2 = "-1.5 4.2";
    FloatTuple tuple2 = string_to_float_tuple(float_str2);
    printf("Tuple 2: (%f, %f)\n", tuple2.part1, tuple2.part2);

    const char* float_str3 = "invalid, string";
    FloatTuple tuple3 = string_to_float_tuple(float_str3);
    printf("Tuple 3: (%f, %f)\n", tuple3.part1, tuple3.part2);

    return 0;
}