#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;
using vs = vector<string>;
using vvs = vector<vector<string>>;

vector<string> variableNames = {};
vector<string> variableValues = {};

/**
 * @brief Reads input from the user for each variable name provided in args
 *        and stores the input values in the variableValues vector.
 *
 * @param[in] args The list of variable names for which input is requested.
 *
 * @return 0 always.
 */
int C_INPUT(vs args){
    for(int i = 0; i < args.size(); i++){
        variableNames.push_back(args.at(i));
        variableValues.push_back("");

        string input;
        cin >> input;
        
        variableValues.at(variableNames.size()-1) = input;
    }
    return 0;
}


/**
 * @brief Output the given arguments as a line of text, with each argument
 *        separated by a space, and with a newline at the end.
 *
 * @param[in] args The list of arguments to output.
 *
 * @return 0 always.
 */
int C_OUTPUT(vs args){
    for(int i = 0; i < args.size(); i++){
        cout << args.at(i);
    }
    cout << endl;
    return 0;
}


int interpretCode(vvs Program){

    for(int lineNumber = 0; lineNumber < Program.size(); lineNumber++){
        string command;
        vs args;

        cout << '8';

        if (!Program.at(lineNumber).empty()) { // Check if the line has any words
            command = Program.at(lineNumber).at(0); // Get the first string (word) in the inner vector
        }else {
            // Handle empty lines if necessary (e.g., skip or error)
            std::cerr << "Warning: Line " << lineNumber << " is empty or has no command." << std::endl;
            continue; // Skip to the next line
        }

        cout << '9';

        if (1 < Program.at(lineNumber).size()) { // Check if the line has any words
            copy(Program.at(lineNumber).begin() + 1, Program.at(lineNumber).end(), args.begin());
        }

        if(command == "C_OUTPUT"){
            C_OUTPUT(args);
        }else{
            cout << command;
        }
    };

    return 0;
}


int readCode(){
    int status = 0;

    ifstream inputProgramFile("MyProgram.vri");

    string line;
    vvs inputProgram;
    
    while (getline(inputProgramFile, line)) {
        vs words;
        istringstream iss(line);
        string word;
        while (iss >> word) {
            words.push_back(word);
        };
        inputProgram.push_back(words);
    };

    interpretCode(inputProgram);

    return status;
}


int main(){
    return readCode();
}