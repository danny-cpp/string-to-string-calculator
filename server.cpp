#include <iostream>
#include "calculator.h"
#include "serialport.h"
using namespace std;

int main() {
////change depend on the connecting board////
    SerialPort Serial("/dev/ttyACM0");///////
/////////////////////////////////////////////	
	string s;
	string table1 = "\n/-------Table of function syntax----/\n";
	string table2 = "/----function----- /-----syntax-----/\n";
	string table3 =	"/   +,-,*, /       /     same       /\n";
	string table4 =	"/        ^         /       ^        /\n";
	string table5 =	"/    brackets      /     ( , )      / \n";
	string table6 =	"/  sin, cos, tan   /   s(, c(, t(   / (Always with bracket)\n";
	string table7 =	"/ asin, acos, atan / as(, ac(, at(  /\n";
	string table8 =	"/   natural log    /       ln(      /\n";
	string table9 =	"/   square root    /       r(       / \n";
	string table10 =	"/    negative      /       _(       /\n";
	string table11 =	"/   complex op     /       j(       / \n";
	string table12 =	"/      log10       /       lg(      /\n";

	cout << table1 + table2 + table3 + table4 + table5 + table6 + table7 + table8 + table9 + table10 + table11 + table12 << endl;
	
	cout << "Please input your equation: " << endl;
    while(true){
    	string s;
    	s = Serial.readline();
    	cout<<"recieve equation: "<< s <<endl;
    	//string s = "9 + 4 * 3 + 7 ^ 2 ^ 3";
    	string out = calculate(s);
    	do{
    		Serial.writeline(out+"\n");
    	}while(Serial.readline() != "r\n");	
    	cout << out << endl;
    }
	return 0;
}