#include <iostream>
#include <string>

using namespace std;

extern bool hadError;
void report(int line, string where, string message);
void error(int line, string message);