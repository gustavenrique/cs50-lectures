#include <cs50.h>
#include <stdio.h>

int main(void) {
    long x = get_long("x: ");
    long y = get_long("y: ");
    
    printf("The sum between them is: %li\n", x + y);
}