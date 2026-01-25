#include <stdio.h>

int addition_mod (int a, int b){
	return (a + b) % (2 * a);
}

int main() {
    int res = addition_mod(1, 2);
    printf("The result is %d\n", res);   
    return 0;
}
