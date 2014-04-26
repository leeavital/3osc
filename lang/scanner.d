module scanner;

import std.stdio;


public string[] lex( string program ){
  string[] arr = [];
  string munch = "";
  foreach( i, ch ; program ){

    if( ch == '(' ){
      arr ~= [ ch ];
    }

    else if( ch == ')' ){
      if( munch != "" ){
        arr ~= munch;
        munch = "";
      }
      arr ~= [ ch ];
    }

    else if( (ch == ' ' ) && munch != "" ){
      arr ~= munch;
      munch = "";
    }
    else{
      munch = munch ~ [ch];
    }
  }


  return arr;

}



unittest{
  string[] s = lex( "(hello)" );
  assert( s == ["(", "hello", ")"] );
}


unittest{
  string[] s = lex("(+ 3 4)");

  assert( s == ["(", "+",  "3", "4", ")"] );

}
