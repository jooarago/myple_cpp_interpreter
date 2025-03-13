#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool hadError = false;

using namespace std;

void run(string source){
    cout << source << endl; // for now.
}

void report(int line, string where, string message){
    cout << "[line " << line << "] Error" << where << ": " << message;
    hadError = true; 
}

void error(int line, string message){
    report(line, "", message);
}

void runFile(const string path){
    ifstream file(path);
    if(!file.is_open()){
        cerr << "File not opened : " << path << endl;
        exit(74);
    }
    stringstream buffer;
    buffer << file.rdbuf();
    run(buffer.str());
    if (hadError) exit(65);
}

void runPrompt(){
    while(1){
        printf("> ");
        string line;
        getline(cin, line);
        if (cin.eof()) break;
        run(line);
        hadError = false;
    }
}

int main(int argc, char* argv[]){
    if(argc > 2){
        printf("Usage: myple [script]");
        exit(64);
    }else if(argc == 2){
        runFile(argv[1]);
    }else{
        runPrompt();
    }
}