#ifndef _LEXER_H_
#define _LEXER_H_

#include <iostream>
#include <iomanip>

#include <complex>
#include <cmath>

#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <ctype.h>

#include <stack>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;


struct Token {
	int type;
	complex <double> data;
	Token(int t = 0, complex <double> d = 0): type(t), data(d) {}
};

int ops_conv(char c);

void parse(vector <Token> &q, string &s);

bool syntax(vector <Token> &q);



#endif