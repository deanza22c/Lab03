// 
// Lab 03
// Names: Alexander McNulty, Clifford Smith

/*
	This lab demonstrates use of stack to make simple mathematical computations.
	The program runs on two stacks, controlled by the InfixCalculator

	use:
		-setInfixExpression(string) -  to submit an expression to the calculator, DOES NOT check for errors
		-evaulateExpression() - to evaulate the expression and produce a result inside the object.
							   ****DOES check for errors, if error, result value set to 0****
		-getResults() - returns the results of the expression.
					   if an improper expression is evaulated result will equal zero

	calculator limitations:
		-single digit numbers
		-single character opperators
*/

#include <iostream>
#include <string>
#include "InfixCalculator.h"

using namespace std;

int main(){

	InfixCalculator infixCalculator;

	cout << "Evaluating test expressions...\n\n";
	
	//first expression
	infixCalculator.setInfixExpression("9*8+2*(2+5)/6");
	infixCalculator.evaluateExpression();
	cout << "9*8+2*(2+5)/6 = " << infixCalculator.getResults() << endl;

	//second expression
	infixCalculator.setInfixExpression("9*2/8+9");
	infixCalculator.evaluateExpression();
	cout << "9*2/8+9 = " << infixCalculator.getResults() << endl;

	//third expression - invalid - error : double digit number '22'
	infixCalculator.setInfixExpression("1+2222+(3+4)");
	infixCalculator.evaluateExpression();
	cout << "1+2222+(3+4) = " << infixCalculator.getResults() << endl;

	//fourth expression - invalid - error : '++'
	infixCalculator.setInfixExpression("1+2-(3++4)");
	infixCalculator.evaluateExpression();
	cout << "1+2-(3++4) = " << infixCalculator.getResults() << endl;

	//fifth expression - invalid - error : beginning with ')'
	infixCalculator.setInfixExpression(")1+2-3+4");
	infixCalculator.evaluateExpression();
	cout << ")1+2-(3+4) = " << infixCalculator.getResults() << endl;

	//sixth expression - invalid - error : undefined logic '2(3'
	infixCalculator.setInfixExpression("1+2(3+4");
	infixCalculator.evaluateExpression();
	cout << "1+2(3+4) = " << infixCalculator.getResults() << endl;
	
	//eight expression
	infixCalculator.setInfixExpression("1+2-(3+4)");
	infixCalculator.evaluateExpression();
	cout << "1+2-(3+4) = " << infixCalculator.getResults() << endl;


	cin.get();

	return 0;
}