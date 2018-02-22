#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define arys 30 // array size
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
//-------------
typedef struct fnd{
    float f;
    struct fnd *next;
}fnode;
fnode *ftop = NULL;
int fcount = 0;

void fpush(float fl){
    fnode *n = malloc(sizeof(fnode));
    n -> next = ftop;
    ftop = n;
    n -> f = fl;
    fcount++;
}

float fpop(){
    if(ftop == 0)
        return 0;
    else{
        float fl;
        fnode *n;
        n = ftop;
        ftop = ftop -> next;
        fl = n -> f;
        free(n);
        fcount--;
        return fl;
    }
}

float fstackftop(){
    if(ftop == 0)
        return 0;
    else
        return ftop -> f;
}


int select(char s[arys]){
    int i = 0;
    int ch = 0, num = 0, ope = 0, unknow = 0, space = 0;
    while(s[i] != NULL){
        if(s[i] >= 'A' && s[i] <= 'Z' || s[i] >= 'a' && s[i] <= 'z')
            ch++;
        else if(s[i] >= '0' && s[i] <= '9' || s[i] == '.'){
                num++;
        }
        else if(s[i] == '^' || s[i] == '*' || s[i] == '/' || s[i] == '+'|| s[i] == '-' || s[i] == '(' || s[i] == ')')
            ope++;
        else if(s[i] == ' ')
            space++;
        else
            unknow++;

        i++;
    }
    //printf("ch = %d num = %d ope = %d unknow = %d space = %d\n", ch, num, ope, unknow, space);
    if(unknow > 0) //ใส่เครื่องหมายไม่รู้จัก
        return -1;
    else if(ope == 0)// ไม่ใส่ตัวดำเนินการ
        return -2;
    else if(num == 0 && ch > 0) //กรณีเจอแต่ตัวอักษร
        return 1;
    else if(num > 0 && ch > 0) // กรณีเจอทั้งตัวเลขและตัวอักษร
        return 2;
    else if(num > 0 && ch == 0) // กรณีเจอแต่ตัวเลข
        return 3;

}

void getInfix(char postfix[arys]){
    int i = 0;
    char tmp[arys];
    char infix[arys];
    while(postfix[i] != NULL){
        if(postfix[i] == ' '){

        }
        if(postfix[i] >= 'A' && postfix[i] <= 'Z' || postfix[i] >= 'a' && postfix[i] <= 'z' || postfix[i] >= '0' && postfix[i] <= '9'){
            push(postfix[i]);
        }
        else if(postfix[i] == '^' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '+' || postfix[i] == '-'){
            char ch = '+';
            int j = 0;
            while(ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-'){

                while(stacktop() == '(' || stacktop() == ')'){
                    tmp[j++] = pop();
                }
                tmp[j++] = pop();
                if(stacktop() == '^' || stacktop() == '*' || stacktop() == '/' || stacktop() == '+' || stacktop() == '-')
                    tmp[j++] = pop();
                else
                    ch = stacktop();
            }

            tmp[j++] = postfix[i];
            tmp[j++] = pop();
            j -= 1;

            while(j >= 0){
                push(tmp[j]);
                j--;
            }

        }
        i++;
    }
    i = 0;
    while(stacktop() != NULL){
        //printf("%d ",i);
        infix[i] = pop();
        //printf("%c",pop());
        i++;
    }
    i -= 1;
    while(i >= 0){
        if((postfix[i] >= '0' && postfix[i] <= '9')){
            printf("%c ",infix[i]);
        }
        else{
            printf("%c",infix[i]);
        }
        i--;
    }
    printf("\n");
    //printf("%s",infix);
}

float operation(float f, float l, char ope){
    switch(ope){
        case '+' : return f+l;
        case '-' : return f-l;
        case '*' : return f*l;
        case '/' : return f/l;
        case '^' : return pow(f,l);
    }
}

void getNum(char postfix[arys]){
    float result = 0;
    float d = 0;
    float base = 0.1;
    int i = 0;
    int c = 0;
    while(postfix[i] != NULL){
        //printf("%c",postfix[i]);
        if((postfix[i] >= '0' && postfix[i] <= '9') || postfix[i] == '.'){

            if(postfix[i] == '.')
                c++;

            if(c == 0 && postfix[i] != '.'){
                d = d*10 + (postfix[i] - '0');
            }
            if(c == 1 && postfix[i] != '.'){
                d = d + (postfix[i] - '0')*base;
                base*= 0.1;
            }

            if(postfix[i+1] == ' '){
                fpush(d);
                d = 0;
                base = 0.1;
                printf("\n");
                c = 0;
            }

        }
        if(postfix[i] == '^' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '+'|| postfix[i] == '-'){
            float l = fpop();
            float f = fpop();
            result = operation(f,l,postfix[i]);
            fpush(result);
        }
        i++;
    }
    printf("%.4f",fpop());
    printf("\n");
}

int main(){

    char infix[arys], postfix[arys];
    while(1){
        printf("Enter postfix : ");
        gets(postfix);

        if(select(postfix) == -1){
            printf("Invalid expression\n\n");
        }
        else if(select(postfix) == -2){
            printf("Please input operator\n\n");
        }
        else if(select(postfix) == 1 || select(postfix) == 2){
            getInfix(postfix);
        }
        else if(select(postfix) == 3){
            getNum(postfix);
        }
    }
    //printf("%s",infix);
    return 0;
}
