#include "lexer.h"

using namespace std;

int ops_conv(char c) {
	if (c == '+') {
		return 1;
	}
	if (c == '-') {
		return 2;
	}
	if (c == '*') {
		return 3;
	}
	if (c == '/') {
		return 4;
	}
	if (c == '^') {
		return 5;
	}
	if (c == '(') {
		return 6;
	}
	if (c == ')') {
		return 7;
	}
	if (c == 's') {
		return 8;
	}
	if (c == 'c') {
		return 9;
	}
	if (c == 't') {
		return 10;
	}
	if (c == 'l') {
		return 14;
	}
	if (c == 'r') {
		return 15;
	}
	

	return 0;
}

//-------------------------------Table of function codes--------------------//
//----function----- //-----syntax-----//-------code------//
//   +,-,*, /       //     same       //   1,(1,2,3,4)   //
//        ^         //       ^        //       1,5       //
//    brackets      //     ( , )      //      2,(6,7)    // 
//  sin, cos, tan   //   s(, c(, t(   //    3,(8,9,10) 	 // (Always with bracket)
// asin, acos, atan // as(, ac(, at(  //    3,(11,12,13) //
//   natural log    //       ln(      //       3,14      //
//   square root    //       r(       //       3,15      //
//    negative      //       _(       //       none      //
//   complex op     //       j(       //       none      //
//      log10       //       lg(      //       3,16      //


void parse(vector <Token> &token_vect, string &s) {
	
	int n = s.length();
	char char_array[n + 1];
	strcpy(char_array, s.c_str());

	string temp;
	int i = 0;
	while (i < n + 1) {
		char t = char_array[i];
		if (isdigit(t) || t == '.') {
			
			temp += char_array[i];
			//cout << temp << endl;
		}
		else if (t == 'P') {
			double PI = acos(-1);
			Token t = Token(0, PI);
			token_vect.push_back(t);
		}
		else if (t == 'j') {
			Token t1 = Token(0, complex <double> (0,1));
			token_vect.push_back(t1);
			Token t2 = Token(1, 3);
			token_vect.push_back(t2);
		}
		else if (t == '_') {
			Token t1 = Token(0, complex <double> (-1,0));
			token_vect.push_back(t1);
			Token t2 = Token(1, 3);
			token_vect.push_back(t2);
		}
		else if (t == 'e') {
			double e = exp(1);
			Token t = Token(0, e);
			token_vect.push_back(t);
		}
		else if (t == 'a') {
			if (char_array[i + 1] == 's') {
				Token t = Token(3, 11);
				token_vect.push_back(t);
			}
			else if (char_array[i + 1] == 'c') {
				Token t = Token(3, 12);
				token_vect.push_back(t);
			}
			else if (char_array[i + 1] == 't') {
				Token t = Token(3, 13);
				token_vect.push_back(t);
			}
			i++;
		}
		else if (t == 'l') {
			if (char_array[i + 1] == 'n') {
				Token t = Token(3, 14);
				token_vect.push_back(t);
			}
			else if (char_array[i + 1] == 'g') {
				Token t = Token(3, 16);
				token_vect.push_back(t);
			}
		}
		else {
			if (!temp.empty()) {
				Token t = Token(0, stod(temp));
				temp.clear();
				token_vect.push_back(t);
			}
			int temp = ops_conv(t);
			if (temp == 0) {
				
			}
			else if (temp == 6 || temp == 7) {
				Token t = Token(2, temp);
				token_vect.push_back(t);
			}
			else if (temp > 7) {
				Token t = Token(3, temp);
				token_vect.push_back(t);
			}
			else {
				Token t = Token(1, temp);
				token_vect.push_back(t);
			}
		}
		
		i++;
	}

}

enum State {NONE = -1, NUM = 0, BIN_OP = 1, FUNC = 3};

State st_conv(Token t) {
	if (t.type == 0) {
		return NUM;
	}
	else if (t.type == 1) {
		return BIN_OP;
	}
	else if (t.type == 3) {
		return FUNC;
	}
	else {
		return NONE;
	}
}

bool expected(State &previous, Token t) {
	State current = st_conv(t);
	if (previous == NONE) {
		return true;
	}
	else if (previous == NUM) {
		return (current == BIN_OP);
	}
	else if (previous == BIN_OP) {
		return (current == NUM) || (current == FUNC) || (current == NONE);
	}
	else if (previous == FUNC) {
		return (current == NUM) || (current == NONE);
	}

	return true;
}

bool syntax(vector <Token> &q) {
	/*---------------------------------------Error category---------------------------------*/
	// 1. Any position the no. of lbra must >= than the no. of rbra. At the end the no. of
	// 	  lbra must = rbra.

	unordered_map <int, int> brackets; // 0 key for lbra, 1 for rbra
	State current = NONE; 

	if (st_conv(q.front()) == BIN_OP) {
		return true;
	}


	for (auto x: q) {
		if (x.type == 2) {	
			if (real(x.data) == 6) {
				brackets[0]++;
			}
			else if (real(x.data) == 7) {
				brackets[1]++;
			}
		}
		if (brackets[0] < brackets[1]) {
			return true;
		}


		if (!expected(current, x)) {
			return true;
		}
		else {
			current = st_conv(x);
		}
	}

	if (brackets[0] != brackets[1]) {
		return true;
	}

	if (current == FUNC || current == BIN_OP) {
		return true;
	}


	return false;
}