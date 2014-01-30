#include <stdio.h>
#include "3osc.h"
#include "ftable.h"

int main(){
    // oscInit();
    // oscStartLoop();

    char ch;
    while( (ch = getchar()) != '.'  ){
        printf( "got %c\n", ch);
        fflush( stdout );
    }
    char *str = "setFrequency";
    ftable_register_function( str, &setFrequency, 1 );


    void* args[1];
    double arg = 220.0;
    args[0] = &arg;
    ftable_call_func( str, args );

    /// printf( "frequency %f\n", frequency);




}
