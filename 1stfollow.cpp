#include <bits/stdc++.h>
using namespace std;


string findFirst(map<char, vector<string>> m, char ch);
string firstString(map<char, vector<string>> m, string s);
string findFollow(map<char, vector<string>> prod, char start, char ch);


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
    cout << "First of the given grammar: " << endl << endl;

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

    cout << endl << "Follow of the given grammer is: " << endl << endl;
    for (auto i = prod.begin(); i != prod.end(); ++i){
        cout << "Follow(" << i->first << ") = {";
        string s = findFollow(prod, start, i->first);
        for (int j = 0; j < s.length(); ++j){
            if (j != s.length() - 1){
                cout << s[j] << " , ";
            }
            else{
                cout << s[j] << " ";
            }
        }
        cout << "}" << endl;
    }

    return 0;
}


string findFirst(map<char, vector<string>> m, char ch){

    if (ch == '^' || !(ch >= 'A' && ch <= 'Z')) return ch + "";

    string ans = "";

    for (int i = 0;  i < m[ch].size(); ++i){

        string s = m[ch][i];
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


string findFollow(map<char, vector<string>> prod, char start, char ch){
    string ans = "";
    if (start == ch){
        ans.push_back('$');
    }
    for (auto i = prod.begin(); i != prod.end(); ++i){
        for (int j = 0; j < i->second.size(); ++j){
            //if var doesn't occur in a prod
            if (i->second[j].find(ch) == string::npos){
                continue;
            }
            string tmp = "";
            bool parent = false;
            // loop over that prod
            for (int a = 0; a < i->second[j].length(); ++a){
                parent = false;
                if (i->second[j][a] == ch){
                    //if last char
                    if (a == i->second[j].length() - 1){
                        parent = true;
                    }
                    else{
                        tmp =  firstString(prod, i->second[j].substr(a + 1, i->second[j].length() - a - 1));
                    }
                    for (int k = 0; k < tmp.length(); ++k){
                        if (tmp[k] == '^'){
                            parent = true;
                            continue;
                        }
                        if (ans.find(tmp[k]) == string::npos){
                            ans.push_back(tmp[k]);
                        }
                    }
                }
                if (parent){
                    if (ch == i->first)
                        continue;
                    tmp = findFollow(prod, start, i->first);
                    for (int k = 0; k < tmp.length(); ++k){
                        if (ans.find(tmp[k]) == string::npos){
                            ans.push_back(tmp[k]);
                        }
                    }
                }
            }
        }
    }
    return ans;
}
