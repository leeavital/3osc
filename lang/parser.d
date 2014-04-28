module parser;

import scanner;
import std.regex;
import std.conv;
import std.stdio;
import std.array;


public class Node {

  abstract int integer();
}

public class IntNode : Node  {

  int val;
  public this( int val ){
    this.val = val;
  }

  override int integer(){
    return val;
  }


}


public class ApplyNode : Node{
  string op;
  Node[] args;
  public this( string op ){
    this.op = op;
  }
  private Node evaluate(){
    if( op == "+" ){
      int i = 0;
      foreach( n ;  this.args ){
        i += n.integer();
      }
      return new IntNode( i  );
    }

    if( op == "-" ){
      return new IntNode( args[0].integer() - args[1].integer() );
    }




    return new IntNode( 0 );
  }

  override int integer(){
    return evaluate().integer();
  }
}


public Node[] parse( string[] tokens ){
  Node[] stack = [];

  auto i = 0;

  while( i < tokens.length ){
    if( tokens[i] == "(" && is_function( tokens[i + 1] ) ){
      stack ~= new ApplyNode( tokens[i + 1] ); 
      i += 2;
    }

    else if( is_int( tokens[i] ) ){
      stack ~= new IntNode( to!int( tokens[i] ) );
      i++;
    }


    else if( tokens[i] == ")" ) {
      // accept a FunctionNode
      // TODO refactor "accept" into its own methods
      Node[] args = [];
      while( ! cast(ApplyNode) (stack.back)  ){
        args ~= stack.back;
        popBack( stack );
      }
      auto app= cast(ApplyNode)(stack.back);
      while( ! args.empty ){
        app.args ~= back( args );
        popBack( args );
      }


      i++;
    }

  }

  return stack;


}


bool is_function( string t ){
  return ( t == "+" || t == "-" || t == "*" || t == "/" );
}

bool is_int( string t ){
  auto r = regex( r"^(-?)\d+$" );
  return ! match( t, r ).empty();
}

unittest{
  assert( is_function( "-" ) );
}


unittest{
  assert( is_int( "23232" ), "is_int 1" );
  assert( is_int( "-23232" ), "is_int 2" );
  assert( ! is_int( "Hello world" ), "is_int 3" );
  assert( ! is_int( "123world" ), "is_int 4" );
  assert( ! is_int( "Hello123" ), "is_int 5" );
}




unittest{
  auto toks = [ "3" ];
  auto node = parse( toks )[0];

  assert(  node.integer() == 3 , "simple value" );

}

unittest{
  auto nodes = parse( ["(", "+", "3", "4", ")"] );
  assert( cast(ApplyNode)(nodes[0] ) );

  assert( nodes.length == 1 );

  assert( nodes[0].integer() == 7 , "One level add" );
}


unittest{
  auto nodes = parse( ["(", "-", "5", "3", ")" ] );
  assert( nodes[0].integer()  == 2, "single subtract" );
}
