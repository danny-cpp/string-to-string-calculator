#include "calculator.h"

using namespace std;




string calculate(string &s) {




	unordered_map <int,int> ord;
				//----------Table of precedence------------//
	ord[0] = 0;	// Placeholder 
	ord[1] = 3;	// Addition
	ord[2] = 3;	// Subtraction
	ord[3] = 4;	// Multiplication
	ord[4] = 4;	// Division
	ord[5] = 5;	// Exponent
	ord[6] = 2; // Left bracket
	ord[7] = 2;	// Right bracket
	
	//-------------------------------Table of function codes--------------------//
	//----function----- //-----syntax-----//-------code------//
	//   +,-,*, /       //     same       //   1,(1,2,3,4)   //
	//        ^         //       ^        //       1,5       // 
	//  sin, cos, tan   //   s(, c(, t(   //    3,(8,9,10) 	 // (Always with bracket)
	// asin, acos, atan // as(, ac(, at(  //    3,(11,12,13) //
	//   natural log    //       ln(      //       3,14      //
	//   square root    //       r(       //       3,15      //
	//    negative      //       _(       //       3,16      //
	
	
	

	string final;
	vector <Token> token_q;
	queue <Token> out_q;
	stack <int> ops_s;
	bool value_error = false;
	

	parse(token_q, s);
	bool syntax_error_flag = syntax(token_q);
	if (syntax_error_flag) {
		
		return "SYNTAX ERROR";
	}

	shunting_yard(token_q, ord, out_q, ops_s);
	complex <double> output  = post_fix(out_q, ops_s, value_error);
	


	if (value_error) {
		
		return "MATH ERROR";
	}


	
	if (real(output) == (int64_t)(real(output))) {
		int64_t tmpreal = (int64_t)(real(output));
		final = to_string(tmpreal);
	}
	else {
		final = to_string(real(output));
	}

	final += " + j";

	if (imag(output) == (int64_t)(imag(output))) {
		int64_t tmpimag = (int64_t)(imag(output));
		final += to_string(tmpimag);
	}
	else {
		final += to_string(imag(output));
	}
	

	return final;
	
}
