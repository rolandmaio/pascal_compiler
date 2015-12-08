#include<cstdio>
using namespace std;

int main(){
    char c;//[8];
    //size_t t;
    //scanf("%8c", c);
    //printf("scanned\n");
    //c[0] = '0';
    //t = (size_t) *c;
    //printf("%zd ", t);
    while(scanf("%c", &c) != EOF) printf("%hhu ", (unsigned char)c);
    //printf("\n%zu\n", t);
}
