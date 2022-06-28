#pragma once

/* Struktur stack. */
struct Stack {
    int top = -1;
    int data[50];
};

namespace stack {

/* Fungsi untuk menguji apakah stack kosong atau tidak. */
bool isEmpty(const Stack &stack) {
    return stack.top == -1;
}

/* Fungsi untuk menguji apakah stack penuh atau tidak. */
bool isFull(const Stack &stack) {
    return stack.top + 1 == 50;
}

/* Fungsi untuk menambahkan data ke dalam stack. */
void push(Stack &stack, const int &value) {
    if (not isFull(stack)) {
        stack.top = stack.top + 1;
        stack.data[stack.top] = value;
    }
}

/* Fungsi untuk menghapus data dari stack. */
int pop(Stack &stack) {
    if (not isEmpty(stack)) {
        return stack.data[stack.top--];
    }
    return 0;
}

/* Fungsi untuk mengambil data teratas dalam stack. */
int peek(Stack &stack) {
    if (not isEmpty(stack)) {
        return stack.data[stack.top];
    }
    return 0;
}

/* Fungsi untuk membersihkan stack. */
void clear(Stack &stack) {
    if (not isEmpty(stack)) {
        stack.top = -1;
    }
}

}
