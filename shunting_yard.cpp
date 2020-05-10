#include "shunting_yard.h"

void shunting_yard(vector <Token> &token_q, unordered_map <int,int> &ord, 
							queue <Token> &out_q, stack <int> &ops_s) {

	ops_s.push(0);

	for (auto x: token_q) {
		if (x.type == 0) {
			out_q.push(x);
		}
		else if (x.type == 3) {
			ops_s.push(real(x.data));
		}
		else if (x.type == 1) {

			while ( 
				(
				(ops_s.top() < 10 && ops_s.top() > 7) 
				|| (ord[ops_s.top()] > ord[real(x.data)]) 
				)

				&& ops_s.top() != 6

				) {
				
				if (ops_s.top() < 7) {
					out_q.push(Token(1, ops_s.top()));
				}
				else if (ops_s.top() > 7 && ops_s.top() <= 10) {
					out_q.push(Token(3, ops_s.top()));
				}
				ops_s.pop();
			}

			ops_s.push(real(x.data));



		}
		else if (x.type == 2 && real(x.data) == 6) {
			ops_s.push(6);
		}
		else if (x.type == 2 && real(x.data) == 7) {
			while (ops_s.top() != 6) {
				if (ops_s.top() < 7) {
					out_q.push(Token(1, ops_s.top()));
				}
				else if (ops_s.top() > 7 && ops_s.top() <= 10) {
					out_q.push(Token(3, ops_s.top()));
				}
				ops_s.pop();
			}
			ops_s.pop();
		}
	}

	while (ops_s.top() != 0) {
		if (ops_s.top() < 7) {
			out_q.push(Token(1, ops_s.top()));
		}
		else if (ops_s.top() > 7) {
			out_q.push(Token(3, ops_s.top()));
		}
		ops_s.pop();
	}

}


complex <double> post_fix(queue <Token> &out_q, stack <int> &ops_s, bool &error) {
	stack <complex<double>> sk;
	while (!out_q.empty()) {
		Token t = out_q.front();
		if (t.type == 0) {
			sk.push(t.data);
		}
		else if (t.type == 1) {
			complex<double> d1 = sk.top();
			sk.pop();
			complex<double> d2 = sk.top();
			sk.pop();
			if (real(t.data) == 1) {
				sk.push(d1 + d2);
			}
			else if (real(t.data) == 2) {
				sk.push(d2 - d1);
			}
			else if (real(t.data) == 3) {
				sk.push(d2 * d1);
			}
			else if (real(t.data) == 4) {
				if (d1 != complex <double> (0,0) ) {
					sk.push(d2 / d1);
				}
				else {
					error = true;
					return 0;
				}
			}
			else if (real(t.data) == 5) {
				if (!( d1 == complex <double> (0,0) && d2 == complex <double> (0,0))) {
					sk.push(pow(d2, d1));
				}
				else {
					error = true;
					return 0;
				}
			}
		}
		else if (t.type == 3) {
			complex<double> d1 = sk.top();
			sk.pop();
			if (real(t.data) == 8) {
				sk.push(sin(d1));
			}
			else if (real(t.data) == 9) {
				sk.push(cos(d1));
			}
			else if (real(t.data) == 10) {
				sk.push(tan(d1));
			}
			else if (real(t.data) == 11) {
				sk.push(asin(d1));
			}
			else if (real(t.data) == 12) {
				sk.push(acos(d1));
			}
			else if (real(t.data) == 13) {
				sk.push(atan(d1));
			}
			else if (real(t.data) == 14) {
				if (real(d1) == 0 && imag(d1) == 0) {
					error = true;
					return 0;
				}
				sk.push(log(d1));
			}
			else if (real(t.data) == 15) {
				sk.push(sqrt(d1));
			}
			else if (real(t.data) == 16) {
				if (real(d1) == 0 && imag(d1) == 0) {
					error = true;
					return 0;
				}
				sk.push(log10(d1));
			}
			
		}



		out_q.pop();
	}
	return sk.top();
}