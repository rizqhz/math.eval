#pragma once

#include <cmath>

namespace machine {

char Tape[50];  /* Pita untuk inputan mesin */
char CC;        /* Current Character */
int  CI;        /* Current Index */
bool EOT;       /* End of Tape */

/* Memulai mesin dengan inputan pita dari awal. */
void start() {
    CI  = 0;
    CC  = Tape[CI];
    EOT = CC == ';';
}

/* Menunjuk ke karakter selanjutnya dari pita. */
void next() {
    CI  = CI + 1;
    CC  = Tape[CI];
    EOT = CC == ';';
}

/* Menguji karakter digit angka yang terdapat di pita. */
bool isDigit() {
    return '0' <= CC and CC <= '9';
}

/* Mendapatkan digit angka dari pita. */
int getDigit() {
    int number = 0;
    while (isDigit()) {
        number = 10 * number + (CC - 48);
        next();
    }
    return number;
}

/* Menguji karakter operator yang terdapat di pita. */
bool isOperator() {
    return CC == '+' or CC == '-' or CC == '*' or
           CC == '/' or CC == '%' or CC == '^';
}

/* Menguji karakter kurung buka/tutup yang terdapat di pita. */
bool isParenthesis() {
    return CC == '(' or CC == ')';
}

/* Mendapatkan tingkat operator aritmatika. */
int level(char op) {
    switch (op) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '%': return 2;
        case '^': return 3;
    }
    return 0;
}

/* Melakukan operasi aritmatika. */
int operation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '%': return a % b;
        case '^': return pow(a, b);
    }
    return 0;
}

}
