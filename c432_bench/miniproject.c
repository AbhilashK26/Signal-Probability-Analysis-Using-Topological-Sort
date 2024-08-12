#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 10000

struct GateInfo {
    char name[10];
    float p;
};

char v[MAX_SIZE][10];
int vcount = 0;

// Stack Section
typedef struct stack {
    int top;
    int max_size;
    int count;
    char **instorage;
} stack;

stack* createCharStack(int stackSize) {
    stack *vstack = (stack*)malloc(sizeof(stack));
    if (vstack == NULL) {
        perror("Failed to create stack");
        return NULL;
    }
    vstack->top = -1;
    vstack->max_size = stackSize;
    vstack->instorage = (char**)malloc(stackSize * sizeof(char*));
    if (vstack->instorage == NULL) {
        perror("Failed to allocate stack storage");
        free(vstack);
        return NULL;
    }
    return vstack;
}

int pushstack(stack *vstack, const char *p) {
    if (vstack->top + 1 == vstack->max_size) {
        printf("Stack is full.\n");
        return 0;
    }
    vstack->top++;
    vstack->instorage[vstack->top] = (char*)malloc(strlen(p) + 1);
    if (vstack->instorage[vstack->top] == NULL) {
        perror("Failed to allocate memory for stack element");
        return 0;
    }
    strcpy(vstack->instorage[vstack->top], p);
    vstack->count++;
    return 1;
}

int popstack(stack *vstack, char *dp) {
    if (vstack->top == -1) {
        printf("Stack is empty.\n");
        return 0;
    }
    strcpy(dp, vstack->instorage[vstack->top]);
    free(vstack->instorage[vstack->top]);  // Free allocated memory
    vstack->top--;
    vstack->count--;
    return 1;
}

void freestack(stack *s) {
    while (s->top != -1) {
        free(s->instorage[s->top]);
        s->top--;
    }
    free(s->instorage);
    free(s);
}

int isstackfull(stack* vstack) {
    return vstack->top + 1 == vstack->max_size;
}

int isstackempty(stack *vstack) {
    return vstack->top == -1;
}

void displayStack(stack *Mystack) {
    int t = Mystack->top;
    printf("***TOP***\n");
    for (int i = t; i != -1; i--) {
        printf("%s\n", Mystack->instorage[i]);
    }
    printf("**END**\n");
}

// Parsing Functions
char* takein(char *p, char *s) {
    while (*s != '(') {
        s++;
    }
    s++;  // Skip '('
    int i = 0;
    while (*s != ',' && *s != ')') {
        p[i++] = *s++;
    }
    p[i] = '\0';
    return (*s == ')') ? NULL : s;
}

char* GateExt(char *str, char *p) {
    while (*str == ',' || *str == ' ') {
        str++;
    }
    int i = 0;
    while (*str != ',' && *str != ')' && *str != ' ') {
        p[i++] = *str++;
    }
    p[i] = '\0';
    return (*str == ')') ? NULL : str;
}

int strequal(const char *s1, const char *s2) {
    return strcmp(s1, s2) == 0;
}

int Is_Input(char* s, char p[][10], int size) {
    char cgate[10];
    char *check = takein(cgate, s);
    int flag = 0;
    for (int i = 0; i < size; i++) {
        if (strequal(cgate, p[i])) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        return 0;
    } else if (check == NULL) {
        return 1;
    } else {
        while (check != NULL) {
            flag = 0;
            check = GateExt(check, cgate);
            for (int i = 0; i < size; i++) {
                if (strequal(cgate, p[i])) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                return 0;
            }
        }
    }
    return 1;
}

int vis(const char* p) {
    for (int i = 0; i < vcount; i++) {
        if (strequal(p, v[i])) {
            return 1;
        }
    }
    return 0;
}

void AddToVis(const char* p) {
    if (vcount < MAX_SIZE) {
        strcpy(v[vcount++], p);
    } else {
        printf("Visibility array is full.\n");
    }
}

