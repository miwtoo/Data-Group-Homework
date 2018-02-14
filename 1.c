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

int main(int argc, char** argv) {

    char infix[30], postfix[30];
    printf("Enter infix : ");
    scanf("%s",&infix);


    int i = 0;
    int count = 0;
    while(infix[i] != NULL){
        if(infix[i] >= 'A' && infix[i] <= 'Z' || infix[i] >= 'a' && infix[i] <= 'z'){
            postfix[count++] = infix[i];
            postfix[count++] = ' ';
        }
        if(infix[i] >= '0' && infix[i] <= '9'){
            postfix[count++] = infix[i];
            if(infix[i+1] < '0' || infix[i+1] > '9')
                postfix[count++] = ' ';
        }
        else if (infix[i] == '^' || infix[i] == '*' || infix[i] == '/' || infix[i] == '+'|| infix[i] == '-' || infix[i] == '(' || infix[i] == ')'){
            if(infix[i] == '('){
                push(infix[i]);
            }
            else if(infix[i] == ')'){
                while(stacktop() != '('){
                    postfix[count++] = pop();
                    postfix[count++] = ' ';

                    //printf("%d ", pop());
                }
                pop();
            }
            else{
                if(getPriority(infix[i],stacktop()) == 1){
                    push(infix[i]);
                }

                else{
                    while(getPriority(infix[i],stacktop()) != 1){
                        postfix[count++] = pop();
                        postfix[count++] = ' ';
                    }
                    push(infix[i]);
                }
            }

        }
        i++;
    }

    while(stacktop() != NULL){
        postfix[count++] = pop();
        postfix[count++] = ' ';
    }
    postfix[count] = NULL;

    i = 0;
    printf("postfix : ");
    printf("%s",postfix);
    printf("\n");


    return (EXIT_SUCCESS);
}

