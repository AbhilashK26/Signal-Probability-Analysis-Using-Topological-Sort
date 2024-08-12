#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_SIZE 10000

int vis[MAX_SIZE];
//float probability[MAX_SIZE];

//stack section
typedef struct stack
{
       int top;
       int max_size;
       int *instorage;
}stack;

stack* createIntegerStack(int stackSize)
{
      stack *vstack;
      vstack = (stack*)malloc(sizeof(stack));
      vstack->top = -1;
      vstack->max_size = stackSize;
      vstack->instorage = (int*)malloc(stackSize*sizeof(int));
      if(vstack ==  NULL)
      { 
         return NULL;
      }
      return vstack;
}
int pushstack(stack *vstack,int p)
{
    if(vstack->top + 1 == vstack->max_size)
    {
       printf("Stack is full.\n");
       return 0;
    }
    vstack->top++;
    vstack->instorage[vstack->top] = p;
    return 1;
}
int popint(stack* vstack,int *dp)
{
    if(vstack->top == -1)
    {
       printf("Stack is empty.\n");
       return 0;
    }
    *dp = vstack->instorage[vstack->top];
    vstack->top--;
    return 1;
}
int freestack(stack *s)
{
    free(s->instorage);
    free(s);
    return 1;
}
int isstackfull(stack* vstack)
{
    if(vstack->top + 1 == vstack->max_size)
        {
            return 1;
        }
        return 0;
}
int isstackempty(stack *vstack)
{
    if(vstack->top == -1)
    {
        return 1;
    }
    return 0;
} 
void displayStack(stack *Mystack)
{
    int t = Mystack->top;
    printf("***TOP***\n");
    for(int i=t;i!=-1;i--)
    {
        printf("%d\n",Mystack->instorage[i]);
    }
    printf("**END**\n");
}
//stack section


struct path
{
    char a;
    int b;
};

#define path struct path

void printpath(path *d)
{
    printf("%c%d\n",d->a,d->b);
}

int toInt(char *ptr)
{
    int n = 0;
    while (*ptr >= '0' && *ptr <= '9') {
        n = n * 10 + (*ptr - '0');
        ptr++;
    }
    return n;
}

char* takein(path *p,char *s)
{
    while(*s!='(')
    {
        s++;
    }
    p->a = *(s+1);
    s += 2;
    char ptr[50];
    int i = 0;
    while(*s>='0' && *s<='9')
    {
        ptr[i] = *s;
        i++;
        s++;
    }
    ptr[i] = '\0';
    p->b = toInt(ptr);
    return s;
}

void GateExt(char *str,path *p)
{
    while(*str>'Z' || *str<'A')
    {
        str++;
    }
    p->a = str[0];
    int i = 1;
    char s[100];
    int j = 0;
    while (str[i] >= '0' && str[i] <= '9') {
        s[j++] = str[i++];
    }
    s[j] = '\0';
    p->b = toInt(s);
}


