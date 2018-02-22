#include <stdio.h>
#include <stdlib.h>

#define arys 30 // array size

typedef struct cnd{
    char c;
    struct cnd *next;
}cnode;
cnode *ctop = NULL;
int ccount = 0;

void cpush(char ch){
    cnode *n = malloc(sizeof(cnode));
    n -> next = ctop;
    ctop = n;
    n -> c = ch;
    ccount++;
}

char cpop(){
    if(ctop == NULL)
        return NULL;
    else{
        char ch;
        cnode *n;
        n = ctop;
        ctop = ctop -> next;
        ch = n -> c;
        free(n);
        ccount--;
        return ch;
    }
}

char cstackctop(){
    if(ctop == NULL)
        return NULL;
    else
        return ctop -> c;
}

int getPriority(char ch1,char ch2){
    // ch2 = ctop
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

int select(char s[arys]){
    int i = 0;
    int ch = 0, num = 0, ope = 0, unknow = 0, space;
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

const char *getPostfix(char infix[arys]){
    static char postfix[arys];
    int i = 0;
    int count = 0;
    while(infix[i] != NULL){
        if(infix[i] == ' '){

        }
        else if(infix[i] >= 'A' && infix[i] <= 'Z' || infix[i] >= 'a' && infix[i] <= 'z'){
            postfix[count++] = infix[i];
            if((infix[i+1] < 'A' || infix[i+1] > 'Z' ) && (infix[i+1] < 'a' || infix[i+1] > 'z' ))
                postfix[count++] = ' ';
        }
        else if((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.'){
            postfix[count++] = infix[i];
            if((infix[i+1] < '0' || infix[i+1] > '9') && infix[i+1] != '.')
                postfix[count++] = ' ';
        }
        else if (infix[i] == '^' || infix[i] == '*' || infix[i] == '/' || infix[i] == '+'|| infix[i] == '-' || infix[i] == '(' || infix[i] == ')'){
            if(infix[i] == '('){
                cpush(infix[i]);
            }
            else if(infix[i] == ')'){
                while(cstackctop() != '('){
                    postfix[count++] = cpop();
                    postfix[count++] = ' ';

                    //printf("%d ", cpop());
                }
                cpop();
            }
            else{
                if(getPriority(infix[i],cstackctop()) == 1){
                    cpush(infix[i]);
                }

                else{
                    while(getPriority(infix[i],cstackctop()) != 1){
                        postfix[count++] = cpop();
                        postfix[count++] = ' ';
                    }
                    cpush(infix[i]);
                }
            }

        }
        i++;
    }

    while(cstackctop() != NULL){
        postfix[count++] = cpop();
        postfix[count++] = ' ';
    }
    postfix[count] = NULL;


    return postfix;
}

int main(){
    int choice;
    char infix[arys], postfix[arys];
    printf("Enter Menu Number Following\n");
    printf("1. Infix to Postfix\n");
    printf("2. Postfix to Infix\n");
    printf("99. Exit\n");
    printf("-------------------------------------\n");
    do{
        printf("Enter choice : ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter infix : ");
                scanf("%d",&infix);
                //gets(infix);

                if(select(infix) == -1){
                    printf("Invalid expression\n\n");
                }
                else if(select(infix) == -2){
                    printf("Please input operator\n\n");
                }
                else if(select(infix) == 1 || select(infix) == 2){
                    printf("%s", getPostfix(infix));
                    printf("\n\n");
                }
                else if(select(infix) == 3){
                    // ตัวเลข
                    //printf("This num only\n");
                    printf("Postfix : %s\n", getPostfix(infix));
                    //getPostfix(infix);
                }
                break;
        }
    }while(choice != 99);
}
