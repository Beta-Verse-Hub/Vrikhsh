#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using vs = vector<string>;

int C_OUTPUT(){
    
    return 0;
}

int readCode(){
    int status = 0;

    ifstream inputProgramFile("MyProgram.vri");

    string line;
    vs inputProgram;
    
    while (getline(inputProgramFile, line)) {
        inputProgram.push_back(line);
    };

    for(int lineNumber = 0; lineNumber < inputProgram.size(); lineNumber++){
        cout << inputProgram.at(lineNumber) << endl;
    }

    return status;
}

int main(){
    return readCode();
}