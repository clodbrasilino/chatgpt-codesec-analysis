#include <stdio.h>
#include <stdbool.h>

bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }
    
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    
    return true;
}

int smallestPrimeDivisor(int num) {
    if (num <= 1) {
        return -1;
    }
    
    for (int i = 2; i <= num; ++i) {
        if (num % i == 0 && isPrime(i)) {
            return i;
        }
    }
    
    return -1;
}