// ���������� ������� � ������� ��� ���������� �������������� ���������

#include "arithmetic.h"
#include <string>
#include "stack.h"
ArithmeticExpr::ArithmeticExpr(string infx) {
	infix = infx;
}
int StringIsAlmostCorrect(string s) { 
	int count = 0;
	if (s[0] == 'e' && s[1] != 'x') return 0; //e for numbers, it cannot be the first character
	if (s[s.length() - 1] == 'e') return s.length() - 1; //e for numbers, it cannot be the last character
	for (int i = 0; i < s.length(); i++) {
		if ((s[i] == '('|| s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && (s[i + 1] == ')' || s[i + 1] == '+' || s[i + 1] == '*' || s[i + 1] == '/')) {
			return i; //checking for errors (*, +*, etc.
		}
		if (s[i] == ')' && s[i + 1] == '(') return i; // checking for )(
		if (s[i] == ' ') return i; // no gaps
		if (s[i] == '(') count++;
		if (s[i] == ')') count--;
		if (i >= 1) {
			if (s[i] == 'x' && (s[i - 1] == '0' || s[i - 1] == '1' || s[i - 1] == '2' || s[i - 1] == '3' || s[i - 1] == '4' || s[i - 1] == '5' || s[i - 1] == '6' || s[i - 1] == '7' || s[i - 1] == '8' || s[i - 1] == '9')){
				return i; //exclusion of situations 6+78x65
			}
		}
		if ((s[i] == '0' || s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9')&&(!(s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/'||s[i+1]==')'||s[i + 1] == '.' || s[i + 1] == 'e'||s[i + 1] == '0' || s[i + 1] == '1' || s[i + 1] == '2' || s[i + 1] == '3' || s[i + 1] == '4' || s[i + 1] == '5' || s[i + 1] == '6' || s[i + 1] == '7' || s[i + 1] == '8' || s[i + 1] == '9'||s[i+1]=='\0'))) {
			return i; //exclusion of situations 6sin(8)
		}
		if ((s[i] == 'x'&&s[i+1]!='p') && (!(s[i + 1] == '0' || s[i + 1] == '1' || s[i + 1] == '2' || s[i + 1] == '3' || s[i + 1] == '4' || s[i + 1] == '5' || s[i + 1] == '6' || s[i + 1] == '7' || s[i + 1] == '8' || s[i + 1] == '9'))) {
			return i; // correct input of variables, such as x*, where * is any number
		}
		if (i == 0 && s[i] == '.') {
			if (!(s[i + 1] == '0' || s[i + 1] == '1' || s[i + 1] == '2' || s[i + 1] == '3' || s[i + 1] == '4' || s[i + 1] == '5' || s[i + 1] == '6' || s[i + 1] == '7' || s[i + 1] == '8' || s[i + 1] == '9')) return i;
		} // if . the first character, then a digit is required after it
		else if (i > 0 && s[i] == '.') {
			if (!(s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '0' || s[i + 1] == '1' || s[i + 1] == '2' || s[i + 1] == '3' || s[i + 1] == '4' || s[i + 1] == '5' || s[i + 1] == '6' || s[i + 1] == '7' || s[i + 1] == '8' || s[i + 1] == '9' || s[i + 1] == 'e') &&
				!(s[i - 1] == '+' || s[i - 1] == '-' || s[i - 1] == '*' || s[i - 1] == '/' || s[i - 1] == '0' || s[i - 1] == '1' || s[i - 1] == '2' || s[i - 1] == '3' || s[i - 1] == '4' || s[i - 1] == '5' || s[i - 1] == '6' || s[i - 1] == '7' || s[i - 1] == '8' || s[i - 1] == '9')) return i;
		} //near . there are no invalid characters

		
		else if (i > 0 && s[i] == 'e' && s[i+1] != 'x' && s[i+2] != 'p') {
			if (!(s[i + 1] == '+' || s[i + 1] == '-') ||!(s[i - 1] == '0' || s[i - 1] == '1' || s[i - 1] == '2' || s[i - 1] == '3' || s[i - 1] == '4' || s[i - 1] == '5' || s[i - 1] == '6' || s[i - 1] == '7' || s[i - 1] == '8' || s[i - 1] == '9' || s[i - 1] == '.')) return i;
		}// there are no incorrect characters near e

		if ((s[i] == 's' && s[i + 1] == 'i' && s[i + 2] == 'n' && s[i + 3] != '(')) return i; //correctness of function input
		if ((s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 's' && s[i + 3] != '(')) return i;
		if ((s[i] == 'e' && s[i + 1] == 'x' && s[i + 2] == 'p' && s[i + 3] != '(')) return i;
		if ((s[i] == 'c' && s[i + 1] == 't' && s[i + 2] == 'g' && s[i + 3] != '(')) return i;
		if ((s[i] == 't' && s[i + 1] == 'g' && s[i + 2] != '(')) return i;
		if ((s[i] == 'l' && s[i + 1] == 'n' && s[i + 2] != '(')) return i;
		
	}
	
	if (s[s.length() - 1] == '(' || s[s.length() - 1] == '+' || s[s.length() - 1] == '-' || s[s.length() - 1] == '*' || s[s.length() - 1] == '/') return -1; // the line does not end with the or operation (
	if (count != 0) return -2; // the quantities '(' and ')' are equal
	return -128;
}
void ArithmeticExpr::Parse() {
	int cor = StringIsAlmostCorrect(infix);
	if (cor!=-128) throw logic_error("There is an assumed error in the string in character number: " + to_string(cor));
	int i = 0;
	if (infix[0] == '-') {
		lexems.push_back("~");
		i++;
	}
	for (i; i < infix.length(); i++) {
		if (infix[i] == '+' || infix[i] == '*' || infix[i] == '/'||infix[i]=='('||infix[i]==')')
			lexems.push_back(string(1,infix[i]));
		else if (infix[i] == '-') {
			if (infix[i - 1] == '(')
				lexems.push_back("~");
			else lexems.push_back(string(1, infix[i]));
		}
		else {
			string tmp = strNumberOrVar(infix.substr(i)); 
			if (tmp.length() != 0) {
				lexems.push_back(tmp);
				i += tmp.length() - 1;  
			}
			else if (strFunc(infix.substr(i)) != "") {
				tmp = strFunc(infix.substr(i));
				lexems.push_back(tmp);
				i += tmp.length() - 1;
			}
			else { 
				throw logic_error("assumed error in the character number n or with function, which begins with character number n; n =  " + to_string(i+1));
			}
		}
	}
	
}

