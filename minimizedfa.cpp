#include <bits/stdc++.h>
using namespace std;

class DFA{
public:
    DFA(set<string>& states, set<string>& alphabet, string& startState,
     set<string>& finalStates, map<string, map<string, 
     string>>& transition) : states{states}, alphabet{alphabet}, 
        startState{startState}, finalStates{finalStates}, transition{transition} { }
    
    void removeUnreachableStates();
    void mergeNonDistinguishaleStates();
    void minimize();
    set<string> setDiff(set<string>& s1, set<string>& s2);
    set<string> setUnion(set<string>& s1, set<string>& s2);
    string findMergedState(string& state, set<string>& states);
    void printStates();
    void printDFA();
    bool inNestedSet(string& s, set<set<string>>& nestedSet);
    
private:
    set<string> states;
    set<string> alphabet;
    string startState;
    set<string> finalStates;
    map<string, map<string, string>> transition;
};




int main(){
    set<string> states;
    set<string> alphabet;
    string startState;
    set<string> finalStates;
    map<string, map<string, string>> transition;

    int numStates, numAlphabet, numFinalStates;

    cout << endl << endl << "Enter number of states:\t";
    cin >> numStates;
    for (int i = 1; i <= numStates; ++i){
        cout << "Enter state #" << i << ":\t";
        string state;
        cin >> state;
        states.insert(state);
    }
    cout << endl << endl;
    cout << "Enter elements in alphabet:\t";
    cin >> numAlphabet;
    for (int i = 1; i <= numAlphabet; ++i){
        cout << "Enter alphabet #" << i << ":\t";
        string alpha;
        cin >> alpha;
        alphabet.insert(alpha);
    }
    cout << endl << endl;

    cout << "Enter start state:\t";
    cin >> startState;
    cout << endl << endl;
    
    cout << "Enter number of final states:\t";
    cin >> numFinalStates;
    for (int i = 1; i <= numFinalStates; ++i){
        cout << "Enter final state #" << i << ":\t";
        string finalState;
        cin >> finalState;
        finalStates.insert(finalState);
    }
    cout << endl << endl;
    for (auto state : states){
        cout << "Enter next state for state " << state << " for the following inputs:" << endl;
        for (auto alpha : alphabet){
            cout << "\t" << "For input " << alpha << ":\t";
            string nextState;
            cin >> nextState;
            transition[state][alpha] = nextState;
        }
    }
    DFA dfa(states, alphabet, startState, finalStates, transition);
    dfa.minimize();

    return 0;
}


void DFA::removeUnreachableStates(){
    set<string> reachableStates, newStates;
    reachableStates.insert(startState);
    newStates.insert(startState);
    
    do{
        set<string> temp;
        for (auto q : newStates){
            for (auto alpha : alphabet){
                // all p's s.t. p = delta(q, alpha)
                string nextState = transition[q][alpha];
                if (nextState.size()){
                    temp.insert(transition[q][alpha]);
                }
            }
        }
        newStates = setDiff(temp, reachableStates); 
        reachableStates = setUnion(reachableStates, newStates);
    } while (!newStates.empty());

    states = reachableStates;
}



set<string> DFA::setDiff(set<string>& s1, set<string>& s2){
    set<string> res;
    set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), 
                    inserter(res, res.end()));
    return res;
}

set<string> DFA::setUnion(set<string>& s1, set<string>& s2){
    set<string> res;
    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
                inserter(res, res.begin()));
    return res;
}

void DFA::printStates(){
    cout << endl;
    cout << "States of the DFA:" << endl;
    for (auto i : states){
        cout << i << " ";
    }
    cout << endl;
}

void DFA::mergeNonDistinguishaleStates(){
    map<string, map<string, bool>> distinctStates;

    for (auto i : states){
        for (auto j : states){
            if (i != j){
                bool isIFinal = finalStates.find(i) != finalStates.end();
                bool isJFinal = finalStates.find(j) != finalStates.end();
                distinctStates[i][j] = isIFinal ^ isJFinal;
            }
        }
    }

    bool newDistinctState = false;
    
    do{
        newDistinctState = false;
        for (auto i : states){
            for (auto j : states){
                if (i == j || distinctStates[i][j]){
                    continue;
                }
                for (auto alpha : alphabet){
                    string nextStateI = transition[i][alpha];
                    string nextStateJ = transition[j][alpha];

                    if (nextStateI != nextStateJ && distinctStates[nextStateI][nextStateJ]){
                        distinctStates[i][j] = true;
                        newDistinctState = true;
                    }
                }
            }
        }
    } while (newDistinctState);

    set<set<string>> mergedStates;

    
    for (auto s : states){
        
        if (inNestedSet(s, mergedStates))
            continue;

        set<string> newSet;
        newSet.insert(s);
        for (auto t : states){
            if (s != t && !distinctStates[s][t]){
                newSet.insert(t);
            }
        }
        mergedStates.insert(newSet);
    }

    set<string> newStates;
    set<string> newFinalStates;
    string newStartState;
    map<string, map<string, string>> newTransition;

    for (auto stateSet : mergedStates){
        bool isStart = false;
        bool isFinal = false;

        string newState = "{ ";
        for (auto state : stateSet){
            if (!state.compare(startState)){
                isStart = true;
            }
            if (finalStates.find(state) != finalStates.end()){
                isFinal = true;
            }
            newState += state + " "; 
        }
        newState += "}";

        newStates.insert(newState);
        if (isStart){
            newStartState = newState;
        }
        if (isFinal){
            newFinalStates.insert(newState);
        }
    }

    for (auto state : states){
        for (auto alpha : alphabet){
            string transitionState = transition[state][alpha];
            string mergedState = findMergedState(state, newStates);
            string mergedTransitionState = findMergedState(transitionState, newStates);
            newTransition[mergedState][alpha] = mergedTransitionState;
        }
    }

    states = newStates;
    startState = newStartState;
    finalStates = newFinalStates;
    transition = newTransition;
}

bool DFA::inNestedSet(string& s, set<set<string>>& nestedSet){
    for (auto set : nestedSet){
        for (auto state : set){
            if (s == state)
                return true;
        }
    }
    return false;
}

string DFA::findMergedState(string& state, set<string>& states){
    for (auto mergedState : states){
        if (mergedState.find(state) != string::npos)
            return mergedState;
    }
    return "";
}

void DFA::printDFA(){
    printStates();
    cout << endl;
    cout << "Start state:\t" << startState << endl << endl;
    cout << "Final states:" << endl;
    for (auto i : finalStates){
        cout << i << " ";
    }
    cout << endl << endl;
    cout << "Transition table:" << endl;

    cout << "State/Input ";
    for (auto alpha : alphabet){
        cout << " " << alpha << " | ";
    } 
    cout << endl;
    for (auto state : states){
        cout << " " << state << "\t   | ";
        for (auto alpha : alphabet){
            cout << " " << transition[state][alpha] << " | ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void DFA::minimize(){
    cout << endl << endl;
    cout << "************  ORIGINAL DFA  *************" << endl << endl;
    printDFA();
    removeUnreachableStates();
    mergeNonDistinguishaleStates();
    cout << "**********  MINIMIZED DFA  *********" << endl << endl;
    printDFA();
}
