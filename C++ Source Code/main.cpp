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
 * @brief Checks if a given variable name is present in the variableNames vector.
 *
 * @param[in] var_name The name of the variable to check.
 *
 * @return The index of the variable in the variableNames vector if found,
 *         -1 otherwise.
 */
int is_a_variable(string var_name){
    auto it = find(variableNames.begin(), variableNames.end(), var_name);
    return (it != variableNames.end()) ? distance(variableNames.begin(), it) : -1;
}

/**
 * @brief Declares a variable with the given name and initializes it with the
 *        given value. If the variable already exists, it updates the value.
 *
 * @param[in] args A vector of strings with the following structure:
 *                  - The first element is the name of the variable to declare.
 *                  - If the second element is "AS", the third element is the
 *                    value to initialize the variable with.
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

    return 0;
}

/**
 * @brief Reads user input for each variable in the given list of argument
 *        names, and stores the input in the corresponding variable.
 *
 * @param[in] args A vector of strings, where each string is the name of a
 *                 variable for which user input should be read. If a variable
 *                 is not declared, it is declared first.
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
 * @brief Outputs the values of the given arguments to the console.
 *
 * @param[in] args A vector of strings, where each string is either a variable
 *                 name or a literal value to output.
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
 * @brief Performs an arithmetic operation on two input values and stores
 *        the result in a new variable, or updates the value of an existing
 *        variable.
 *
 * @param[in] args A vector of strings, where the first two strings are variable
 *                 names or literal values, and the third string is the name
 *                 of the variable to store the result.
 * @param[in] operation The arithmetic operation to perform, one of "ADD",
 *                      "SUB", "MUL", or "DIV".
 *
 * @return 0 always.
 */
int ASMD_OPERATIONS(vs args, string operation){

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

    int newval;
    if(operation == "ADD"){
        newval = val1 + val2;
    }else if(operation == "SUB"){
        newval = val1 - val2;
    }else if(operation == "MUL"){
        newval = val1 * val2;
    }else if(operation == "DIV"){
        newval = val1 / val2;
    }

    if (newvar == -1){
        variableNames.push_back(args.at(2));
        variableValues.push_back(to_string(newval));
        return 0;
    }else{
        variableValues.at(newvar) = to_string(newval);
        return 0;
    }
}

/**
 * @brief Interprets the given program, a vector of strings where each string
 *        is a line of code, and executes each line of code.
 *
 * @param[in] Program A vector of vectors of strings, where each inner vector
 *                    contains the words of a line of code. The first word is
 *                    the command, and the rest of the words are arguments to
 *                    the command.
 *
 * @throws None
 */
void interpretCode(vvs Program){

    for(int lineNumber = 0; lineNumber < Program.size(); lineNumber++){
        string command;
        vs args;

        if (!Program.at(lineNumber).empty()) { // Check if the line has any words
            command = Program.at(lineNumber).at(0); // Get the first string (word) in the inner vector
            args = Program.at(lineNumber); // Get the rest of the words in the inner vector
            args.erase(args.begin()); // Remove the command from the args vector
       }else {
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
        }else if(command == "ADD" || command == "SUB" || command == "MUL" || command == "DIV"){
            ASMD_OPERATIONS(args, command);
        }else if(command == "COMMENT"){
            // Do nothing
        }else{
            std::cerr << "Error: Unknown command: " << command << std::endl;
        }
    };
}

/**
 * @brief Reads the program from the given script path and interprets it.
 *
 * @param scriptPath The path to the script file containing the program.
 *
 * @throws None
 */
void readCode(string scriptPath){

    ifstream inputProgramFile(scriptPath);

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
}


/**
 * @brief The main function of the program.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 *
 * @return 0 if the program executed successfully. 1 if an error occurred.
 *
 * This function checks if exactly one command line argument is provided,
 * which is the path to a script file. It then reads the script file and
 * interprets the program contained within it.
 */
int main(int argc, char* argv[]){
    if (argc != 2) {
        cerr << "Error: Please provide a script file as an argument." << endl;
        return 1;
    }

    string scriptPath = argv[1];
    readCode(scriptPath);

    return 0;
}