string ArithmeticExpr::strNumberOrVar(string infx) {
	string tmp = "";
	int i = 0, countd=0, counte=0;
	while (infx[i] == 'x'||infx[i] == '0' || infx[i] == '1' || infx[i] == '2' || infx[i] == '3' || infx[i] == '4' || infx[i] == '5' || infx[i] == '6' || infx[i] == '7' || infx[i] == '8' || infx[i] == '9' || infx[i] == '.'|| (infx[i] == 'e'&&infx[i+1]!='x' && infx[i + 2] != 'p')) { 
		tmp += infx[i];
		if (infx[i] == 'e') {
			tmp += infx[++i];
			counte++;
		}
		if (infx[i] == '.') countd++;
		i++;	
	}
	if (counte > 1 || countd > 1) throw logic_error("assumed error in the character number "+to_string(i+1));
	return tmp;
}

string ArithmeticExpr::strFunc(string infx) {
	string tmp = "";
	int i = 0;
	if (infx[i] == 's' && infx[i + 1] == 'i' && infx[i + 2] == 'n') {
		tmp = "sin";
	}
	else if (infx[i] == 'c' && infx[i + 1] == 'o' && infx[i + 2] == 's') {
		tmp = "cos";
	}
	else if (infx[i] == 't' && infx[i + 1] == 'g') {
		tmp = "tg";
	}
	else if (infx[i] == 'c' && infx[i + 1] == 't' && infx[i + 2] == 'g') {
		tmp = "ctg";
	}
	else if (infx[i] == 'l' && infx[i + 1] == 'n') {
		tmp = "ln";
	}
	else if (infx[i] == 'e' && infx[i + 1] == 'x' && infx[i + 2] == 'p') {
		tmp = "exp";
	}
	return tmp;
}

int ArithmeticExpr::Priority(string item) {
	int i = 0;
	while (item != priorStr[i]) i++;
	return priorVal[i];
}

