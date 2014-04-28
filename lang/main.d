import std.stdio;


import scanner;
import parser;


int main(){
  string line;
  writefln( "3OSC SHELL");
  writef( ">>" );
  while ((line = stdin.readln()) !is null){
    auto tokens = scanner.lex( line );
    auto tree = parser.parse( tokens );

    auto n = tree[0].integer();

    writefln( "RESULT: %d", n );
    writef( ">>" );
  }


  return 0;
}
