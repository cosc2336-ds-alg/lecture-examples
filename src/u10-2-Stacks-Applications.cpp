/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   January 18, 2019
 * @assg   C++ Stacks Application video
 *
 * @description Introduction to Stacks.  Applications of stacks.
 */
#include "Stack.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/** reverse list
 * Display a given linked list in reverse order.  A simple example
 * of recursion to reverse access to list elements.  We implicitly
 * are using the function call stack when we use recursion, so in
 * actual fact, all examples of recursion we have used in this class
 * were really examples of using a stack to perform calculations.
 *
 * @param node A pointer to a node of the list we are reverse
 *   displaying.
 */
void displayReverseList(Node<string>* nodePtr)
{
  // base case, we are done if we reach NULL at the end of the
  // linked list/recursion process
  if (nodePtr == NULL)
  {
    return;
  }
  else // general case
  {
    // first recursively display our linked item,
    displayReverseList(nodePtr->link);

    // before we display ourself
    cout << "displayReverseList item: " << nodePtr->item << endl;
  }
}

/** split string on delimeters
 * A simple splitter or tokenizer.  Splits given string on the
 * provided delimeters.
 *
 * Stack Overflow:
 *  https://stackoverflow.com/questions/7621727/split-a-string-into-words-by-multiple-delimiters
 *
 * @param line The line to be split/tokenized
 * @param delimeters The delimeters to split/tokenize line on
 *
 * @returns vector<string>& Returns a vector of the tokenized
 *   strings found in the input line.
 */
vector<string> split(const string& line, const string& delimeters)
{
  vector<string> tokens;
  size_t prev = 0;
  size_t pos;

  // we find next instance of a delimiter from the previous instance,
  // and push the substring between these two positions onto
  // our vector of resulting tokens
  while ((pos = line.find_first_of(delimeters, prev)) != string::npos)
  {
    if (pos > prev)
    {
      // cout << "prev=" << prev << " pos=" << pos << " substr <"
      //   << line.substr(prev, pos-prev) << ">" << endl;
      tokens.push_back(line.substr(prev, pos - prev));
    }
    prev = pos + 1;
  }

  // if no trailing delimiter on line, need to push the last
  // bit of string on as the final token before returning
  if (prev < line.length())
  {
    tokens.push_back(line.substr(prev, string::npos));
  }

  return tokens;
}

/** evaluate postfix expression
 * Example of a function using a stack for a calculation.  Given
 * a line (string) of postfix notation, tokenize the line and
 * interpret it by executing the operators on the operands in the
 * indicated order.
 *
 * @param line A valid string of operands and operators in postfix
 *  notation order.
 *
 * @returns double Returns the resulting value of the calculation.
 */
double evaluatePostfixExpression(const string& line)
{
  LStack<double> postfixStack;
  vector<string> tokens;
  double result;

  // tokenize the line.  This simply splits up the line into a list (vector)
  // of the individual tokens
  tokens = split(line, " \t");

  // iterate through each token
  for (auto& token : tokens)
  {
    // cout << "Found token: " << token << endl;

    // token will be either an operator or an operand
    // if token is an operaotr, use stack to calculate the
    // indicated operation
    if ((token == "+") || (token == "-") || (token == "*") || (token == "/"))
    {
      double op1;
      double op2;

      // if stack is empty before either of these pop()/top() then
      // expression is malformed,
      try
      {
        op2 = postfixStack.top();
        postfixStack.pop();
        op1 = postfixStack.top();
        postfixStack.pop();
      }
      catch (EmptyStackException emptyStackObj)
      {
        cout << "    Error: postfix expression was malformed" << endl;
        return 0; // return immediatly, can't process expression any further
      }

      switch (token[0])
      {
      case '+':
        postfixStack.push(op1 + op2);
        break;
      case '-':
        postfixStack.push(op1 - op2);
        break;
      case '*':
        postfixStack.push(op1 * op2);
        break;
      case '/':
        postfixStack.push(op1 / op2);
        break;
      default:
        cout << "   Error: unknown operator: " << token << endl;
        return 0;
      }
    }
    // otherwise we assume everything else is an operand,
    // in this case a number that we can convert to a double
    // and push on the stack awaiting to be operated on
    else
    {
      // stod() tries to convert string to double
      postfixStack.push(stod(token));
    }
  }

  // return the result
  result = postfixStack.top();
  postfixStack.pop();
  if (!postfixStack.isEmpty())
  {
    cout << "   Error: postfix expression was malformed" << endl;
  }
  return result;
}

/** main
 * The main entry point for this program.  Execution of this program
 * will begin with this main function.
 *
 * @param argc The command line argument count which is the number of
 *     command line arguments provided by user when they started
 *     the program.
 * @param argv The command line arguments, an array of character
 *     arrays.
 *
 * @returns An int value indicating program exit status.  Usually 0
 *     is returned to indicate normal exit and a non-zero value
 *     is returned to indicate an error condition.
 */
int main(int argc, char** argv)
{
  //-----------------------------------------------------------------------
  // In general, stacks can be used to reverse a list of items
  // Recursive implementations of reverse like this actually
  // implicitly use a function call stack.

  // build a linked list by hand using Node from Stack.hpp
  Node<string>* first = new Node<string>;
  first->item = "I am first!";

  Node<string>* second = new Node<string>;
  second->item = "I am second?";

  Node<string>* third = new Node<string>;
  third->item = "Third is the bird";

  Node<string>* fourth = new Node<string>;
  fourth->item = "George the 4th";

  first->link = second;
  second->link = third;
  third->link = fourth;
  fourth->link = NULL;

  // first, a recursive function example, from chapter 15
  displayReverseList(first);
  cout << endl << endl;

  // So if we iterate through a list, pushing items on a stack as we go
  AStack<string> reverseStack;

  Node<string>* nodeItr = first;
  int itemNum = 1;
  while (nodeItr != NULL)
  {
    reverseStack.push(nodeItr->item);
    cout << "List item " << itemNum << ": " << nodeItr->item << endl;
    nodeItr = nodeItr->link;
    itemNum++;
  }
  cout << endl << endl;

  // Then if we pop off the items, they will be in reverse
  itemNum = 1;
  while (!reverseStack.isEmpty())
  {
    cout << "Reverse list item " << itemNum << ": " << reverseStack.top() << endl;
    reverseStack.pop();
    itemNum++;
  }
  cout << endl << endl;

  //-----------------------------------------------------------------------
  // postfix calculator.  This is an example of a parser/interpreter that tokenizes
  // the line of input executes the operations on the operands.  We
  // use a stack in evaluating the expressions
  string line = "";
  double result;

  // loop forever getting lines from user to parse/interpret
  while (true)
  {
    // get a line of postfix to parse/interpret
    cout << "Enter a postfix expression, or 'done' to quit: ";
    getline(cin, line);
    if (line == "done")
    {
      break;
    }

    // interpret the line using a stack (see evaluatePostfixExpression function)
    cout << "Parsing/Interpreting line: <" << line << ">" << endl;
    result = evaluatePostfixExpression(line);
    cout << "    Result: " << result << endl;
  }

  return 0;
}
