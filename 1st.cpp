#include <bits/stdc++.h>
using namespace std;


string findFirst(map<char, vector<string>> m, char ch);
string firstString(map<char, vector<string>> m, string s);


int main() {
    map <char, vector<string>> prod;
    int n;
    cout << "Enter number of productions:\t";
    cin >> n;
    char start;
    for (int i = 0; i < n; ++i){
        string s;
        cout << "Enter production " << i + 1 << ":\t";
        cin >> s;
        char ch = s[0];
        if (i == 0) start = ch;
        string body = s.substr(3);
        prod[ch].push_back(body);
    }
    cout << "First of the given grammar: " << endl;

    for (auto i = prod.begin(); i != prod.end(); ++i){
        cout << "First(" << i->first << ") = {";
        string s = findFirst(prod, i->first);
        for (int j = 0; j < s.length(); ++j){
            if (j != s.length() - 1){
                cout << s[j] << " , ";
            }
            else{
                cout << s[j] << "}";
            }
        }
        cout << endl;
    }
    return 0;
}


string findFirst(map<char, vector<string>> m, char ch){

    // if ch is epsilon or term, return ch
    if (ch == '^' || !(ch >= 'A' && ch <= 'Z')) return ch + "";

    string ans = "";

    for (int i = 0;  i < m[ch].size(); ++i){

        string s = m[ch][i];
        bool ifnext = true;

        for (int j = 0; j < s.length() && ifnext; ++j){

            ifnext = false;

            // s[j] is eps or term
            if (s[j] == '^' || !(s[j] >= 'A' && s[j] <= 'Z')){
                // checks if s[j] is in ans, if not then inserts it
                if (ans.find(s[j]) == string::npos){
                    ans.push_back(s[j]);
                }
            }
            // s[j] is var
            else{
                string tmp = findFirst(m, s[j]);

                for (int k = 0; k < tmp.length(); ++k){
                    if (tmp[k] == '^'){
                        ifnext = true;
                    }
                    else if (ans.find(tmp[k]) == string::npos){
                        ans.push_back(tmp[k]);
                    }
                }
                // j reaches value s.len - 1 only when all prev ones are vars
                // and first of all contain eps
                if (ifnext && j == s.length() - 1){
                    //should check if ans already contains eps, may come from other prods
                    ans.push_back('^');
                }
            }
        }
    }
    return ans;
}

string firstString(map<char, vector<string>> m, string s){

    string ans = "";
    bool ifnext = true;

    for (int j = 0; j < s.length() && ifnext; ++j){
        
        ifnext = false;

        if (s[j] == '^' || !(s[j] >= 'A' && s[j] <= 'Z')){
            if (ans.find(s[j]) == string::npos){
                ans.push_back(s[j]);
            }
        }
        
        else{
            string tmp = findFirst(m, s[j]);
            
            for (int k = 0; k < tmp.length(); ++k){
                if (tmp[k] == '^'){
                    ifnext = true;
                }
                else if (ans.find(tmp[k]) == string::npos){
                    ans.push_back(tmp[k]);
                }
            }
            
            if (ifnext && j == s.length() - 1){
                ans.push_back('^');
            }
        }
    }
    
    if (ans == ""){
        return "^";
    }
    
    return ans;
}

