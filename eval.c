#include "dsl.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct node t_node;

struct node{
    void* val;
    void* fn_evaluate;
    t_node* args;

};

int str_is_int( char* str );
t_node * parse( char* cmd );
void* eval( char* );
void* eval_node( t_node* );
void* identity( void*, t_node* );


// evaluate a string
void* eval( char* c ){
    t_node * root = parse( c );
    return eval_node( root );

}


// evaluate a node by calling it's evaluation function
// on it's value and on it's arguments
void* eval_node( t_node * node ){
    // extract the function pointer 
    void* (*fp)(void*, t_node*);
    fp = node->fn_evaluate;
    return fp( node->val, node->args );
}




t_node * parse( char* cmd ){
    t_node *n = (t_node*)malloc( sizeof( t_node ) );
    if( str_is_int( cmd  ) ){
        // set the evaluation function to the int identity 
        n->fn_evaluate = (void*)identity;

        // set the value to an int
        int* ptr = (int *)(malloc( sizeof( int ) ));
        *ptr = atoi( cmd );
        n->val = ptr;
    }
    return n;

}


void* identity( void *i , t_node* _args){
    return i;
}


int str_is_int( char* c ){
    int i;
    for( i = 0; i < strlen( c ); i++ ){
        if( c[i] < '0' || c[i] > '9' ){
            return 0;
        }
    }
    return 1;
}