void ArithmeticExpr::ToPostfix() {
	Parse();
	stack<string> st;
	string stackItem;
	for (string item : lexems) {
		if (item == "(") st.push(item);
		else if (item == ")") {
			if (st.isEmpty() == true) throw logic_error("the brackets are in the wrong sequence, that is, the closing bracket does not have its own opening one");
			stackItem = st.pop();
			while (stackItem != "(") {
				pubpostfix += stackItem;
				postfix.push_back(stackItem);
				stackItem = st.pop();
			}
		}
		else if (item == "+" || item == "-" || item == "*" || item == "/"||item =="~"||item == "sin"||item == "cos" || item == "tg" || item == "ctg" || item == "exp" || item == "ln") { 
			while (!st.isEmpty()) {
				stackItem = st.pop();
				if (Priority(item) <= Priority(stackItem)) {
					pubpostfix += stackItem;
					postfix.push_back(stackItem);
				}
				else {
					st.push(stackItem);
					break;
				}
			}
			st.push(item);
		}
		
		else {
			if (item[0] == 'x') {
				operands.insert({ item,0.0 });
				pubpostfix += item;
				postfix.push_back(item);
			}
			else {
				double tmp;
				tmp = Translate(item);
				operands.insert({ item,tmp });
				pubpostfix += item;
				postfix.push_back(item);
			}
			
		}
	}
	while (!st.isEmpty()) {
		stackItem = st.pop();
		pubpostfix += stackItem;
		postfix.push_back(stackItem);
	}
}
string ArithmeticExpr::GetInfix() const { return infix; }
string ArithmeticExpr::GetPostfix() const { return pubpostfix; }
vector <string> ArithmeticExpr::GetLexems() const { return lexems; }

vector<string> ArithmeticExpr::GetOperands() const {
	vector<string> op;
	for (const auto& item : operands) {
		op.push_back(item.first);
	}
	return op;
}
double ArithmeticExpr::Calculate(const map<string, double>& value) {
	for (auto& val : value) {
		try {
			operands.at(val.first) = val.second;  
		}
		catch (out_of_range& e) {}
	}
	stack<double> st;
	double leftOp, rightOp;
	for (string lexem : postfix) {
		if (lexem == "+") {
			rightOp = st.pop();
			leftOp = st.pop();
			double res = leftOp + rightOp;
			st.push(res);
		}
		else if (lexem == "-") {
			rightOp = st.pop();
			leftOp = st.pop();
			double res = leftOp - rightOp;
			st.push(res);
		}
		else if (lexem == "~") {
			double Op = -st.pop();
			st.push(Op);
		}
		
		else if (lexem == "sin") {
			double Op = sin(st.pop());
			st.push(Op);
		}
		else if (lexem == "cos") {
			double Op = cos(st.pop());
			st.push(Op);
		}
		else if (lexem == "tg") {
			double Op = tan(st.pop());
			st.push(Op);
		}
		else if (lexem == "ctg") {
			double Op = 1/tan(st.pop());
			st.push(Op);
		}
		else if (lexem == "exp") {
			double Op = exp(st.pop());
			st.push(Op);
		}
		else if (lexem == "ln") {
			double Op = log(st.pop());
			st.push(Op);
		}
		else if (lexem == "*") {
			rightOp = st.pop();
			leftOp = st.pop();
			double res = leftOp * rightOp;
			st.push(res);
		}
		else if (lexem == "/") {
			rightOp = st.pop();
			leftOp = st.pop();
			double res = leftOp / rightOp;
			st.push(res);
		}
		else {
			st.push(operands[lexem]);
		}
	}
	return st.pop();
}

double ArithmeticExpr::Translate(string snum) {
	vector<int> fpart;
	vector<int> spart;
	vector<int> power;
	int sign = -1;
	int i = 0;
	while ((snum[i] != '.') && (i < snum.length()) && (snum[i]!='e')) {
		fpart.push_back(int(snum[i]) - 48);
		i++;
	}
	if (snum[i] == '.') {
		if (fpart.size() == 0) fpart.push_back(0);
		i++;
		while (snum[i] != 'e' && snum[i] != '\0') {
			if (snum[i] == '.') throw logic_error("assumed error in the expression " + snum);
			spart.push_back(int(snum[i]) - 48);
			i++;
		}
		if (spart.size() == 0) spart.push_back(0);
	}
	if (snum[i] == 'e') {
		i++;
		if (snum[i] == '.' || snum[i] == 'e') throw logic_error("assumed error in the expression " + snum);
		if (snum[i] == '-') sign = 1;
		else sign = 0;
		i++;
		while (i < snum.length()) {
			if (snum[i] == '.' || snum[i] == 'e') throw logic_error("assumed error in the expression " + snum);
			power.push_back(int(snum[i]) - 48);
			i++;
		}

	}

	double res = 0;
	int j = fpart.size() - 1;
	while (j >= 0) {
		res += fpart[j] * (pow(10, fpart.size() - j - 1));
		j--;
	}
	j = 0;
	while (j < spart.size()) {
		res += spart[j] * (pow(10, -j - 1));
		j++;
	}
	j = power.size() - 1;
	int e = 0;
	while (j >= 0) {
		e += power[j] * (pow(10, power.size() - j - 1));
		j--;
	}
	if (sign == 1) {
		res /= pow(10, e);
	}
	else if (sign == 0) {
		res *= pow(10, e);
	}
	return res;
}
