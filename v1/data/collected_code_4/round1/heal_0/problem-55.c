#include <stdio.h>
#include <math.h>

double findTNthTerm(int a, double r, int n){
    
    if(n <= 0 || a==0 || r==0)
      return 0.0;
      
    double nthTerm = a * pow(r, n - 1);
  
    return nthTerm;
}

int main() {
    int a = 2; 
    double r = 3.0; 
    int n = 4;  
   
    double nthTerm = findTNthTerm(a, r, n);
    
    if(nthTerm != 0.0)
      printf("The term is %.2lf", nthTerm);
    else
      printf("Invalid Input");

    return 0;
}