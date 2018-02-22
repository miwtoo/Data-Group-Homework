#include <stdio.h>

int main(){
    char a[30] = "(((5(B(*C)+d)";

    //scanf("%s[^\n]",&a);
    //gets(a);

    int i = 0;
    //while(a[i] != NULL){
        if(a[i] == '('){
            while(a[i] != ')'){
                printf("%c",a[i]);
                i++;
            }
        }
        i++;
    //}
    //printf(")");

}
