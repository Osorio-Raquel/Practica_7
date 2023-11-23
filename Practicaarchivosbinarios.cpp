#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

const char EF[] = "Estudiantes.bin";
const char NF[] = "Notas.bin";

struct S {
    char c[10];
    char n[30];
    char a[30];
};

struct N {
    char c[10];
    char m[30];
    int nt;
};

void ie() {
    ofstream f(EF, ios::binary | ios::app);

    if (!f) {
        cout << "Error al abrir el archivo de estudiantes.\n";
        return;
    }

    S e;

    cout << "Ingreso de datos de estudiantes (Ingrese '0' en CI para terminar):\n";

    while (true) {
        cout << "CI: ";
        cin >> e.c;

        if (strcmp(e.c, "0") == 0) {
            break;
        }

        cout << "Nombres: ";
        cin.ignore();
        cin.getline(e.n, sizeof(e.n));

        cout << "Apellidos: ";
        cin.getline(e.a, sizeof(e.a));

        f.write(reinterpret_cast<char*>(&e), sizeof(S));

        cout << "Estudiante registrado correctamente.\n";
    }

    f.close();
}

void in() {
    ifstream ef(EF, ios::binary);

    if (!ef) {
        cout << "Error al abrir el archivo de estudiantes.\n";
        return;
    }

    ofstream nf(NF, ios::binary | ios::app);

    if (!nf) {
        cout << "Error al abrir el archivo de notas.\n";
        ef.close();
        return;
    }

    N n;
    S e;

    cout << "Ingreso de notas (Ingrese '0' en CI para terminar):\n";

    while (true) {
        cout << "CI del estudiante: ";
        cin >> n.c;

        if (strcmp(n.c, "0") == 0) {
            break;
        }

        bool ee = false;

        ef.clear();
        ef.seekg(0, ios::beg);

        while (ef.read(reinterpret_cast<char*>(&e), sizeof(S))) {
            if (strcmp(n.c, e.c) == 0) {
                ee = true;
                break;
            }
        }

        if (!ee) {
            cout << "El estudiante no existe. Ingrese un CI válido o '0' para terminar.\n";
            continue;
        }

        cout << "Materia: ";
        cin.ignore();
        cin.getline(n.m, sizeof(n.m));

        cout << "Nota: ";
        cin >> n.nt;

        nf.write(reinterpret_cast<char*>(&n), sizeof(N));

        cout << "Nota registrada correctamente.\n";
    }

    ef.close();
    nf.close();
}

void ren() {
    ifstream ef(EF, ios::binary);
    ifstream nf(NF, ios::binary);

    if (!ef || !nf) {
        cout << "Error al abrir uno o más archivos.\n";
        return;
    }

    S e;
    N n;

    cout << "Reporte de estudiantes y notas:\n";

    while (ef.read(reinterpret_cast<char*>(&e), sizeof(S))) {
        cout << "CI: " << e.c << endl;
        cout << "Nombres: " << e.n << endl;
        cout << "Apellidos: " << e.a << endl;

        nf.clear();
        nf.seekg(0, ios::beg);

        bool ne = false;

        while (nf.read(reinterpret_cast<char*>(&n), sizeof(N))) {
            if (strcmp(n.c, e.c) == 0) {
                cout << "Materia: " << n.m << " - Nota: " << n.nt << endl;
                ne = true;
            }
        }

        if (!ne) {
            cout << "No hay notas registradas para este estudiante.\n";
        }

        cout << "-----------------------------\n";
    }

    ef.close();
    nf.close();
}

int main() {
    int o;

    do {
        cout << "\nMenú:\n";
        cout << "1. Ingreso de datos de estudiantes\n";
        cout << "2. Ingreso de materias y notas\n";
        cout << "3. Reporte de estudiantes y notas ingresadas\n";
        cout << "4. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> o;

        switch (o) {
            case 1:
                ie();
                break;

            case 2:
                in();
                break;

            case 3:
                ren();
                break;

            case 4:
                cout << "Saliendo del programa. Hasta luego.\n";
                break;

            default:
                cout << "Opción no válida. Inténtelo de nuevo.\n";
                break;
        }

    } while (o != 4);

    return 0;
}
