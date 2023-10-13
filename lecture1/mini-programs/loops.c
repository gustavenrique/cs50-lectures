#include <stdio.h>
#include <cs50.h>

// declaring that there's gonna be this function
void meow(int l);

int main(void) { 
    
    int l = get_int("how many meows? ");
    meow(l);
    
}

void meow(int l) {
    // for (declaring the variable; applying the condition; counting)
    for (int i = 0; i < l; i++) {
        printf("meow!\n");
    }
}