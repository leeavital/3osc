#include "ftable.h"


#define TABLE_SIZE 20


typedef struct func{
    char* name;
    void* fn;
    int arity;
} t_func;


t_func functions[ TABLE_SIZE ];

int num_registered_functions = 0;


void ftable_register_function( char* func_name, void* fn, int arity){

    t_func fnc = (t_func){.name = func_name, .fn=fn, .arity = arity};
    functions[ num_registered_functions ] = fnc;
    num_registered_functions++;

}


void ftable_call_func( char* func_name, void** args ){
    t_func fnc;
    int i;

    for( i = 0; i < num_registered_functions; i++ ){
        if( functions[i].name == func_name ){
            fnc = functions[i];
        }
    }

    switch( fnc.arity ){
    case 1:
        ((void (*)(float)) (fnc.fn))( *((double*)(args[0])) );

    }

}
