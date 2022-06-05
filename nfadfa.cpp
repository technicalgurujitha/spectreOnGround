#include <bits/stdc++.h>

using namespace std;

vector<int> epsilonClosure(int state, vector<vector<vector<int>>> transition);
void printNFA(vector<vector<vector<int>>> transition);
void printDFA(vector<vector<vector<int>>> transition, vector<vector<int>> currentStates);


int main(){
    int numStates;
    cout << "Enter number of states in NFA:\t";
    cin >> numStates;
    int numAlpha;
    cout << "Enter number of letters in alphabet:\t";
    cin >> numAlpha;

    vector<vector<vector<int>>> transition;

    for (int i = 0; i != numStates; ++i){
        cout << "For state " << (char)(i + 'A') << endl;
        vector<vector<int>> vec;
        for (int j = 0; j != numAlpha; ++j){
            vector<int> nextStates;
            cout << "Enter number of output states for input: " <<
                (char)('a' + j) << "\t";
            int numInputs;
            cin >> numInputs;
            cout << "Enter corresponding output states(A-Z):" << endl;
            for (int k = 0; k != numInputs; ++k){
                char nextStateChar;
                int nextState;
                cin >> nextStateChar;
                nextState = (int) (nextStateChar - 'A');
                nextStates.emplace_back(nextState);
            }
            vec.emplace_back(nextStates);
        }
        vector<int> nextStatesEpsilon;
        cout << "Enter number of output states for input ^:\t";
        int numOutputs;
        cin >> numOutputs;
        cout << "Enter corresponding output states(A-Z):" << endl;
        for (int j = 0; j != numOutputs; ++j){
            char nextStateChar;
            int nextState;
            cin >> nextStateChar;
            nextState = (int) (nextStateChar - 'A');
            nextStatesEpsilon.emplace_back(nextState);
        }
        vec.emplace_back(nextStatesEpsilon);
        transition.emplace_back(vec);
    } 

    cout << "NFA Transition Table" << endl;
    printNFA(transition);

    vector<vector<vector<int>>> transitionDFA;
    vector<vector<int>> states;
    states.emplace_back(epsilonClosure(0, transition));

    queue<vector<int>> q;
    q.push(states[0]);

    while (!q.empty()){
        vector<int> front = q.front();
        q.pop();
        vector<vector<int>> vec;

        for (int i = 0; i < numAlpha; ++i){
            vector<int> nextStates;
            set<int> setStates;

            for (int j = 0; j < front.size(); ++j){
                for (int k = 0; k < transition[front[j]][i].size(); ++k){
                    vector<int> closure = epsilonClosure(transition[front[j]][i][k], transition);

                    for (int l = 0; l < closure.size(); ++l){
                        if (setStates.find(closure[l]) == setStates.end()){
                            setStates.insert(closure[l]);
                        }
                    }
                }
            }

            for (set<int>::iterator it = setStates.begin(); it != setStates.end(); ++it){
                nextStates.emplace_back(*it);
            }
            vec.emplace_back(nextStates);

            if (find(states.begin(), states.end(), nextStates) == states.end()){
                states.emplace_back(nextStates);
                q.push(nextStates);
            }
        }
        transitionDFA.emplace_back(vec);
    }
    printDFA(transitionDFA, states);

    return 0;
}


vector<int> epsilonClosure(int state, vector<vector<vector<int>>> transition) {
    vector<int> nextStates;
    queue<int> q;
    nextStates.emplace_back(state);
    int total = transition[state][transition[state].size() - 1].size();
    
    for (int i = 0; i != total; ++i){
        nextStates.emplace_back(transition[state][transition[state].size() - 1][i]);
        q.push(nextStates[i]);
    }

    while (!q.empty()){
        int front = q.front();
        if (!transition[front][transition[front].size() - 1].empty()){
            int totalCur = transition[front][transition[front].size() - 1].size();

            for (int i = 0; i != totalCur; ++i){
                int curr = transition[front][transition[front].size() - 1][i];
                
                if (find(nextStates.begin(), nextStates.end(), curr) == nextStates.end()){
                    nextStates.emplace_back(curr);
                    q.push(curr);
                }
            }
        }
    }

    return nextStates;
}



void printNFA(vector<vector<vector<int>>> transition){ 
    cout << "  State/Input  ";
    cout << " |";
    for (int i = 0; i < transition[0].size() - 1; ++i){
        cout << "   " << (char)('a' + i) << "   |";
    }
    cout << "  ^  " << endl << endl;
    
    for (int i = 0; i < transition.size(); ++i){
        cout << "\t" << (char) ('A' + i) << "\t";
        for (int j = 0; j < transition[i].size(); ++j){
            cout << " | ";
            for (int k = 0; k < transition[i][j].size(); ++k){
                cout << (char) (transition[i][j][k] + 'A') << " ";
            }
        }
        cout << endl;
    }
}


void printDFA(vector<vector<vector<int>>> transition, vector<vector<int>> currentStates){ 
    cout << "  State/Input  ";

    for (int i = 0; i < transition[0].size(); ++i){
        cout << "|  " << (char) ('a' + i) << "  ";
    }    
    cout << endl;

    for (int i = 0; i < currentStates.size(); ++i){
        cout << "{ ";
        for (int j = 0; j < currentStates[i].size(); ++j){
            cout << (char) (currentStates[i][j] + 'A') << " ";
        }
        if (currentStates[i].empty()){
            cout << "^ ";
        }
        cout << "} ";

        for (int j = 0; j < transition[i].size(); ++j){
            cout << " | ";
            for (int k = 0; k < transition[i][j].size(); ++k){
                cout <<  (char) (transition[i][j][k] + 'A') << " ";
            }
            if (transition[i][j].empty()){
                cout << "^ ";
            }
        }
        cout << endl;
    }
}
