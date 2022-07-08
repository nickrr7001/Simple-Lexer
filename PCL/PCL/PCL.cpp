// PCL.cpp : Defines the entry point for the application.
//
#include <string>
#include <vector>
#include "PCL.h"
#include "Lexer.cpp"
using namespace std;

int main()
{
	string code = "def function () { x = 10 ; x += 2 ; }";
	Lexer l = Lexer(code);
	vector<Token> tokens = l.lex();
	for (Token t : tokens) {
		cout << t.TText << "(" << t.tokenType << ")";
	}
	return 0;
}
