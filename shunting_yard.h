#ifndef _SHUNTING_YARD_H_
#define _SHUNTING_YARD_H_

#include <iostream>
#include <iomanip>

#include <complex>
#include <cmath>

#include <stack>
#include <queue>
#include <unordered_map>
#include <vector>

#include "lexer.h" // for Token struct

using namespace std;


void shunting_yard(vector <Token> &token_q, unordered_map <int,int> &ord, 
							queue <Token> &out_q, stack <int> &ops_s);


complex <double> post_fix(queue <Token> &out_q, stack <int> &ops_s, bool &error);



#endif