#include <iostream>
#include <limits>
using namespace std;

struct especie {
    string nombre;
    int fortaleza;
    double ataque;
    double salud;
    double rapidez;
};

struct personaje {
    string especie;
    string nombre;
};

struct implemento {
    string nombre;
    string tipo;
    int usos;
    int fortaleza;
    double valorAtk;
    double valorDef;
    double valorHeal;
};

struct magia {
    string nombre;
    string funcion;
};

struct mapa {
    int sala;
    int distancia;
    int adyacencias;
    int cantOrcos;
};

int leerOpcion() {
    int op;
    while (true) {
        cin >> op;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida. Por favor ingresa un numero valido: ";
        } else {
            return op;
        }
    }
}

void verSubMenuModificar() {
    int op;
    cout<<"\n-- Modificar Elemento --"<<endl;
    cout<<"1. Personajes"<<endl;
    cout<<"2. Implementos"<<endl;
    cout<<"3. Equipos "<<endl;
    cout<<"4. Mochilas"<<endl;
    cout<<"5. Mapa"<<endl;
    cout<<"6. Volver al menu principal"<<endl;
    cout<<"Seleccione una opcion: ";
    op=leerOpcion();

    switch (op) {
        case 1:
            cout<<"Ingresando a la modificacion de personajes..."<<endl;
            break;
        case 2:
            cout<<"Ingresando a la modificacion de implementos..."<<endl;
            break;
        case 3:
            cout<<"Ingresando a la modificacion de equipos..."<<endl;
            break;
        case 4:
            cout<<"Ingresando a la modificacion de mochilas..."<<endl;
            break;
        case 5:
            cout<<"Ingresando a la modificacion de mapas..."<<endl;
            break;
        case 6:
            return;
    }
} 

void verSubMenuEliminar() {
    int op;
    cout<<"\n-- Eliminar Elemento --"<<endl;
    cout<<"1. Personajes"<<endl;
    cout<<"2. Implementos"<<endl;
    cout<<"3. Equipos "<<endl;
    cout<<"4. Mochilas"<<endl;
    cout<<"5. Mapa"<<endl;
    cout<<"6. Volver al menu principal"<<endl;
    cout<<"Seleccione una opcion: ";
    op=leerOpcion();

    switch (op) {
        case 1:
            cout<<"Ingresando a la eliminacion de personajes..."<<endl;
            break;
        case 2:
            cout<<"Ingresando a la eliminacion de implementos..."<<endl;
            break;
        case 3:
            cout<<"Ingresando a la eliminacion de equipos..."<<endl;
            break;
        case 4:
            cout<<"Ingresando a la eliminacion de mochilas..."<<endl;
            break;
        case 5:
            cout<<"Ingresando a la eliminacion de mapas..."<<endl;
            break;
        case 6:
            return;
    }
} 

void verSubMenuAgregar() {
    int op;
    cout<<"\n-- Crear Elemento --"<<endl;
    cout<<"1. Personajes"<<endl;
    cout<<"2. Implementos"<<endl;
    cout<<"3. Equipos "<<endl;
    cout<<"4. Mochilas"<<endl;
    cout<<"5. Mapa"<<endl;
    cout<<"6. Volver al menu principal"<<endl;
    cout<<"Seleccione una opcion: ";
    op=leerOpcion();

    switch (op) {
        case 1:
            cout<<"Ingresando a la creacion de personajes..."<<endl;
            break;
        case 2:
            cout<<"Ingresando a la creacion de implementos..."<<endl;
            break;
        case 3:
            cout<<"Ingresando a la creacion de equipos..."<<endl;
            break;
        case 4:
            cout<<"Ingresando a la creacion de mochilas..."<<endl;
            break;
        case 5:
            cout<<"Ingresando a la creacion de mapas..."<<endl;
            break;
        case 6:
            return;
    }
} 

void verSubMenuInformacion() {
    int op;
    cout<<"\n__Ver Informacion__"<<endl;
    cout<<"1. Personajes/Especies"<<endl;
    cout<<"2. Implementos"<<endl;
    cout<<"3. Equipos (Soldados)"<<endl;
    cout<<"4. Mochilas" << endl;
    cout<<"5. Mapas" << endl;
    cout<<"6. Equipos completos y mochilas"<<endl;
    cout<<"7. Resultados de Misiones"<<endl;
    cout<<"8. Bitacora"<<endl;
    cout<<"9. Volver al menu principal"<<endl;
    cout<<"Seleccione una opcion: ";
    op=leerOpcion();

    switch (op) {
        case 1:
            cout<<"Mostrando Personajes/Especies..."<<endl;
            break;
        case 2:
            cout<<"Mostrando Implementos..."<<endl;
            break;
        case 3:
            cout<<"Mostrando Equipos..."<<endl;
            break;
        case 4:
            cout<<"Mostrando Mochilas..."<<endl;
            break;
        case 5:
            cout<<"Mostrando Mapas..."<<endl;
            break;
        case 6:
            cout<<"Mostrando equipos y mochilas..."<<endl;
            break;
        case 7:
            cout<<"Mostrando resultados de misiones..."<<endl;
            break;
        case 8:
            cout<<"Mostrando bitacora..."<<endl;
            break;
        case 9:
            return;
    }
}

int main() {
    int op = 0;

    do {
        // Menú principal
        cout<<"\n___Bienvenido a Khazad-Dum___"<<endl;
        cout<<"____Menu de Interacciones____"<<endl;
        cout<<"1. Ver Informacion"<<endl;
        cout<<"2. Crear Elemento"<<endl;
        cout<<"3. Eliminar Elemento"<<endl;
        cout<<"4. Modificar Elemento"<<endl;
        cout<<"5. Visualizar Mapa"<<endl;
        cout<<"6. Salir";
        cout<<"______________________"<<endl;
        cout<<"Selecciona una opcion: "<<endl;
        op=leerOpcion();;

        switch (op) {
            case 1:
                verSubMenuInformacion();
                break;
            case 2:
                verSubMenuAgregar();
                break;
            case 3:
                verSubMenuEliminar();
                break;
            case 4:
                verSubMenuModificar();
                break;
            case 5:
                cout<<"[Visualizar Mapa] en desarrollo..."<<endl;
                break;
            case 6:
                cout<<"Saliendo del programa..."<<endl;
                return 0;
        
        }
    }while (op != 6);

    return 0;
}
