#ifndef FTABLE_H
#define FTABLE_H


void ftable_register_function( char* func_name, void* fn, int arity);


void ftable_call_func( char* func_name, void** args );
#endif
