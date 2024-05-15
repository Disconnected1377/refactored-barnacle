#include <stdio.h>
#include <math.h>

long long int modular_exponentiation(long long int base, long long int exponent, long long int modulus) {
    long long int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent / 2;
        base = (base * base) % modulus;
    }
    return result;
}

long long int CALCULATE(long long int g, long long int a, long long int p) {
    if (g == 1) {
        return 1;
    } else {
        return modular_exponentiation(g, a, p);
    }
}


int main(){
    long long int a,b,x,y,p,g,ka,kb;

    printf("Enter the value of p: ");
    scanf("%lld",&p);

    printf("Enter the value of g: ");
    scanf("%lld",&g);

    printf("Enter the secrate key of A: ");
    scanf("%lld",&a);

    printf("Enter the secrate key of B: ");
    scanf("%lld",&b);

    x=CALCULATE(g,a,p);
    y=CALCULATE(g,b,p);

    printf("value of x  and y: %lld %lld\n\n",x,y);

    ka=CALCULATE(y,a,p);
    kb=CALCULATE(x,b,p);

    printf("Secrate key for A: %lld\n",ka);
    printf("Secrate key for B: %lld\n",kb);
    return 0;
}