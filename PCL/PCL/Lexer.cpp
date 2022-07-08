#include <string>
#include <vector>
#include <regex>
#include<iostream>
using namespace std;
class Token {
public:
	string tokenType;
	string TText;
	Token(string tt, string text) {
		tokenType = tt;
		TText = text;
	}
};
class SequenceRule {
public:
	string tokenName;
	string tokenRegex;
	bool isOmmitted;
	SequenceRule(string tn, string reg, bool ommit = false) {
		tokenName = tn;
		tokenRegex = reg;
		isOmmitted = ommit;
	}
};
class Lexer {
public:
	Lexer(string code) {
		curCode = code;
	}
	vector<Token> lex() {
		nextToken();
		return retVal;
	}
	//Precedence - those that take precedence should occur in the array first!
private:
	string curCode;
	vector<Token> retVal;
	SequenceRule rules[8] = {
		SequenceRule("WhiteSpace","[\\f\\n\\r\\t\\v]",true),
		SequenceRule("end-statement",";"),
		SequenceRule("LParen","\\("),
		SequenceRule("RParen","\\)"),
		SequenceRule("number","-?[0-9]+"),
		SequenceRule("operator","[=|+|-|*|\\/|>|<]"),
		SequenceRule("function","def"),
		SequenceRule("identifier","[a-z|A-Z]*[\\f\\n\\r\\t\\v]+")

	};
	bool ruleFound(string subSTR) {
		for (int i = 0; i < 8; i++)
		{
			try {
				regex reg(rules[i].tokenRegex);
				smatch matches;
				regex_search(subSTR, matches, reg);
				if (matches.size() != 0) {
					//Match was found! Meaning a token was found
					Token t = Token(rules[i].tokenName, subSTR);
					retVal.push_back(t);
					return true;
				}
			}
			catch (exception e) {
				cout << rules[i].tokenRegex << endl;
				continue;
			}
		}
		return false;
	}
	void nextToken() {
		//continue through code untill match is found
		//remove match from curcode, add equivelant token to retVal
		int n = curCode.length();
		int subStrStart = 0;
		for (int i = 0; i < curCode.length(); i++)
		{
			if (ruleFound(curCode.substr(subStrStart, (i + 1) - subStrStart))) {
				subStrStart = i+1;
			}
		}
	}
};
