#include <stdlib.h>
#include <stdio.h>

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
    char ch;
    node *n;
    n = top;
    top = top -> next;
    ch = n -> c;
    free(n);
    count--;
    return ch;
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
    else if(ch1 == '+' || ch1 == '-')
        a = 0;


    if(ch2 == '*' || ch2 == '/')
        b = 1;
    else if(ch2 == '+' || ch2 == '-')
        b = 0;

    if(a <= b)
        return 0; // ใส่ไม่ได้
    else
        return 1;

}

int main(){
    char str[30];
    char str2[30];

    scanf("%s",&str);

    int i = 0, count = 0;;
    while(str[i] != NULL){
        push(str[i]);
    }
    i = 0;
    while(str[i] != NULL){
        if(getPriority(str[i],stacktop()) == 1 )
            printf("%c",pop());
        i++;
    }
    //printf("%s",str);
    return 0;
}
