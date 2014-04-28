import std.stdio;


import scanner;
import parser;

int main(){
  string line;
  while ((line = stdin.readln()) !is null){
    auto tokens = scanner.lex( line );
    auto tree = parser.parse( tokens );

    int i = tree[0].evaluate();

    writefln( "RESULT: %d", i );

  }


  return 0;
}

