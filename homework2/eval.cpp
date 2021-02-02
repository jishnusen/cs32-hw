#include <cassert>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isOperand(char c) {
  char ba[10] = {
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
      //  true,  true,  true,  false, false, false, true,  false, true,  false
  };
  for (int i = 0; i < 10; i++) {
    if (c == ba[i]) {
      return true;
    }
  }
  return false;
}

bool operandNext(string infix, int i) {
  for (i = i + 1; i < infix.size(); i++) {
    if (isOperand(infix[i]) || infix[i] == '!') {
      return true;
    } else if (!isspace(infix[i]) && infix[i] != '(') {
      return false;
    }
  }
  return false;
}

char operandBefore(string infix, int i) {
  for (; i >= 0; i--) {
    if (isOperand(infix[i])) {
      return true;
    } else if (!isspace(infix[i])) {
      return false;
    }
  }
  return false;
}

void dumpStack(stack<bool> s) {
  while (!s.empty()) {
    cout << s.top() << endl;
    s.pop();
  }
}

int precedence(char c) {
  switch (c) {
    case '&':
      return 2;
    case '|':
      return 1;
  }
  return 3;
}

int evaluate(string infix, const bool values[], string& postfix, bool& result) {
  postfix = "";             // Resulting postfix operation string
  stack<char> postfix_ops;  // Postfix operators
  for (int i = 0; i < infix.size(); i++) {
    switch (infix[i]) {
      case '(':
        if (operandNext(infix, i)) {
          postfix_ops.push(infix[i]);
          break;
        }
        // cerr << "no operand after (" << endl;
        return 1;
      case '!':
        postfix_ops.push(infix[i]);
        break;
      case ')':
        if (operandBefore(infix, i)) {
          // cerr << "empty parenthesis" << endl;
          return 1;
        }
        while (postfix_ops.top() != '(') {
          postfix += postfix_ops.top();
          postfix_ops.pop();
        }
        postfix_ops.pop();
        break;

      case '&':
      case '|':
        while (!postfix_ops.empty() && postfix_ops.top() != '(' &&
               precedence(infix[i]) <= precedence(postfix_ops.top())) {
          postfix += postfix_ops.top();
          postfix_ops.pop();
        }
        postfix_ops.push(infix[i]);
        break;
      default:
        if (isOperand(infix[i])) {
          postfix += infix[i];
          if (postfix_ops.size() > 0) {
            if (postfix_ops.top() == '!') {
              postfix += postfix_ops.top();
              postfix_ops.pop();
            }
          }
        } else if (!isspace(infix[i])) {
          return 1;
        }
        break;
    }
  }
  while (!postfix_ops.empty()) {
    postfix += postfix_ops.top();
    postfix_ops.pop();
  }

  stack<bool> operand_stack;
  for (int i = 0; i < postfix.size(); i++) {
    if (isOperand(postfix[i])) {
      operand_stack.push(values[postfix[i] - '0']);
    } else if (postfix[i] == '!') {
      operand_stack.top() = !operand_stack.top();
    } else {
      if (operand_stack.size() < 2) {
        // cerr << "not enough operands" << endl;
        return 1;
      }
      bool operand2 = operand_stack.top();
      operand_stack.pop();
      bool operand1 = operand_stack.top();
      operand_stack.pop();
      switch (postfix[i]) {
        case '&':
          operand_stack.push(operand1 & operand2);
          break;
        case '|':
          operand_stack.push(operand1 | operand2);
          break;
      }
    }
  }

  if (operand_stack.size() != 1) {
    // cerr << "missing operator" << endl;
    return 1;
  }

  result = operand_stack.top();

  return 0;
}

int main() {
  bool ba[10] = {
      //  0      1      2      3      4      5      6      7      8      9
      true, true, true, false, false, false, true, false, true, false};
  string pf;
  bool answer;
  assert(evaluate("2| 3", ba, pf, answer) == 0 && pf == "23|" && answer);
  assert(evaluate("8|", ba, pf, answer) == 1);
  assert(evaluate(" &6", ba, pf, answer) == 1);
  assert(evaluate("4 5", ba, pf, answer) == 1);
  assert(evaluate("01", ba, pf, answer) == 1);
  assert(evaluate("()", ba, pf, answer) == 1);
  assert(evaluate("()4", ba, pf, answer) == 1);
  assert(evaluate("2(9|8)", ba, pf, answer) == 1);
  assert(evaluate("2(&8)", ba, pf, answer) == 1);
  assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
  assert(evaluate("x+5", ba, pf, answer) == 1);
  assert(evaluate("", ba, pf, answer) == 1);
  assert(evaluate("2|3|4", ba, pf, answer) == 0 && pf == "23|4|" && answer);
  assert(evaluate("2|(3|4)", ba, pf, answer) == 0 && pf == "234||" && answer);
  assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0 &&
         pf == "43!03&&|" && !answer);
  assert(evaluate(" 9  ", ba, pf, answer) == 0 && pf == "9" && !answer);
  ba[2] = false;
  ba[9] = true;
  assert(evaluate("((9))", ba, pf, answer) == 0 && pf == "9" && answer);
  assert(evaluate("2| 3", ba, pf, answer) == 0 && pf == "23|" && !answer);
  cout << "Passed all tests" << endl;
}