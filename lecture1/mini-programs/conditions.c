#include <cs50.h>
#include <stdio.h>

int main(void) {
    //getting the character from the user
    char a = get_char("Do you agree? ");
    
    //verifying the answer (it has to be a single quote to characters)
    if (a == 'y' || a == 'Y') {
        printf("Agreed!\n");
    } 
    else if (a == 'N' || a == 'n') {
        printf("Disagreed.\n");
    }
    
}