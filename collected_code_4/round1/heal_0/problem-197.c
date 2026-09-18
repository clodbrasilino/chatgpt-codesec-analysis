#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Tuple {
    long long first;
    long long second;
} Tuple;

Tuple* exponentiation(Tuple* tuple1, Tuple* tuple2) {
    if(!tuple1 || !tuple2) {
        return NULL;
    }
    
    Tuple* result = (Tuple*)malloc(sizeof(Tuple));
    if(!result) {
        return NULL;
    }
    
    result->first = pow(tuple1->first, tuple2->first);
    result->second = pow(tuple1->second, tuple2->second);

    return result;
}

int main() {
    Tuple tuple1;
    tuple1.first = 2;
    tuple1.second = 3;
    
    Tuple tuple2;
    tuple2.first = 4;
    tuple2.second = 5;
    
    Tuple* result = exponentiation(&tuple1, &tuple2);
    
    if(result){
        printf("Exponentiation Result: (%lld, %lld)\n", result->first, result->second);
        free(result);
    } else {
        printf("Failed to Calculate Exponentiation.\n");
    }
    
    return 0;
}