void DFS(const char* a, FILE *rf, stack *MyStack) {
    fseek(rf, 0, SEEK_SET);
    char s[50] = {0};
    while (fgets(s, sizeof(s), rf) != NULL) {
        s[strcspn(s, "\n")] = '\0';
        int flag = 0;
        char g[10];
        GateExt(s, g);
        char p[10];
        char *ptr = takein(p, s);
        if (strcmp(p, a) == 0) {
            flag = 1;
        } else if (ptr != NULL) {
            while (ptr != NULL) {
                ptr = GateExt(ptr, p);
                if (strcmp(p, a) == 0) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 1 && !vis(g)) {
            DFS(g, rf, MyStack);
            AddToVis(g);
            pushstack(MyStack, g);
            fseek(rf, 0, SEEK_SET);
        }
    }
}

// Probability functions
float pOfAND(float pi1, float pi2) {
    return pi1 * pi2;
}

float pOfNAND(float pi1, float pi2) {
    return 1.0f - (pi1 * pi2);
}

float pOfNOT(float p1) {
    return 1.0f - p1;
}

float pOfOR(float pi1, float pi2) {
    return 1.0f - ((1.0f - pi1) * (1.0f - pi2));
}

float pOfNOR(float pi1, float pi2) {
    return 1.0f - ((1.0f - pi1) * (1.0f - pi2));
}

float pOfXOR(float pi1, float pi2) {
    return (1.0f - pi1) * pi2 + pi1 * (1.0f - pi2);
}

float pOfXNOR(float pi1, float pi2) {
    return 1.0f - ((1.0f - pi1) * pi2 + pi1 * (1.0f - pi2));
}

float pOfBUFF(float pi1) {
    return pi1;
}

// Determines gate type and calculates probability
float gateDeter(char *s, float f1, float f2) {
    while (*s != '=') s++;
    s += 2;  // Skip "= "
    
    char g[7];
    int i = 0;
    while (*s != '(') {
        g[i++] = *s++;
    }
    g[i] = '\0';
    
    if (strcmp(g, "AND") == 0) {
        return pOfAND(f1, f2);
    } else if (strcmp(g, "OR") == 0) {
        return pOfOR(f1, f2);
    } else if (strcmp(g, "NOT") == 0) {
        return pOfNOT(f1);
    } else if (strcmp(g, "NAND") == 0) {
        return pOfNAND(f1, f2);
    } else if (strcmp(g, "XOR") == 0) {
        return pOfXOR(f1, f2);
    } else if (strcmp(g, "NOR") == 0) {
        return pOfNOR(f1, f2);
    } else if (strcmp(g, "XNOR") == 0) {
        return pOfXNOR(f1, f2);
    } else if (strcmp(g, "BUFF") == 0) {
        return pOfBUFF(f1);
    }
    
    return 0.0f;  // Default return value
}

// Computes probability based on gate configuration
float probability(char *p, struct GateInfo GI[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(p, GI[i].name) == 0) {
            return GI[i].p;
        }
    }
    return 0.0f;  // Default probability
}

// Computes probability of a gate's output
float Dprobab(char *s, int n, struct GateInfo GI[]) {
    char *check;
    char g1[10];
    char g2[10];
    
    check = takein(g1, s);
    if (check != NULL) {
        float f = probability(g1, GI, n);
        while (check != NULL) {
            check = GateExt(check, g2);
            if (check == NULL) break;
            f = gateDeter(s, f, probability(g2, GI, n));
        }
        return f;
    } else {
        return gateDeter(s, probability(g1, GI, n), 0.0f);
    }
}

int main() {
    stack *MyStack = createCharStack(MAX_SIZE);

    struct GateInfo GI[MAX_SIZE];
    int count = 0;

    FILE *ptr = fopen("c432.bench", "r");
    if (ptr == NULL) {
        perror("Error opening file");
        return 1;
    }

    char s[50];
    fgets(s, 40, ptr);
    int max = 0;
    while (strstr(s, "OUTPUT") == NULL && strstr(s, "INPUT") != NULL) {
        max++;
        fgets(s, 40, ptr);
    }

    fseek(ptr, 0, SEEK_SET);
    int In_Size = max;
    char pIn[max][10];
    fgets(s, 40, ptr);
    int i = 0;
    while (strstr(s, "OUTPUT") == NULL && strstr(s, "INPUT") != NULL) {
        takein(pIn[i], s);
        i++;
        fgets(s, 40, ptr);
    }

    fseek(ptr, 0, SEEK_SET);
    while (strstr(s, "INPUT") != NULL) {
        fgets(s, 40, ptr);
    }

    fgets(s, 40, ptr);
    while (strstr(s, "OUTPUT") != NULL) {
        fgets(s, 40, ptr);
    }

    FILE *rf = fopen("relationfile.txt", "w");
    while (fgets(s, 40, ptr) != NULL) {
        fputs(s, rf);
    }
    fclose(rf);
    fclose(ptr);

    rf = fopen("relationfile.txt", "r");
    while (fgets(s, 40, rf) != NULL) {
        char p[10];
        GateExt(s, p);
        if (Is_Input(s, pIn, In_Size) && !vis(p)) {
            DFS(p, rf, MyStack);
            AddToVis(p);
            pushstack(MyStack, p);
            fseek(rf, 0, SEEK_SET);
        }
    }

    FILE *result = fopen("result.txt", "w");
    fprintf(result, "{");
    int k;
    for (k = 0; k < In_Size; k++) {
        strcpy(GI[k].name, pIn[k]);
        count++;
        GI[k].p = 0.5;
        fprintf(result, "'%s': [0.5, 0.5], ", pIn[k]);
    }

    fseek(rf, 0, SEEK_SET);
    char data[10];
    while (!isstackempty(MyStack)) {
        char *check;
        char p1[10];
        popstack(MyStack, data);
        strcpy(GI[k].name, data);
        count++;
        check = fgets(s, 40, rf);
        GateExt(s, p1);
        while (!strequal(p1, data) && check != NULL) {
            check = fgets(s, 40, rf);
            GateExt(s, p1);
        }
        GI[k].p = Dprobab(s, k, GI);
        fprintf(result, "'%s': [%f, %f]", GI[k].name, 1.0 - GI[k].p, GI[k].p);
        if (!isstackempty(MyStack)) {
            fprintf(result, ", ");
        }
        k++;
        fseek(rf, 0, SEEK_SET);
    }
    fprintf(result, "}");
    fclose(result);
    fclose(rf);
    freestack(MyStack);

    return 0;
}
