#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct P {
    string n, a, m;
    int nt;
};

void ingresar() {
    ofstream a("Personas.txt", ios::app);

    if (!a) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    while (true) {
        P p;

        cout << "Ingrese el nombre (ingrese '0' para terminar): ";
        cin >> p.n;

        if (p.n == "0") {
            break;
        }

        cout << "Ingrese los apellidos: ";
        cin >> p.a;

        cout << "Ingrese la materia: ";
        cin.ignore();
        getline(cin, p.m);

        cout << "Ingrese la nota de la materia: ";
        string ni;
        cin >> ni;

        stringstream ns(ni);
        ns >> p.nt;

        a << p.n << ";" << p.a << ";" << p.m << ";" << p.nt << "\n";

        cout << "Datos almacenados correctamente en el archivo.\n";
    }

    a.close();
}

void leer(vector<P>& p) {
    ifstream a("Personas.txt");

    if (!a) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    p.clear();

    while (a) {
        P e;
        getline(a, e.n, ';');
        getline(a, e.a, ';');
        getline(a, e.m, ';');
        a >> e.nt;
        a.ignore();

        if (!a.eof()) {
            p.push_back(e);
        }
    }

    cout << "Datos leídos del archivo y almacenados en el vector.\n";

    a.close();
}

void imprimir(const vector<P>& p) {
    cout << "Datos almacenados:\n";

    for (const auto& e : p) {
        cout << "Nombre: " << e.n << "\n";
        cout << "Apellidos: " << e.a << "\n";
        cout << "Materia: " << e.m << "\n";
        cout << "Nota: " << e.nt << "\n";
        cout << "---------------------------\n";
    }
}

int main() {
    vector<P> p;

    ingresar();
    leer(p);
    imprimir(p);

    return 0;
}
