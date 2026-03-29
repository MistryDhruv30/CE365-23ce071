#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOperator(string s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

bool isNumber(string s) {
    for (char c : s) {
        if (!isdigit(c) && c != '.') return false;
    }
    return true;
}

string applyOp(string a, string b, string op) {
    if (isNumber(a) && isNumber(b)) {
        double x = stod(a), y = stod(b), res;
        if (op == "+") res = x + y;
        else if (op == "-") res = x - y;
        else if (op == "*") res = x * y;
        else res = x / y;

        if (res == (int)res) return to_string((int)res);
        return to_string(res);
    }
    return a + " " + op + " " + b;
}

vector<string> tokenize(string expr) {
    vector<string> tokens;
    for (int i = 0; i < expr.size(); i++) {
        if (expr[i] == ' ') continue;

        if (isdigit(expr[i])) {
            string num = "";
            while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.')) {
                num += expr[i];
                i++;
            }
            i--;
            tokens.push_back(num);
        }
        else if (isalpha(expr[i])) {
            string var = "";
            while (i < expr.size() && isalpha(expr[i])) {
                var += expr[i];
                i++;
            }
            i--;
            tokens.push_back(var);
        }
        else {
            tokens.push_back(string(1, expr[i]));
        }
    }
    return tokens;
}

string constantFold(string expr) {
    vector<string> tokens = tokenize(expr);
    stack<string> values;
    stack<string> ops;

    for (int i = 0; i < tokens.size(); i++) {

        if (tokens[i] == "(") {
            ops.push(tokens[i]);
        }

        else if (tokens[i] == ")") {
            while (!ops.empty() && ops.top() != "(") {
                string b = values.top(); values.pop();
                string a = values.top(); values.pop();
                string op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            ops.pop();
        }

        else if (!isOperator(tokens[i])) {
            values.push(tokens[i]);
        }

        else {
            while (!ops.empty() && ops.top() != "(" &&
                   precedence(ops.top()[0]) >= precedence(tokens[i][0])) {

                string b = values.top(); values.pop();
                string a = values.top(); values.pop();
                string op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            ops.push(tokens[i]);
        }
    }

    while (!ops.empty()) {
        string b = values.top(); values.pop();
        string a = values.top(); values.pop();
        string op = ops.top(); ops.pop();
        values.push(applyOp(a, b, op));
    }

    return values.top();
}

int main() {
    while (true) {
        string expr;
        cout << "Enter Expression: ";
        getline(cin, expr);

        if (expr == "") break;

        cout << constantFold(expr) << endl << endl;
    }
    return 0;
}