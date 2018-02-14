#include <stdio.h>
#include <stdlib.h>

typedef struct nd{
    char c;
    struct nd *next;
}node;
node *top = NULL;
int count = 0;

void push(char ch){
    node *n = malloc(sizeof(node));
    n -> next = top;
    top = n;
    n -> c = ch;
    count++;
}

char pop(){
    if(top == NULL)
        return NULL;
    else{
        char ch;
        node *n;
        n = top;
        top = top -> next;
        ch = n -> c;
        free(n);
        count--;
        return ch;
    }
}

char stacktop(){
    if(top == NULL)
        return NULL;
    else
        return top -> c;
}

int getPriority(char ch1,char ch2){
    // ch2 = top
    int a = 0,b = 0; // ^ = 2    *,/ = 1      +,- = 0
    if(ch1 == '*' || ch1 == '/')
        a = 1;
    else if(ch1 == '^')
        a = 2;
    else if(ch1 == '+' || ch1 == '-')
        a = 0;

    if(ch2 == '*' || ch2 == '/')
        b = 1;
    else if(ch2 == '^')
        b = 2;
    else if(ch2 == '+' || ch2 == '-')
        b = 0;
    else if(ch2 == NULL)
        return 1;
    else if(ch2 == '(')
        return 1;

    if(a <= b)
        return 0; // ใส่ไม่ได้
    else
        return 1;

}

int main(){

    char infix[30] = "", postfix[30];
    printf("Enter postfix : ");
    scanf("%s",&postfix);

    int i = 0;
    char tmp[30];
    while(postfix[i] != NULL){
        if(postfix[i] >= 'A' && postfix[i] <= 'Z' || postfix[i] >= 'a' && postfix[i] <= 'z'){
            //printf("MU ");
            push(postfix[i]);
        }
        else if(postfix[i] == '^' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '+' || postfix[i] == '-'){
            char ch = '+';
            int j = 0;
            while(ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-'){
                //printf("EI ");
                //tmp[j++] = ')';
                while(stacktop() == '(' || stacktop() == ')'){
                    //printf("GGWP ");
                    tmp[j++] = pop();
                }
                tmp[j++] = pop();
                if(stacktop() == '^' || stacktop() == '*' || stacktop() == '/' || stacktop() == '+' || stacktop() == '-')
                    tmp[j++] = pop();
                else
                    ch = stacktop();
            }
            //printf("KA ");

            tmp[j++] = postfix[i];
            tmp[j++] = pop();
            //tmp[j++] = '(';
            j -= 1;

            while(j >= 0){
                //printf("%d ",j);
                push(tmp[j]);
                j--;
            }

        }
        i++;
    }
    //i -= 1;
    i = 0;
    while(stacktop() != NULL){
        //printf("%d ",i);
        infix[i] = pop();
        //printf("%c",pop());
        i++;
    }
    i -= 1;
    while(i >= 0){
        printf("%c",infix[i]);
        i--;
    }

    //printf("%s",infix);
    return 0;
}
