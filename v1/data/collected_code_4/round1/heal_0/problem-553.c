#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double convert_tuple_to_float(char *tuple){
    char *end;
    double result;
    result = strtod(tuple, &end);
    if(tuple == end){
        printf("Conversion error, non-convertible part: %s", end);
        exit(1);
    }
    return result;
}

int main(){
    char tuple[] = "(3.14, 2.71)";
    char *tuple_ptr = tuple;
    double res1, res2;
    tuple_ptr += 1;    // Skip the "("

    res1 = convert_tuple_to_float(tuple_ptr);
    tuple_ptr = strchr(tuple_ptr, ',');  // Find the ","
    if (tuple_ptr != NULL) {
        tuple_ptr += 2;   // Skip the comma and space
        res2 = convert_tuple_to_float(tuple_ptr);
    }
    else {
        printf("Proper tuple format not detected.");
        return -1;
    }
    printf("Converted numbers are %f and %f", res1, res2);
    return 0;
}