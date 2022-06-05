#include<bits/stdc++.h>
using namespace std;
int n;
string s;
vector<char> st;
vector<char> a;

void StackAndInput(){ 
  cout<<"\n$";
  for(auto x: st)
      cout<<x;
  cout<<"\t";
  for(auto x : a)
      cout<<x;
}
void check()  
{
    for(int i=0;i<st.size();i++)
    {
        if(st[i]=='a')
        {
            st[i]='E';
            StackAndInput();
            cout<<"$\t"<<"REDUCE E->a";
            check(); 
        }
        if(i+2<st.size() && st[i]=='E'&& (st[i+1]==('+') || st[i+1]==('*')) && st[i+2]=='E')
        {
            st.pop_back();
            st.pop_back();
            StackAndInput();
            if(st[i+1]=='+')
              cout<<"$\t"<<"REDUCE E->E+E";
            else if(st[i+1]=='*')
              cout<<"$\t"<<"REDUCE E->E*E";
        }
    }
}
int main()
{
    cout<<"Grammar: \n E->E+E \n E->E*E \n E->a\n";
    cout<<"Enter Input String: ";
    cin>>s;
    n=s.length();
    for(int i=0;i<n;i++)
      a.push_back(s[i]);

    cout<<"\nstack\t input\taction";
    for(int i=0;i<n;i++)
    {
        st.push_back(a[i]);
        a[i]=' '; 
        StackAndInput();
        cout<<"$\t"<<"SHIFT->"<<st.back();
        check();
    }
    if(st.size()==1 && st[0]=='E')
        cout<<"\n\nSTRING ACCEPTED!";
    else
        cout << "\n\nSTRING REJECTED";

    return 0;
}
