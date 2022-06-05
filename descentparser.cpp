#include <stdio.h>
#include <string.h>
void E();
void Ed();
void T();
void Td();
void F();


int i, f;
char str[100];

int main(){
    i = 0;
    f = 0;
    
    int exit = 0;

    printf("Grammar is:\n");
    printf("E->TE'\nE'->+TE'|^\nT->FT'\nT'->*FT'|^\nF->(E)|d\n\n");
    while (exit == 0){
        i = 0;
        f = 0;
        printf("Enter a string to parse (type x to exit):\n");
        scanf("%s", str);
        if (str[0] == 'x'){
            exit = 1;
            break;
        }
        E();
        if ((strlen(str) == i) && (f == 0)){
            printf("PARSING SUCCESSFUL\n\n");
        }
        else{
            printf("PARSING ERROR\n\n");
        }
    }
    return 0;
}


void E(){
    T();
    Ed();
}

void Ed(){
    if (str[i] == '+'){
        i++;
        T();
        Ed();
    }
}

void T(){
    F();
    Td();
}

void Td(){
    if (str[i] == '*'){
        i++;
        F();
        Td();
    }
}

void F(){
    if (str[i] == '('){
        i++;
        E();
        if (str[i] == ')')
        {
            i++;
        }
        else{
            f = 1;
        }
    }
    else if (str[i] == 'd'){
        i++;
    }
    else
        f = 1;
}
