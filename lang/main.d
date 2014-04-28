import std.stdio;


import scanner;
import parser;

int main(){
  string line;
  while ((line = stdin.readln()) !is null){
    auto tokens = scanner.lex( line );
    auto tree = parser.parse( tokens );

    auto n = tree[0].integer();

    writefln( "RESULT: %d", n );
  }


  return 0;
}
