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
    // a 100-deep list of t_nodes
    t_node* context[ 20 ];
    int context_depth = 0;

    // the next sequence we will munch, make sure it is zeroed
    char munch[ 32 ];
    int munch_i = 0;
    // bzero( munch, 32 );
    printf( "Here\n");
    for( int i = 0; i < strlen( cmd ); i++ ){
        char c = cmd[ i ];

        printf( "char %c\n", c );
        // if we have an lparen, we need to push a node onto the context
        if( c == '('){
            context[ context_depth ] = (t_node*)(malloc( sizeof( t_node ) ));
            context_depth++;
        }

        else if( c == ' ' ){
            printf("muched %s\n", munch );
            // if we have munched an int, put it into the current node
            if( str_is_int( munch ) ){
                void* data = malloc( sizeof( int ) );
                *((int*)(data)) = atoi( munch );
                context[ context_depth - 1]->val = data;
                context[ context_depth - 1]->fn_evaluate = identity;
            }
            bzero( munch, 32 );
            munch_i = 0;
        }

        else{
            munch[  munch_i ] = c;
            munch_i++;
        }

    } // end for

    return context[ 0 ];
    // t_node *n = (t_node*)malloc( sizeof( t_node ) );
    // if( str_is_int( cmd  ) ){
    //     // set the evaluation function to the int identity 
    //     n->fn_evaluate = (void*)identity;

    //     // set the value to an int
    //     int* ptr = (int *)(malloc( sizeof( int ) ));
    //     *ptr = atoi( cmd );
    //     n->val = ptr;
    // }
    // return n;

}


// the identity function, used as the evaluation
// function when the node is a scalar value (e.g. string,
// int, float)
//
// so, eval( "3" ) would resolve to identity( &3, NULL );
void* identity( void *i , t_node* _args){
    return i;
}


// determine if a string is an int
int str_is_int( char* c ){
    int i;
    for( i = 0; i < strlen( c ); i++ ){
        if( c[i] < '0' || c[i] > '9' ){
            return 0;
        }
    }
    return 1;
}
