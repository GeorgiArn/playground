#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]);
void push(double f);
double pop();
void top();
void swap();
void duplicate();
void clear();

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) push(pop() / op2);
                else printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0) push((int) pop() % (int) op2);
                else printf("error: zero divisor\n");
                break;
            case '&':
                push(sin(pop()));
                break;
            case '^':
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case 'e':
                push(exp(pop()));
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            case 't':
                top();
                break;
            case 'd':
                duplicate();
                break;
            case 's':
                swap();
                break;
            case 'c':
                clear();
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL) val[sp++] = f;
    else printf("error: stack full can't push %g\n", f);
}

double pop() {
    if (sp == 0) {
        printf("erorr: stack empty\n");
        return 0.0;
    }

    return val[--sp];
}

void top() {
    if (sp == 0) {
        printf("erorr: stack empty\n");
    } else {
        printf("\t%.8g\n", val[sp]);
    }
}

void swap() {
    double a = pop();
    double b = pop();

    push(a);
    push(b);
}

void duplicate() {
    double a = pop();

    push(a);
    push(a);
}

void clear() {
    do {
        val[sp] = 0.0;
    } while (sp--);
}

int getch();
void ungetch(int c);
int isnum(char c);

int getop(char s[]) {
    int i, c, prev;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    i = 0;

    if (!isnum(c) && c != '-') {
        return c;
    } else if (c == '-') {
        prev = c;
        c = getch();

        int cond = !isnum(c);

        ungetch(c);

        if (cond) return prev;
    }

    if (isdigit(c)) while (isdigit(s[++i] = c = getch()));
    if (c == '.') while (isdigit(s[++i] = c = getch()));

    s[i] = '\0';

    if (c != EOF) ungetch(c);

    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch() {
    return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) printf("ungetch: too many characters\n");
    else buf[bufp++] = c;
}

int isnum(char c) {
    return isdigit(c) || c == '.';
}