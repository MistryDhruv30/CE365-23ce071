#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Quad {
    string op, arg1, arg2, result;
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

vector<Quad> generateQuadruple(string expr) {
    stack<string> operands;
    stack<char> operators;
    vector<Quad> quads;
    int tempCount = 1;

    for (int i = 0; i < expr.length(); i++) {

        if (expr[i] == ' ') continue;

        if (isdigit(expr[i])) {
            string num = "";
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                num += expr[i];
                i++;
            }
            i--;
            operands.push(num);
        }

        else if (expr[i] == '(') {
            operators.push(expr[i]);
        }

        else if (expr[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                string op2 = operands.top(); operands.pop();
                string op1 = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();

                string temp = "t" + to_string(tempCount++);
                quads.push_back({string(1, op), op1, op2, temp});
                operands.push(temp);
            }
            operators.pop();
        }

        else {
            while (!operators.empty() &&
                   precedence(operators.top()) >= precedence(expr[i])) {

                string op2 = operands.top(); operands.pop();
                string op1 = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();

                string temp = "t" + to_string(tempCount++);
                quads.push_back({string(1, op), op1, op2, temp});
                operands.push(temp);
            }
            operators.push(expr[i]);
        }
    }

    while (!operators.empty()) {
        string op2 = operands.top(); operands.pop();
        string op1 = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();

        string temp = "t" + to_string(tempCount++);
        quads.push_back({string(1, op), op1, op2, temp});
        operands.push(temp);
    }

    return quads;
}

int main() {
    while (true) {
        string expr;
        cout << "Enter Expression: ";
        getline(cin, expr);

        if (expr == "") break;

        vector<Quad> result = generateQuadruple(expr);

        cout << "Operator\tOperand1\tOperand2\tResult\n";

        for (auto q : result) {
            cout << q.op << "\t\t"
                 << q.arg1 << "\t\t"
                 << q.arg2 << "\t\t"
                 << q.result << endl;
        }

        cout << endl;
    }

    return 0;
}