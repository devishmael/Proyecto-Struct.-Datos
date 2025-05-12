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

struct nodoEspecie {
    especie dato;
    nodoEspecie* siguiente;
};

struct personaje {
    string nombre;
    personaje * siguiente;
    especie * tipoEspecie;
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

// Punteros principales a listas
personaje * listaPersonajes = nullptr;
implemento * listaImplementos = nullptr;
mapa * listaMapas = nullptr;

int leerOpcion();

class listaEspecies {
private:
    nodoEspecie* cabeza;

public:
    listaEspecies() {
        cabeza = nullptr;
    }

    nodoEspecie* getCabeza() {
        return cabeza;
    }

    void agregarEspecie() {
        cin.ignore();
        especie nuevaEspecie;
        string tipo;

        cout << "Ingrese el nombre de la especie: ";
        getline(cin, nuevaEspecie.nombre);

        while (true) {
            cout << "La especie es un Heroe o un Orco? (H/O): ";
            getline(cin, tipo);

            if (tipo == "h" || tipo == "H") {
                cout << "Ingrese la fortaleza del heroe: ";
                while (!(cin >> nuevaEspecie.fortaleza)) {
                    cout << "Numero invalido. Intenta de nuevo: ";
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                nuevaEspecie.ataque = 0;
                break;
            } else if (tipo == "o" || tipo == "O") {
                cout << "Ingrese el ataque del orco: ";
                while (!(cin >> nuevaEspecie.ataque)) {
                    cout << "Numero invalido. Intenta de nuevo: ";
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                nuevaEspecie.fortaleza = 0;
                break;
            } else {
                cout << "Opción inválida. Intenta de nuevo.\n";
            }
        }

        cout << "Ingrese la salud de la especie: ";
        while (!(cin >> nuevaEspecie.salud)) {
            cout << "Numero invalido. Intenta de nuevo: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Ingrese la rapidez de la especie: ";
        while (!(cin >> nuevaEspecie.rapidez)) {
            cout << "Numero invalido. Intenta de nuevo: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        nodoEspecie* nuevoNodo = new nodoEspecie;
        nuevoNodo->dato = nuevaEspecie;
        nuevoNodo->siguiente = nullptr;

        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            nodoEspecie* temp = cabeza;
            while (temp->siguiente != nullptr) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoNodo;
        }

        cout << "Especie '" << nuevaEspecie.nombre << "' agregada." << endl;
    }

    void mostrarEspecie() {
        if (cabeza == nullptr) {
            cout << "No hay especies registradas." << endl;
            return;
        }

        cout << "\n=== HÉROES ===\n";
        nodoEspecie* temp = cabeza;
        while (temp != nullptr) {
            if (temp->dato.fortaleza > 0) {
                cout << "Especie: " << temp->dato.nombre << endl;
                cout << "Fortaleza: " << temp->dato.fortaleza << endl;
                cout << "Salud: " << temp->dato.salud << endl;
                cout << "Rapidez: " << temp->dato.rapidez << endl << endl;
            }
            temp = temp->siguiente;
        }

        cout << "\n=== ORCOS ===\n";
        temp = cabeza;
        while (temp != nullptr) {
            if (temp->dato.ataque > 0) {
                cout << "Especie: " << temp->dato.nombre << endl;
                cout << "Ataque: " << temp->dato.ataque << endl;
                cout << "Salud: " << temp->dato.salud << endl;
                cout << "Rapidez: " << temp->dato.rapidez << endl << endl;
            }
            temp = temp->siguiente;
        }
    }

    nodoEspecie* seleccionarEspeciePorIndice() {
        if (!cabeza) {
            cout << "No hay especies registradas.\n";
            return nullptr;
        }

        cout << "\n=== Especies disponibles ===\n";
        nodoEspecie* temp = cabeza;
        int i = 1;
        while (temp) {
            cout << i << ". " << temp->dato.nombre << endl;
            temp = temp->siguiente;
            i++;
        }

        int seleccion;
        cout << "Seleccione el número de la especie: ";
        seleccion = leerOpcion();

        temp = cabeza;
        for (int j = 1; temp && j < seleccion; j++) {
            temp = temp->siguiente;
        }

        if (!temp) {
            cout << "Selección inválida.\n";
            return nullptr;
        }

        return temp;
    }

    void eliminarEspecie() {
        nodoEspecie* seleccionada = seleccionarEspeciePorIndice();
        if (!seleccionada) return;

        nodoEspecie* actual = cabeza;
        nodoEspecie* anterior = nullptr;

        while (actual) {
            if (actual == seleccionada) {
                if (!anterior) cabeza = actual->siguiente;
                else anterior->siguiente = actual->siguiente;
                delete actual;
                cout << "Especie eliminada exitosamente.\n";
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }

        cout << "Error inesperado: no se encontró la especie.\n";
    }

    void modificarEspecie() {
        nodoEspecie* seleccionada = seleccionarEspeciePorIndice();
        if (!seleccionada) return;

        especie& esp = seleccionada->dato;
        cin.ignore();
        cout << "Nuevo nombre de la especie: ";
        getline(cin, esp.nombre);

        string tipo;
        while (true) {
            cout << "¿Será un Héroe o un Orco? (H/O): ";
            getline(cin, tipo);
            if (tipo == "H" || tipo == "h") {
                cout << "Nueva fortaleza: ";
                cin >> esp.fortaleza;
                esp.ataque = 0;
                break;
            } else if (tipo == "O" || tipo == "o") {
                cout << "Nuevo ataque: ";
                cin >> esp.ataque;
                esp.fortaleza = 0;
                break;
            } else {
                cout << "Opción inválida. Intenta de nuevo.\n";
            }
        }

        cout << "Nueva salud: ";
        cin >> esp.salud;

        cout << "Nueva rapidez: ";
        cin >> esp.rapidez;

        cout << "Especie modificada exitosamente.\n";
    }
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

void agregarPersonaje(listaEspecies& lista) {
    personaje* nuevo = new personaje();
    cout << "Nombre del personaje: ";
    cin.ignore();
    getline(cin, nuevo->nombre);

    string tipo;
    while (true) {
        cout << "¿El personaje será un Héroe o un Orco? (H/O): ";
        cin >> tipo;
        if (tipo == "H" || tipo == "h" || tipo == "O" || tipo == "o") break;
        else cout << "Opción inválida. Intenta de nuevo.\n";
    }

    // Mostrar solo especies del tipo correspondiente
    cout << "\nEspecies disponibles:\n";
    nodoEspecie* actual = lista.getCabeza();
    int contador = 0;

    while (actual != nullptr) {
        if ((tipo == "H" || tipo == "h") && actual->dato.fortaleza > 0) {
            cout << "- " << actual->dato.nombre << " (Héroe)\n";
            contador++;
        } else if ((tipo == "O" || tipo == "o") && actual->dato.ataque > 0) {
            cout << "- " << actual->dato.nombre << " (Orco)\n";
            contador++;
        }
        actual = actual->siguiente;
    }

    if (contador == 0) {
        cout << "No hay especies registradas para este tipo. Personaje no creado.\n";
        delete nuevo;
        return;
    }

    cin.ignore();
    string seleccion;
    cout << "Escribe el nombre de la especie: ";
    getline(cin, seleccion);

    // Buscar la especie seleccionada
    actual = lista.getCabeza();
    while (actual != nullptr) {
        if (actual->dato.nombre == seleccion) {
            nuevo->tipoEspecie = &actual->dato;
            nuevo->siguiente = listaPersonajes;
            listaPersonajes = nuevo;
            cout << "Personaje creado exitosamente.\n";
            return;
        }
        actual = actual->siguiente;
    }

    cout << "No se encontró una especie con ese nombre. Personaje no creado.\n";
    delete nuevo;
}

void consultarPersonajes() {
    personaje* actual = listaPersonajes;
    if (!actual) {
        cout << "No hay personajes registrados.\n";
        return;
    }

    cout << "\n=== Lista de Personajes ===\n";
    while (actual) {
        cout << "Nombre: " << actual->nombre << "\n";
        cout << "Especie: " << actual->tipoEspecie->nombre << "\n";
        cout << "---------------------------\n";
        actual = actual->siguiente;
    }    
}

void eliminarPersonaje() {
    if (!listaPersonajes) {
        cout << "No hay personajes registrados.\n";
        return;
    }

    personaje* actual = listaPersonajes;
    int index = 1;

    cout << "\n=== Personajes Registrados ===\n";
    while (actual) {
        cout << index << ". " << actual->nombre << " (" << actual->tipoEspecie->nombre << ")\n";
        actual = actual->siguiente;
        index++;
    }

    cout << "Seleccione el número del personaje a eliminar: ";
    int seleccion = leerOpcion();

    actual = listaPersonajes;
    personaje* anterior = nullptr;
    for (int i = 1; actual && i < seleccion; i++) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (!actual) {
        cout << "Selección inválida.\n";
        return;
    }

    if (!anterior) listaPersonajes = actual->siguiente;
    else anterior->siguiente = actual->siguiente;

    delete actual;
    cout << "Personaje eliminado exitosamente.\n";
}

void modificarPersonaje(listaEspecies& lista) {
    if (!listaPersonajes) {
        cout << "No hay personajes registrados.\n";
        return;
    }

    personaje* actual = listaPersonajes;
    int index = 1;

    cout << "\n=== Personajes Registrados ===\n";
    while (actual) {
        cout << index << ". " << actual->nombre << " (" << actual->tipoEspecie->nombre << ")\n";
        actual = actual->siguiente;
        index++;
    }

    cout << "Seleccione el número del personaje a modificar: ";
    int seleccion = leerOpcion();

    actual = listaPersonajes;
    for (int i = 1; actual && i < seleccion; i++) {
        actual = actual->siguiente;
    }

    if (!actual) {
        cout << "Selección inválida.\n";
        return;
    }

    cin.ignore();
    cout << "Nuevo nombre: ";
    getline(cin, actual->nombre);

    cout << "Seleccione nueva especie:\n";
    nodoEspecie* especieActual = lista.getCabeza();
    int especieIndex = 1;

    while (especieActual) {
        cout << especieIndex << ". " << especieActual->dato.nombre << endl;
        especieActual = especieActual->siguiente;
        especieIndex++;
    }

    int seleccionEspecie;
    cout << "Ingrese el número de la nueva especie: ";
    seleccionEspecie = leerOpcion();

    especieActual = lista.getCabeza();
    for (int j = 1; especieActual && j < seleccionEspecie; j++) {
        especieActual = especieActual->siguiente;
    }

    if (!especieActual) {
        cout << "Especie no encontrada. No se actualizó.\n";
        return;
    }

    actual->tipoEspecie = &especieActual->dato;
    cout << "Personaje modificado exitosamente.\n";
}

void verSubMenuModificar(listaEspecies& lista) {
    int op;
    cout << "\n-- Modificar Elemento --" << endl;
    cout << "1. Personajes" << endl;
    cout << "2. Especies" << endl;
    cout << "3. Implementos" << endl;
    cout << "4. Equipos " << endl;
    cout << "5. Mochilas" << endl;
    cout << "6. Mapa" << endl;
    cout << "7. Volver al menu principal" << endl;
    cout << "Seleccione una opcion: ";
    op = leerOpcion();

    switch (op) {
        case 1:
            modificarPersonaje(lista);
            break;
        case 2:
            lista.modificarEspecie();
            break;
        case 3:
            cout << "Ingresando a la modificación de implementos..." << endl;
            break;
        case 4:
            cout << "Ingresando a la modificación de equipos..." << endl;
            break;
        case 5:
            cout << "Ingresando a la modificación de mochilas..." << endl;
            break;
        case 6:
            cout << "Ingresando a la modificación de mapas..." << endl;
            break;
        case 7:
            return;
        default:
            cout << "Opción inválida.\n";
    }
} 

void verSubMenuEliminar(listaEspecies& lista) {
    int op;
    cout << "\n-- Eliminar Elemento --" << endl;
    cout << "1. Personajes" << endl;
    cout << "2. Especies" << endl;
    cout << "3. Implementos" << endl;
    cout << "4. Equipos" << endl;
    cout << "5. Mochilas" << endl;
    cout << "6. Mapa" << endl;
    cout << "7. Volver al menu principal" << endl;
    cout << "Seleccione una opcion: ";
    op = leerOpcion();

    switch (op) {
        case 1:
            eliminarPersonaje();
            break;
        case 2:
            lista.eliminarEspecie();
            break;
        case 3:
            cout << "Ingresando a la eliminacion de implementos..." << endl;
            break;
        case 4:
            cout << "Ingresando a la eliminacion de equipos..." << endl;
            break;
        case 5:
            cout << "Ingresando a la eliminacion de mochilas..." << endl;
            break;
        case 6:
            cout << "Ingresando a la eliminacion de mapas..." << endl;
            break;
        case 7:
            return;
        default:
            cout << "Opción inválida.\n";
    }
}

void verSubMenuAgregar(listaEspecies& lista) {
    int op;
    cout<<"\n-- Crear Elemento --"<<endl;
    cout<<"1. Especies"<<endl;
    cout<<"2. Personajes"<<endl;
    cout<<"3. Implementos"<<endl;
    cout<<"4. Equipos "<<endl;
    cout<<"5. Mochilas"<<endl;
    cout<<"6. Mapa"<<endl;
    cout<<"7. Volver al menu principal"<<endl;
    cout<<"Seleccione una opcion: ";
    op=leerOpcion();

    switch (op) {
        case 1:
            lista.agregarEspecie(); // ✅ permite crear especie
            break;
        case 2:
            agregarPersonaje(lista);
            break;
        case 3:
            cout<<"Ingresando a la creacion de implementos..."<<endl;
            break;
        case 4:
            cout<<"Ingresando a la creacion de equipos..."<<endl;
            break;
        case 5:
            cout<<"Ingresando a la creacion de mochilas..."<<endl;
            break;
        case 6:
            cout<<"Ingresando a la creacion de mapas..."<<endl;
            break;
        case 7:
            return;
    }
}

void verSubMenuInformacion(listaEspecies& lista) {
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
            consultarPersonajes();
            lista.mostrarEspecie();
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
    listaEspecies lista;
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
        cout<<"6. Salir"<<endl;
        cout<<"______________________"<<endl;
        cout<<"Selecciona una opcion: ";
        op=leerOpcion();;

        switch (op) {
            case 1:
                verSubMenuInformacion(lista);;
                break;
            case 2:
                verSubMenuAgregar(lista);
                break;
            case 3:
                verSubMenuEliminar(lista);
                break;
            case 4:
                verSubMenuModificar(lista);
                break;
            case 5:
                cout<<"[Visualizar Mapa] en desarrollo..."<<endl;
                break;
            case 6:
                cout<<"Saliendo del programa..."<<endl;
                return 0;
        
        }
    }while (op!=6);

    return 0;
}
