# VRIKSH language and compiler:

### Syntax:
COMMAND arg1 arg2 ... argN

### Commands:

**DECLARE** : Declares a variable with the given name and initializes it with the given value. If the variable already exists, it updates the value.

Syntax:

DECLARE A *Sets it null*

DECLARE A AS 0 *Sets it 0*

**C_INPUT** : Takes input from the user and stores it in the variable with the given name.

Syntax:

C_INPUT A *Prompts the user to enter a value and stores it in A*

**C_OUTPUT** : Prints the value of the variable with the given name or a text literal to the console(no double quotes or single quotes).

Syntax:

C_OUTPUT A *Prints the value of A to the console*

**ADD**, **SUB**, **MUL**, **DIV** : Performs an arithmetic operation on two input values and stores the result in a new variable, or updates the value of an existing variable.

Syntax:

ADD A B C *Sets C to A + B*

SUB A B D *Sets D to A - B*

MUL A B E *Sets E to A * B*

DIV A B F *Sets F to A / B*

**COMMENT** : These lines are ignored by the parser.

Syntax:

COMMENT This is a comment

---

# Installation:

Get the code from the following link: https://github.com/Beta-Verse-Hub/Vrikhsh/releases/latest

---

# Running the code:

Open a cmd window and run the following command to run the example code:

`main.exe "ExampleCode.vri"`

The example code takes two inumbrs input from te user and then add, subtract, multiply and divide them and finally output the results.
