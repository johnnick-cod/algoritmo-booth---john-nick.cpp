#include <iostream>
#include <string>

using namespace std;

// decimal para binario
string binario(int num, int bits) {
    string r = "";

    if (num < 0) {
        num = (1 << bits) + num;
    }

    for (int i = bits - 1; i >= 0; i--) {
        if ((num >> i) & 1) {
            r = r + "1";
        } else {
            r = r + "0";
        }
    }

    return r;
}
// binario para decimal
int decimal(string b) {
    int valor = 0;
    int bits = b.length();

    for (int i = 0; i < bits; i++) {
        if (b[i] == '1') {
            valor = valor * 2 + 1;
        } else {
            valor = valor * 2;
        }
    }

    if (b[0] == '1') {
        valor = valor - (1 << bits);
    }

    return valor;
}
// soma de dois binarios
string soma(string a, string b, int bits) {

    int x = decimal(a);
    int y = decimal(b);

    int resultado = x + y;

    return binario(resultado, bits);
}

// deslocamento para direita
void desloca(string &A, string &Q, char &q1, int bits) {

    char sinal = A[0];
    char ultimoA = A[bits - 1];
    char ultimoQ = Q[bits - 1];

    // desloca Q
    for (int i = bits - 1; i > 0; i--) {
        Q[i] = Q[i - 1];
    }

    Q[0] = ultimoA;

    // desloca A
    for (int i = bits - 1; i > 0; i--) {
        A[i] = A[i - 1];
    }

    A[0] = sinal;

    q1 = ultimoQ;
}

int main() {

    int M, Qnum;
    int bits = 4;

    cout << "Multiplicando (4 bits): ";
    cin >> M;

    cout << "Multiplicador (4 bits): ";
    cin >> Qnum;

    string Mbin = binario(M, bits);
    string menosM = binario(-M, bits);

    string A = "0000";
    string Q = binario(Qnum, bits);

    char q1 = '0';

    cout << "\n----- ALGORITMO DE BOOTH -----\n";

    cout << "M = " << Mbin << endl;
    cout << "Q = " << Q << endl;

    cout << "\nInicial:\n";
    cout << "A = " << A << "   Q = " << Q << "   Q-1 = " << q1 << endl;

    for (int i = 1; i <= bits; i++) {

        char q0 = Q[bits - 1];

        cout << "\nPasso " << i << endl;

        if (q0 == '0' && q1 == '1') {
            A = soma(A, Mbin, bits);
            cout << "A = A + M" << endl;
        }
        else if (q0 == '1' && q1 == '0') {
            A = soma(A, menosM, bits);
            cout << "A = A - M" << endl;
        }
        else {
            cout << "Nenhuma operacao" << endl;
        }

        cout << "Antes deslocar:" << endl;
        cout << "A = " << A << "   Q = " << Q << "   Q-1 = " << q1 << endl;

        desloca(A, Q, q1, bits);

        cout << "Depois deslocar:" << endl;
        cout << "A = " << A << "   Q = " << Q << "   Q-1 = " << q1 << endl;
    }

    cout << "\nResultado final:" << endl;
    cout << "Binario = " << A << Q << endl;
    cout << "Decimal = " << decimal(A + Q) << endl;

    return 0;
}
