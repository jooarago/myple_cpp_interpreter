#include "error_handling.h"
#include <iostream>
#include <string>

using namespace std;

bool hadError = false;

void report(int line, string where, string message){
    cout << "[line " << line << "] Error" << where << ": " << message;
    hadError = true; 
}

void error(int line, string message){
    report(line, "", message);
}