int Is_Input(char* s,path *p,int size)
{
    path p1;
    char *s2 = takein(&p1,s);
    for(int i=0;i<size;i++)
    {
        if(p1.b == p[i].b)
        {
            path p2;
            GateExt(s2,&p2);
            for(int i=0;i<size;i++)
            {
                if(p2.b == p[i].b)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int Is_Output(char* s,path *p,int size)
{
    path p1;
    GateExt(s,&p1);
    for(int i=0;i<size;i++)
    {
        if(p1.b == p[i].b)
        {
            GateExt(s,&p1);
            for(int i=0;i<size;i++)
            {
                if(p1.b == p[i].b)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void DFS(int a,FILE *rf,stack *MyStack)
{
    fseek(rf,0,SEEK_SET);
    char s[50];
    while(fgets(s,40,rf) != NULL)
    {
        path p;
        path p1;
        path p2;
        GateExt(s,&p);
        GateExt(takein(&p1,s),&p2);
        if((p1.b == a || p2.b == a) && (vis[p.b] != 1))
        {
            DFS(p.b,rf,MyStack);
            vis[p.b] = 1;
            pushstack(MyStack,p.b);
            fseek(rf,0,SEEK_SET);
        }
    }
}

//PROBABILITY FUNCTIONS
float pOfAND(float pi1,float pi2)
{
    return pi1 * pi2;
}

float pOfNAND(float pi1, float pi2) {
    return 1.0f - (pi1 * pi2);
}

float pOfNOT(float p1) {
    return 1.0f - p1;
}

float pOfOR(float pi1, float pi2) {
    return ((1.0f - pi1) * (1.0f - pi2));
}
float pOfNOR(float pi1, float pi2) {
    return 1.0f - ((1.0f - pi1) * (1.0f - pi2));
}

float pOfXOR(float pi1, float pi2) {
    return (1.0f - pi1) * (pi2) + (pi1) * (1.0f - pi2);
}

float pOfXNOR(float pi1, float pi2) {
    return 1.0f - ((1.0f - pi1) * (pi2) + (pi1) * (1.0f - pi2));
}

float Dprobab(char *s,float f1,float f2)
{
    while(*s != '=')
    {
        s++;
    }
    s = s + 2;
    char g[7];
    int i = 0;
    while(*s != '(')
    {
        g[i] = *s;
        i++;
        s++;
    }
    g[i] = '\0';
    char and[5] = "AND";
    char or[5] = "OR";
    char not[5] = "NOT";
    char nand[5] = "NAND";
    char xor[5] = "XOR";
    char nor[5] = "NOR";
    char xnor[5] = "XNOR";
    if(!strcmp(g,and))
    {
        return pOfAND(f1,f2);
    }
    else if(!strcmp(g,or))
    {
        return pOfOR(f1,f2);
    }
    else if(!strcmp(g,not))
    {
        return pOfNOT(f1);
    }
    else if (!strcmp(g, nand))
    {
    return pOfNAND(f1, f2);
    }
    else if (!strcmp(g, xor))
    {
    return pOfXOR(f1, f2);
    }
    else if (!strcmp(g, nor))
    {
    return pOfNOR(f1, f2);
    }
    else if (!strcmp(g, xnor))
    {
    return pOfXNOR(f1, f2);
    }
}

int main()
{
    float probability[24];
    stack *MyStack = createIntegerStack(MAX_SIZE);
    FILE *ptr = fopen("c17.bench","r");
    char s[50];
    fgets(s,40,ptr);
    int max = 0;
    while(strstr(s,"OUTPUT") == NULL && strstr(s,"INPUT") != NULL)
    {
        max++;
        fgets(s,40,ptr);
    }
    fseek(ptr,0,SEEK_SET);
    int In_Size = max;
    path pIn[max];
    fgets(s,40,ptr);
    int i = 0;
    while(strstr(s,"OUTPUT") == NULL && strstr(s,"INPUT") != NULL)
    {
        takein(pIn+i,s);
        i++;
        fgets(s,40,ptr);
    }
    max = 0;
    fgets(s,40,ptr);
    while(strstr(s,"OUTPUT") != NULL && strstr(s,"INPUT") == NULL)
    {
        max++;
        fgets(s,40,ptr);
    }
    fseek(ptr,0,SEEK_SET);
    int Out_Size = max;
    path pOut[max];
    fgets(s,40,ptr);
    while(strstr(s,"OUTPUT") == NULL && strstr(s,"INPUT") != NULL)
    {
        fgets(s,40,ptr);
    }
    fgets(s,40,ptr);
    i = 0;
    while(strstr(s,"OUTPUT") != NULL && strstr(s,"INPUT") == NULL)
    {
        takein(pOut+i,s);
        i++;
        fgets(s,40,ptr);
    }
    fseek(ptr,0,SEEK_SET);
    fgets(s,40,ptr);
    while(strstr(s,"INPUT") != NULL)
    {
        fgets(s,40,ptr);
    }
    fgets(s,40,ptr);
    while(strstr(s,"OUTPUT") != NULL)
    {
        fgets(s,40,ptr);
    } 
    FILE * rf = fopen("relationfile.txt","w");
    while(fgets(s,40,ptr) != NULL)
    {
        fputs(s,rf);
    }
    fclose(rf);
    fclose(ptr);
    rf = fopen("relationfile.txt","r");
    while(fgets(s,40,rf) != NULL)
    {
        path p;
        GateExt(s,&p);
        if(Is_Input(s,pIn,In_Size) && vis[p.b]!=1)
        {
            DFS(p.b,rf,MyStack);
            vis[p.b] = 1;
            pushstack(MyStack,p.b);
            fseek(rf,0,SEEK_SET);
        }
    }
    displayStack(MyStack);
    for(int i=0;i<In_Size;i++)
    {
        probability[pIn[i].b] = 0.5;
    }
    fseek(rf,0,SEEK_SET);
    int data;
    while(!isstackempty(MyStack))
    {
        char *check;
        path p1;
        popint(MyStack,&data);
        check = fgets(s,40,rf);
        GateExt(s,&p1);
        while(p1.b != data &&  check!= NULL)
        {
            check = fgets(s,40,rf);
            GateExt(s,&p1);
        }
        path px;
        path py;
        char *ptr;
        ptr = takein(&px,s);
        GateExt(ptr,&py);
        probability[p1.b] = Dprobab(s,probability[px.b],probability[py.b]);
        printf("N%d -> %f\n",p1.b,probability[p1.b]);
        fseek(rf,0,SEEK_SET);
    }
    return 0;
}