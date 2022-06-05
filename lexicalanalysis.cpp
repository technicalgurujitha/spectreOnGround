#include <bits/stdc++.h>
using namespace std;

bool isOperator(char c){
    switch (c){
        case '*' : return true;
        case '-' : return true;
        case '+' : return true;
        case '/' : return true;
        case '>' : return true;
        case '<' : return true;
        case '=' : return true;
        case '!' : return true;
        default : return false;
    }
}

bool isDelimiter(char c){
    switch (c){
        case ' ' : return true;
        case ',' : return true;
        case ';' : return true;
        case '(' : return true;
        case ')' : return true;
        case '[' : return true;
        case ']' : return true;
        case '{' : return true;
        case '}' : return true;
        default : return isOperator(c);
    }
}


bool isKeyword(const string& token){
    vector<string> keywords = {"auto", "break", "case", "char", "const",
        "continue", "default", "do", "double", "else", "enum", "extern", 
        "float", "for", "goto", "if", "inline", "int", "long", "register", 
        "restrict", "return", "short", "signed", "sizeof", "static", 
        "struct", "switch", "typedef", "union", "unsigned", "void", 
        "volatile", "while"};

    for (string i : keywords){
        if (!token.compare(i)){
            return true;
        }
    }
    return false;
}

bool isValidId(const string& token){
    if (!isalpha(token[0]))
        return false;
    for (int i = 1; i < token.size(); ++i){
        if (!isalnum(token[0]) && token[0] != '_'){
            return false;
        }
    }
    return true;
}


bool isNum(const string& token){
    if (isdigit(token[0]) || token[0] == '-' || token[0] == '+'){
    }
    else{
        return false;
    }
    bool dot = false;
    for (int i = 0; i < token.size(); ++i){
        if (token[i] == '.'){
            if (dot)
                return false;
            if (!dot)
                dot = true;
        }
        else{
            if (!isdigit(token[i])){
                return false;
            }
        }
    }
    return true;
}

void tokenize(const string& line){
    int left, right;
    left = right = 0;
    
    while (right < line.size() && left <= right){
        if (!isDelimiter(line[right]))
            right++;

        if (isDelimiter(line[right]) && left == right){
            if (isOperator(line[right])){
                cout << line[right] << " is an OPERATOR" << endl;
            }
            right++;
            left = right;
        }
        else if ((isDelimiter(line[right]) || (right == line.size() - 1))
            && left != right){
                
                string token = line.substr(left, right - left);

                if (isKeyword(token)){
                    cout << token << " is a KEYWORD" << endl;
                }
                else if (isNum(token)){
                    cout << token << " is a NUMBER" << endl;
                }
                else if (isValidId(token)){
                    cout << token << " is a valid IDENTIFIER" << endl;
                }
                else{
                    cout << token << " is a NOT a valid IDENTIFIER" << endl;
                }
                left = right;
            }
    }
}



int main(){
    ifstream fin;
    fin.open("prog.c");
    string line;

    while (fin){
        getline(fin, line);
        if (line.size()){
            tokenize(line);
        }
        fin.peek();
    }
    return 0;
}
