#include <iostream>
#include "lib/machine.hpp"
#include "lib/stack.hpp"

/* Fungsi untuk mengkalkulasi nilai yang terdapat di dalam 
   stack nilai dengan operator yang terdapat di dalam stack 
   operator. */
void calculate(Stack &values, Stack &operators) {
    char op = stack::pop(operators);
    int v2 = stack::pop(values);
    int v1 = stack::pop(values);
    std::cout << char(195) << char(196) << char(196) << char(196)
              << ' ' << v1 << ' ' << op << ' ' << v2 << '\n';
    stack::push(values, machine::operation(v1, v2, op));
}

int main(int argc, char const *argv[]) {
    /* Inputan berupa ekspresi aritmatika yang akan dimasukkan
       ke dalam pita. */
    std::cout << char(218) << char(196) << " Ekspresi Aritmatika : ";
    std::cin.getline(machine::Tape, 50);
    /* Membuat dua stack untuk menampung nilai dan operator
       aritmatika. */
    Stack values, operators;
    /* Memulai mesin dengan keadaan penunjuk karakter (CC) 
       menunjuk ke awal pita. */
    machine::start();
    /* Memulai membaca pita sampai penunjuk karakter (CC) sama
       dengan titik koma atau sampai menunjuk ke akhir pita. */
    while (not machine::EOT) {
        /* Jika penunjuk karakter (CC) sama dengan digit angka
           maka dapatkan digit angka tersebut sampai penunjuk 
           karakter tidak sama dengan digit angka. Lalu digit 
           angka tersebut simpan ke dalam stack nilai. */
        if (machine::isDigit()) {
            stack::push(values, machine::getDigit());
        }
        /* Jika penunjuk karakter (CC) sama dengan operator 
           aritmatika dan stack operator tidak kosong maka 
           lakukan kalkulasi terlebih dahulu apabila operator 
           yang terdapat di stack lebih tinggi tingkatnya 
           dibanding dengan operator yang sedang ditunjuk oleh 
           karakter penunjuk (CC). Setelah itu simpan operator 
           yang ditunjuk oleh penunjuk karakter ke dalam stack 
           operator. */
        else if (machine::isOperator()) {
            int op[2];
            while (not stack::isEmpty(operators)) {
                op[0] = machine::level(stack::peek(operators));
                op[1] = machine::level(machine::CC);
                if (op[0] >= op[1]) {
                    calculate(values, operators);
                } else {
                    break;
                }
            }
            stack::push(operators, machine::CC);
            machine::next();
        }
        /* Jika penunjuk karakter (CC) sama dengan parenthesis 
           atau kurung buka/tutup, maka lakukan proses sesuai 
           kondisi masing-masing. */
        else if (machine::isParenthesis()) {
            switch (machine::CC) {
                /* Jika penunjuk karakter (CC) sama dengan 
                   kurung buka '(', maka simpan ke dalam stack 
                   operator. */
                case '(': {
                    stack::push(operators, machine::CC);
                    machine::next();
                    break;
                }
                /* Jika penunjuk karakter (CC) sama dengan 
                   kurung tutup ')', maka lakukan proses 
                   kalkulasi sampai operator di stack sama 
                   dengan kurung buka '('. Setelah itu hapus
                   kurung buka tersebut. */
                case ')': {
                    while (stack::peek(operators) != '(') {
                        calculate(values, operators);
                    }
                    stack::pop(operators);
                    machine::next();
                    break;
                }
            }
        }
        /* Jika kondisi di atas tidak terpenuhi, dengan kata lain 
           penunjuk karakter (CC) tidak sama dengan digit angka, 
           operator, ataupun titik koma, maka penunjuk karakter 
           menunjuk ke karakter selanjutnya di dalam pita. */
        else machine::next();
    }
    /* Setelah pembacaan pita, maka lakukan proses kalkulasi dengan 
       nilai dan operator yang terdapat di stack sampai stack 
       operator kosong. */
    while (not stack::isEmpty(operators)) {
        calculate(values, operators);
    }
    /* Output dari hasil evaluasi */
    std::cout << char(192) << char(196) << " Hasil Evaluasi : "
              << stack::peek(values) << '\n';
    std::cin.get();
    return 0;
}
