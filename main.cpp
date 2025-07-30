#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;
using vs = vector<string>;
using vvs = vector<vector<string>>;

vs variableNames = {};
vs variableValues = {};

/**
 * @brief Checks if the given variable name exists in the list of declared 
 *        variables and returns its index.
 *
 * @param[in] var_name The name of the variable to check.
 *
 * @return The index of the variable if it exists, otherwise -1.
 */
int is_a_variable(string var_name){
    auto it = find(variableNames.begin(), variableNames.end(), var_name);
    return (it != variableNames.end()) ? distance(variableNames.begin(), it) : -1;
}

/**
 * @brief Declare a variable and initialize it with a value if specified.
 *
 * @param[in] args A vector of strings with the following structure:
 *                  - The first element is the variable name to declare.
 *                  - The second element is "AS" if a value is specified.
 *                  - The third element is the value to assign to the variable.
 *
 * @return 0 always.
 */
int DECLARE(vs args){

    auto it = find(variableNames.begin(), variableNames.end(), args.at(0));
    if (variableNames.end() != it) {

        if (args.size() <= 1) {
            return 0;
        }

        if (args.size() >= 3 && args.at(1) == "AS") {
            int index = distance(variableNames.begin(), it);    

            variableValues.at(index) = args.at(2);
            return 0;
        }else {
            variableValues.push_back("null");
            return 0;
        }
    }

    variableNames.push_back(args.at(0));

    if (args.size() == 1) {
        variableValues.push_back("null");
        return 0;
    };

    if (args.at(1) == "AS") {
        int index = distance(variableNames.begin(), it);
        variableValues.at(index) = args.at(2);
        return 0;
    };
}

/**
 * @brief Reads input from the user for each variable name provided in args
 *        and stores the input values in the variableValues vector.
 *
 * @param[in] args The list of variable names for which input is requested.
 *
 * @return 0 always.
 */
int C_INPUT(vs args){
    for(const string& var_name : args){
        int index = is_a_variable(var_name);
        
        if (index == -1) { // If variable not declared, declare it first
            variableNames.push_back(var_name);
            variableValues.push_back(""); // Initialize with empty string
            index = variableNames.size() - 1;
        }

        string input;
        cin >> input;

        variableValues.at(index) = input;
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
        int variableIndex = is_a_variable(args.at(i));
        
        if(variableIndex < 0){
            cout << args.at(i);
        }else{
            cout << variableValues.at(variableIndex);
        }
    }
    cout << endl;
    return 0;
}


/**
 * @brief Adds two values together and stores the result in a variable.
 *
 * @param[in] args A vector of strings with the following structure:
 *                  - The first element is the first value to add.
 *                  - The second element is the second value to add.
 *                  - The third element is the variable name in which to store the result.
 *
 * @return 0 always.
 */
int ADD(vs args){

    int val1 = is_a_variable(args.at(0));
    int val2 = is_a_variable(args.at(1));
    int newvar = is_a_variable(args.at(2));

    if(val1 == -1){
        val1 = stoi(args.at(0));
    }else{
        val1 = stoi(variableValues.at(val1));
    }

    if(val2 == -1){
        val2 = stoi(args.at(1));
    }else{
        val2 = stoi(variableValues.at(val2));
    }

    if (newvar == -1){
        variableNames.push_back(args.at(2));
        variableValues.push_back(to_string(val1 + val2));
        return 0;
    }else{
        variableValues.at(newvar) = to_string(val1 + val2);
        return 0;
    }
}


/**
 * @brief Subtracts the second value from the first and stores the result in a variable.
 *
 * @param[in] args A vector of strings with the following structure:
 *                  - The first element is the first value.
 *                  - The second element is the second value to subtract from the first.
 *                  - The third element is the variable name in which to store the result.
 *
 * @return 0 always.
 */
int SUB(vs args){

    int val1 = is_a_variable(args.at(0));
    int val2 = is_a_variable(args.at(1));
    int newvar = is_a_variable(args.at(2));

    if(val1 == -1){
        val1 = stoi(args.at(0));
    }else{
        val1 = stoi(variableValues.at(val1));
    }

    if(val2 == -1){
        val2 = stoi(args.at(1));
    }else{
        val2 = stoi(variableValues.at(val2));
    }

    if (newvar == -1){
        variableNames.push_back(args.at(2));
        variableValues.push_back(to_string(val1 - val2));
        return 0;
    }else{
        variableValues.at(newvar) = to_string(val1 - val2);
        return 0;
    }
}


/**
 * @brief Executes the given program by interpreting the commands and arguments
 *        in each line, and executing the corresponding functions.
 *
 * @param[in] Program The program to execute, given as a vector of vectors of
 *                    strings, where each inner vector represents a line of code.
 *
 * @return 0 always.
 */
int interpretCode(vvs Program){

    for(int lineNumber = 0; lineNumber < Program.size(); lineNumber++){
        string command;
        vs args;

        if (!Program.at(lineNumber).empty()) { // Check if the line has any words
            command = Program.at(lineNumber).at(0); // Get the first string (word) in the inner vector
            args = Program.at(lineNumber); // Get the rest of the words in the inner vector
            args.erase(args.begin()); // Remove the command from the args vector
       }else {
            // Handle empty lines if necessary (e.g., skip or error)
            std::cerr << "Warning: Line " << lineNumber << " is empty or has no command." << std::endl;
            continue; // Skip to the next line
        }

        if (1 > Program.at(lineNumber).size()) { // Check if the line has any words
            continue;
        }

        if(command == "C_OUTPUT"){
            C_OUTPUT(args);
        }else if(command == "C_INPUT"){
            C_INPUT(args);
        }else if(command == "DECLARE"){
            DECLARE(args);
        }else if(command == "ADD"){
            DECLARE(args);
        }else if(command == "SUB"){
            DECLARE(args);
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