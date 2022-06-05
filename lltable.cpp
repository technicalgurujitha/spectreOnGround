#include <bits/stdc++.h>
using namespace std;


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
            if (i->second[j].find(ch) == string::npos){
                continue;
            }
            string tmp = "";
            bool parent = false;
            for (int a = 0; a < i->second[j].length(); ++a){
                parent = false;
                if (i->second[j][a] == ch){
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

int main(){
    map <char, vector<string>> prod;
    int n;
    int t;
    cout << "Enter number of terminals: ";
    cin >> t;
    cout << "Enter terminals" << endl;
    map <char, int> terminals;
    for (int i = 0; i < t; ++i){
        char ch;
        cin >> ch;

        terminals[ch] = i;
    }
    terminals['$'] = t;
    cout << "Enter number of productions: ";
    cin >> n;
    cout << "Enter productions: " << endl;
    char start;
    for (int i = 0; i < n; ++i){
        char ch;
        string s;
        cin >> ch;
        if (i == 0)
            start = ch;
        cout << " -> ";
        cin >> s;
        prod[ch].push_back(s);
    }
    cout << "Given grammar is: " << endl;
    for (auto i : prod){
        cout << i.first << " -> ";
        for (int j = 0; j < i.second.size(); ++j){
            cout << i.second[j];
            if (j != i.second.size() - 1){
                cout << " | ";
            }
        }
        cout << endl;
    }

    vector<vector<string>> table(prod.size(), vector<string> (t + 1, ""));
    for (map<char, vector<string>>::iterator i = prod.begin(); i != prod.end(); ++i) {
        for (int j = 0; j < i->second.size(); ++j){
            string s = firstString(prod, i->second[j]);
            bool hasnull = false;
            bool hasnull2 = false;
            for (int k = 0; k < s.length(); ++k){
                if (s[k] == '^'){
                    hasnull = true;
                    continue;
                }
                string gg = "";
                gg = gg + i->first;
                gg = gg + " -> ";
                gg = gg + i->second[j];
                table[i->first - 'A'][terminals[s[k]]] = gg;
            }
            //shouldn't it enter A->a in M[A,b] for all b in Follow(A)
            if (hasnull) {
                string temp = findFollow(prod, start, i->first);
                for (int k = 0; k < temp.length(); ++k){
                    string ss = "";
                    ss += i->first;
                    ss += " -> ^";
                    table[i->first - 'A'][terminals[temp[k]]] = ss;
                }
            }
        }
    }
    cout << endl << endl;
    cout << "Non terminals \\ Terminals | ";
    vector<char> vv(t+1);
    for (map<char, int>::iterator i = terminals.begin(); i != terminals.end(); ++i)
        vv[i->second] = i->first;
    for (int i = 0; i < vv.size(); ++i)
        cout << "\t" << vv[i] <<"\t| ";
    cout << endl;
    int ii = 0;
    for (map<char, vector<string>>::iterator i = prod.begin(); i != prod.end(), ii < table.size(); i++, ii++){
        cout << "\t\t" << i->first << "\t\t|";
        for (int j = 0; j < table[ii].size(); ++j){
            cout << " " << table[ii][j] << " | ";
        }
        cout << endl;
    }
    
    
    return 0;
}
