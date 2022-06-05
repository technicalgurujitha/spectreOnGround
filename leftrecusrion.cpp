#include <bits/stdc++.h>
#include <boost/tokenizer.hpp>
using namespace std;

vector<string> split(string s, const char* sep1, const char* sep2);

class CFG{
public:
    CFG(const vector<string>& productions) {
        //parse productions manually - many RHS case, remove whitespaces
        for (string prod : productions){
            //removing whitespaces
            //remove just shuffles, call erase to modify length of string
            string::iterator endPos = remove(prod.begin(), prod.end(), ' ');
            prod.erase(endPos, prod.end());

            string rhs = prod.substr(3);
            // rhs can have many productions
            vector<string> multiProds = split(rhs, "/", "");
            for (string i : multiProds){
                string newProd = prod.substr(0, 3) + i; 
                this->productions.emplace_back(newProd);
            }
                
        }

        for (string i : this->productions){
            nonTerminals.insert(i[0]);
        }
    };
    bool isLeftRecursive(const string& prod){
        return prod[0] == prod[3];
    }
    void removeLeftRecursion();
    static bool comparator(const string& s1, const string& s2){
        if (s1[0] < s2[0]) return true;
        else if (s1[0] > s2[0]) return false;
        else{
            if (s1[1] == '\'')  return false;
            else if (s2[1] == '\'') return true;
            else{
                return true;
            }
        }
    }
private:
    vector<string> productions;
    set<char> nonTerminals;
};


int main(){
    vector<string> productions;
    cout << "Enter number of productions in the grammar:\t";
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i){
        string prod;
        cout << "Enter production " << i + 1 << ":\t";
        cin >> prod;
        productions.emplace_back(prod);
    }
    
    CFG cfg(productions);
    cfg.removeLeftRecursion();
    return 0;
}


void CFG::removeLeftRecursion(){

    vector<string> newProds;

    for (char s : nonTerminals){
        string newNonTerminal = "";
        newNonTerminal += s;
        newNonTerminal += "'";
        for (string prod : productions){
            if (prod[0] == s){

                if (isLeftRecursive(prod)){
                    string alpha = prod.substr(4);
                    string newProd = "";
                    newProd += newNonTerminal;
                    newProd += "->" + alpha +  newNonTerminal;
                    newProds.emplace_back(newProd);
                }
                else{
                    string beta = prod.substr(3);
                    string newProd = "";
                    newProd += prod[0];
                    newProd += "->" + beta + newNonTerminal;
                    newProds.emplace_back(newProd);
                }
            }
        }
        string epsilonProd = newNonTerminal + "->^";
        newProds.emplace_back(epsilonProd);
    }
    cout << endl << "Productions after removing left recursion" << endl;

    this->productions = newProds;
    sort(productions.begin(), productions.end(), comparator);
    for (auto i : this->productions){
        cout << i << endl;
    }
}

vector<string> split(string s, const char* sep1, const char* sep2)
{
    vector<string> tokens;
    boost::char_separator<char> sep(sep1, sep2);
    boost::tokenizer<boost::char_separator<char> > tok(s, sep);
    for(auto i = tok.begin(); i!=tok.end(); ++i)
        tokens.emplace_back(*i);
    return tokens;
}

