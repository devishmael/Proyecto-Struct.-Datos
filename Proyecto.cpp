//Modulos
#include <iostream>
#include <limits>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <regex>
#include <cctype>
#include <iomanip>
#include <stack>

using namespace std;

//Funcion para validar opciones numericas
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

//Declaraciones Anticipadas
struct Sala;
class listaEspecies;
class listaPersonajes;
class listaMochilas;

//Estructura de las Especies
struct especie {
    string nombre;
    int fortaleza;
    double ataque;
    double salud;
    double rapidez;
    string tipo;
    especie* siguiente;
};
//Estructura de las Mochilas e Implementos
struct implemento {
    string nombre;
    string tipo;
    int usos;
    int fortaleza;
    int valorAtk;
    int valorDef;
    int valorHeal;
    bool enUso;

    implemento() : enUso(false) {} // Iniciar enUso a false
};
struct mochila {
    implemento* implementos[5];
    int numImplementos;

    mochila() : numImplementos(0) {
        for (int i = 0; i < 5; i++) {
            implementos[i] = nullptr;
        }
    }

    void agregarImplementoAMochila(implemento* imp) {
        if (imp->enUso) {
            cout << "El implemento '" << imp->nombre << "' ya está en uso y no se puede agregar a la mochila.\n";
            return;
        }

        if (numImplementos < 5) {
            implementos[numImplementos++] = imp;
            imp->enUso = true; // Marcar el implemento como en uso
            cout << "Implemento '" << imp->nombre << "' agregado a la mochila.\n";
        } else {
            cout << "La mochila está llena.\n";
        }
    }

    void eliminarImplementoEnMochila(int ind) {
        if (ind < 0 || ind >= numImplementos) {
            cout << "Índice inválido.\n";
            return;
        }
        cout << "Implemento '" << implementos[ind]->nombre << "' eliminado.\n";
        implementos[ind]->enUso = false;
        for (int i = ind; i < numImplementos - 1; i++) {
            implementos[i] = implementos[i + 1];
        }
        numImplementos--;
    }

    void mostrarMochila() {
        if (numImplementos == 0) {
            cout << "La mochila está vacía.\n";
            return;
        }
        cout << "\nContenido de la mochila (" << numImplementos << "/5):\n";
        cout << left << setw(5) << "No." 
            << setw(25) << "Nombre del implemento"
            << setw(20) << "Tipo"
            << setw(15) << "Usos restantes" << endl;
        cout << "----------------------------------------------------\n";
        for (int i = 0; i < numImplementos; i++) {
            cout << left << setw(5) << i+1 
                << setw(25) << implementos[i]->nombre
                << setw(20) << implementos[i]->tipo
                << setw(15) << implementos[i]->usos << endl;
        }
        cout << "----------------------------------------------------\n";
    }
};

//Estructura de los Personajes
struct personaje {
    personaje* siguiente;
    especie* especie;
    string nombre;
    mochila mochila;
};

//Lista de los Implementos
class listaImplementos {
    private:
        implemento* implementos;
        int capacidad;
        int cantidad;

    public:
        listaImplementos() {
            capacidad= 10;
            cantidad= 0;
            implementos= new implemento[capacidad];
        }

        ~listaImplementos() {
        delete[] implementos;
        }

        int obtenerCantidad() const {
            return cantidad;
        }

        implemento* obtenerImplemento(int ind) {
            if (ind >= 0 && ind < cantidad) {
                return &implementos[ind];
            }
            return nullptr;
        }

        void agregarImplemento(string nombre, string tipo, int usos, int fortaleza, int valorAtk, int valorDef, int valorHeal) {
            if(cantidad== capacidad) {
                capacidad*= 2;
                implemento* nuevoArray= new implemento[capacidad];
                for(int i= 0; i<cantidad; i++) {
                    nuevoArray[i]= implementos[i];
                }
                delete[] implementos;
                implementos= nuevoArray;
            }

            implemento nuevo;
         nuevo.nombre= nombre;
            nuevo.tipo= tipo;
         nuevo.usos= usos;
         nuevo.fortaleza= fortaleza;

            if(nuevo.tipo=="atacar") {
                nuevo.valorAtk= valorAtk;
                nuevo.valorDef= 0;
                nuevo.valorHeal= 0;
            } else if(nuevo.tipo=="defender") {
                nuevo.valorDef= valorDef;
                nuevo.valorAtk= 0;
                nuevo.valorHeal= 0;
            } else if(nuevo.tipo=="curar") {
                nuevo.valorHeal= valorHeal;
                nuevo.valorAtk= 0;
                nuevo.valorDef= 0;
            }

            implementos[cantidad++]= nuevo;
        }

        void agregarImplemento() {
            if(cantidad== capacidad) {
                capacidad*= 2;
                implemento* nuevoArray= new implemento[capacidad];
                for(int i=0; i<cantidad; i++) {
                    nuevoArray[i]= implementos[i];
                }
                delete[] implementos;
                implementos= nuevoArray;
            }

            implemento nuevo;
            cin.ignore();
            cout<<"Nombre del implemento: ";
            getline(cin, nuevo.nombre);

            string tipo;
            while(true) {
                cout<<"Tipo (atacar / defender / curar): ";
                getline(cin, tipo);
                if(tipo=="atacar" || tipo=="defender" || tipo=="curar") {
                    nuevo.tipo = tipo;
                    break;
                } else{
                    cout<<"El tipo no es valido. Por favor escribe atacar, defender o curar.\n";
                }
            }

         cout<<"Usos: ";
            while(!(cin>>nuevo.usos)) {
                cout<<"Numero invalido. Ingresa un numero entero: ";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout<<"Fortaleza: ";
            while(!(cin>>nuevo.fortaleza)) {
                cout<<"Cantidad invalida. Ingresa un numero entero: ";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if(nuevo.tipo=="atacar") {
                cout<<"Valor de ataque: ";
                while (!(cin>>nuevo.valorAtk)) {
                    cout<<"Cantidad invalida. Ingresa un numero entero: ";
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } else if(nuevo.tipo=="defender") {
                cout<<"Valor de defensa: ";
                while(!(cin>>nuevo.valorDef)) {
                    cout<<"Cantidad invalida. Ingresa un numero entero: ";
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } else if(nuevo.tipo=="curar") {
                cout<<"Valor de curacion: ";
                while(!(cin>>nuevo.valorHeal)) {
                    cout<<"Cantidad invalida. Ingresa un numero decimal: ";
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            implementos[cantidad++]= nuevo;
            cout<<"Implemento agregado.\n";
        }

        void mostrarImplementos() {
            if(cantidad == 0) {
                cout << "No hay implementos registrados.\n";
                cout << "__________________________\n";
                return;
            }

            cout << left << setw(5) << "No." 
                << setw(20) << "Nombre" 
                << setw(15) << "Tipo" 
                << setw(10) << "Usos" << "\n";
            cout << "---------------------------------------------------\n";

            for(int i = 0; i < cantidad; i++) {
                cout << left << setw(5) << i + 1 
                    << setw(20) << implementos[i].nombre 
                    << setw(15) << implementos[i].tipo 
                    << setw(10) << implementos[i].usos << "\n";
            }
            cout << "---------------------------------------------------\n";
        }

        void eliminarImplemento() {
            mostrarImplementos();
            cout<<"Selecciona el numero del implemento para eliminar: ";
            int sel= leerOpcion();
            if(sel<1 || sel>cantidad) {
                cout << "Opcion incorrecta.\n";
                return;
            }
            for(int i=sel - 1; i<cantidad-1; i++) {
                implementos[i]= implementos[i+1];
            }
            cantidad--;
            cout<<"Implemento eliminado.\n";
        }

        void modificarImplemento() {
            mostrarImplementos();
            cout<<"Selecciona el numero del implemento a modificar: ";
            int sel= leerOpcion();
            if(sel<1 || sel>cantidad) {
                cout<<"Opcion incorrecta.\n";
                return;
            }
            implemento& imp= implementos[sel-1];
            cin.ignore();
            cout<<"Nuevo nombre: ";
            getline(cin, imp.nombre);

            string tipo;
            while(true) {
                cout<<"Nuevo tipo (atacar/defender/curar): ";
                getline(cin, tipo);
                if(tipo=="atacar" || tipo=="defender" || tipo=="curar") {
                    imp.tipo= tipo;
                    break;
                } else{
                    cout<<"Tipo invalido. Por favor escribe atacar, defender o curar.\n";
                }
            }

            cout<<"Nuevos usos: ";
            cin>>imp.usos;

            cout<<"Nueva fortaleza: ";
            cin>>imp.fortaleza;

            if(imp.tipo=="atacar") {
                cout<<"Nuevo ataque: ";
                cin>>imp.valorAtk;
                imp.valorDef= 0;
                imp.valorHeal= 0;
            } else if(imp.tipo=="defender") {
                cout<<"Nueva defensa: ";
                cin>>imp.valorDef;
                imp.valorAtk= 0;
                imp.valorHeal= 0;
            } else if(imp.tipo=="curar") {
                cout<<"Nueva curacion: ";
                cin>>imp.valorHeal;
                imp.valorAtk= 0;
                imp.valorDef= 0;
            }
            cout<<"Implemento modificado.\n";
        }
};

//Lista de las Especies
class listaEspecies {
    private:
        especie* cabeza;

        int contarEspecies() {
            int count = 0;
            especie* temp = cabeza;
            while (temp) {
                count++;
                temp = temp->siguiente;
            }
            return count;
        }

    public:
        listaEspecies() {
            cabeza = nullptr;
        }

        ~listaEspecies() {
            limpieza();
        }

        void limpieza() {
            especie* actual = cabeza;
            while (actual != nullptr) {
                especie* siguiente = actual->siguiente;
                delete actual;
                actual = siguiente;
            }
            cabeza = nullptr;
        }

        especie* obtenerCabeza() {
            return cabeza;
        }

        void agregarEspecie(string nombre, string tipo, int fortaleza, double ataque, double salud, double rapidez) {
            especie* nuevaEspecie = new especie();
            nuevaEspecie->nombre = nombre;
            
            if (tipo == "Heroe") {
                nuevaEspecie->fortaleza = fortaleza;
                nuevaEspecie->ataque = 0;
            } else if (tipo == "Orco") {
                nuevaEspecie->ataque = ataque;
                nuevaEspecie->fortaleza = 0;
            }
            
            nuevaEspecie->salud = salud;
            nuevaEspecie->rapidez = rapidez;
            nuevaEspecie->tipo = tipo;
            nuevaEspecie->siguiente = nullptr;

            if (!cabeza) {
                cabeza = nuevaEspecie;
            } else {
                especie* temp = cabeza;
                while (temp->siguiente) {
                    temp = temp->siguiente;
                }
                temp->siguiente = nuevaEspecie;
            }
        }

        void agregarEspecie() {
            especie* esp = new especie();
            string tipo;
            
            // Validación de nombre
            cout << "Ingrese el nombre: ";
            cin >> esp->nombre;
            
            // Validación de tipo
            while (true) {
                cout << "Heroe u Orco? (H/O): ";
                cin >> tipo;
                if (toupper(tipo[0]) == 'H') {
                    esp->tipo = "Heroe";
                    cout << "Fortaleza: ";
                    cin >> esp->fortaleza;
                    esp->ataque = 0;
                    break;
                } else if (toupper(tipo[0]) == 'O') {
                    esp->tipo = "Orco";
                    cout << "Ataque: ";
                    cin >> esp->ataque;
                    esp->fortaleza = 0;
                    break;
                }
                cout << "Tipo inválido!\n";
            }
            
            cout << "Salud: ";
            cin >> esp->salud;
            cout << "Rapidez: ";
            cin >> esp->rapidez;
            
            esp->siguiente = nullptr;
            
            if (!cabeza) {
                cabeza = esp;
            } else {
                especie* temp = cabeza;
                while (temp->siguiente) {
                    temp = temp->siguiente;
                }
                temp->siguiente = esp;
            }
            cout << esp->nombre << " agregado.\n";
        }

        void mostrarEspecies() {
            especie* temp = cabeza;
            int i = 1;
            
            cout << "\nLISTA DE ESPECIES:\n";
            cout << left << setw(5) << "No." 
                << setw(15) << "Nombre" 
                << setw(10) << "Tipo" 
                << setw(10) << (cabeza && cabeza->tipo == "Heroe" ? "Fuerza" : "Ataque")
                << setw(10) << "Salud"
                << setw(10) << "Velocidad\n";
            
            while (temp) {
                cout << left << setw(5) << i++
                    << setw(15) << temp->nombre 
                    << setw(10) << temp->tipo 
                    << setw(10) << (temp->tipo == "Heroe" ? temp->fortaleza : temp->ataque)
                    << setw(10) << temp->salud
                    << setw(10) << temp->rapidez << "\n";
                temp = temp->siguiente;
            }
        }

        especie* seleccionarEspecie() {
            mostrarEspecies();
            if (!cabeza) return nullptr;
            
            int opcion;
            cout << "Seleccione especie (1-" << contarEspecies() << "): ";
            cin >> opcion;
            
            especie* temp = cabeza;
            for (int i = 1; temp && i < opcion; i++) {
                temp = temp->siguiente;
            }
            
            return temp;
        }

        void eliminarEspecie() {
            if (!cabeza) {
                cout << "Lista vacía!\n";
                return;
            }
            
            especie* temp = cabeza;
            cabeza = cabeza->siguiente;
            cout << "Eliminando " << temp->nombre << "\n";
            delete temp;
        }

        void modificarEspecie() {
            especie* seleccionada = seleccionarEspecie();
            if (!seleccionada) {
                cout << "No se seleccionó ninguna especie.\n";
                return;
            }

            cin.ignore();
            cout << "Nuevo nombre de la especie: ";
            getline(cin, seleccionada->nombre);

            string tipo;
            while (true) {
                cout << "¿Será un Héroe o un Orco? (H/O): ";
                getline(cin, tipo);
                if (toupper(tipo[0]) == 'H') {
                    cout << "Nueva fortaleza: ";
                    cin >> seleccionada->fortaleza;
                    seleccionada->ataque = 0;
                    break;
                } else if (toupper(tipo[0]) == 'O') {
                    cout << "Nuevo ataque: ";
                    cin >> seleccionada->ataque;
                    seleccionada->fortaleza = 0;
                    break;
                } else {
                    cout << "Opción no válida. Intenta de nuevo." << endl;
                }
            }

            cout << "Nueva salud: ";
            cin >> seleccionada->salud;

            cout << "Nueva rapidez: ";
            cin >> seleccionada->rapidez;

            cout << "Especie modificada exitosamente." << endl;
        }
};

//Lista de los Personajes
class listaPersonajes {
    private:
        personaje* cabeza;
        listaEspecies* lista_especies;

        especie* buscarEspecie(string nombre) {
            especie* temp = lista_especies->obtenerCabeza(); // Cambiado a especie*
            while (temp != nullptr) {
                if (temp->nombre == nombre) {
                    return temp;
                }
                temp = temp->siguiente;
            }
            return nullptr;
        }

    public:
        listaPersonajes(listaEspecies& especies) {
            cabeza = nullptr;
            lista_especies = &especies;
        }

        ~listaPersonajes() {
            limpieza();
        }

        void limpieza() {
            personaje* actual = cabeza;
            while (actual != nullptr) {
                personaje* siguiente = actual->siguiente;
                delete actual;
                actual = siguiente;
            }
            cabeza = nullptr;
        }

        personaje* obtenerCabeza() {
            return cabeza;
        }

        void agregarPersonaje(string nombre_especie, string nombre_personaje) {
            especie* especie_ptr = buscarEspecie(nombre_especie);
            if (!especie_ptr) {
                cout << "Error: Especie '" << nombre_especie << "' no encontrada." << endl;
                return;
            }

            personaje* nuevo = new personaje();
            nuevo->nombre = nombre_personaje;
            nuevo->especie = especie_ptr;
            nuevo->siguiente = nullptr;

            if (cabeza == nullptr) {
                cabeza = nuevo;
            } else {
                personaje* temp = cabeza;
                while (temp->siguiente != nullptr) {
                    temp = temp->siguiente;
                }
                temp->siguiente = nuevo;
            }
        }

        void agregarPersonaje() {
            personaje* nuevo = new personaje();

            while (true) {
                cout << "Ingresa el nombre del personaje: ";
                cin >> nuevo->nombre;

                bool valido = true;
                for (char c : nuevo->nombre) {
                    if (!isalpha(c)) {
                        valido = false;
                        break;
                    }
                }

                if (valido) break;
                cout << "Nombre invalido, solo letras. Intenta de nuevo." << endl;
            }

            cout << "Selecciona una especie para el personaje" << endl;
            cout << "_________________________________" << endl;
            lista_especies->mostrarEspecies();

            int op;
            while (true) {
                cout << "Ingresa el numero de la especie: ";
                cin >> op;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Numero invalido. Ingresa un numero." << endl;
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                especie* tempEsp = lista_especies->obtenerCabeza();
                int cont = 1;
                while (tempEsp != nullptr && cont < op) {
                    tempEsp = tempEsp->siguiente;
                    cont++;
                }

                if (tempEsp == nullptr) {
                    cout << "No existe una especie con ese numero. Intenta de nuevo." << endl;
                    continue;
                }

                nuevo->especie = tempEsp;
                break;
            }

            nuevo->siguiente = nullptr;

            if (cabeza == nullptr) {
                cabeza = nuevo;
            } else {
                personaje* temp = cabeza;
                while (temp->siguiente != nullptr) {
                    temp = temp->siguiente;
                }
                temp->siguiente = nuevo;
            }
            cout << "Personaje '" << nuevo->nombre << "' agregado exitosamente." << endl;
        }

        personaje* obtenerPjInd(int ind) {
            personaje* temp = cabeza;
            int cont = 1;

            while (temp != nullptr) {
                if (cont == ind) {
                    return temp;
                }
                temp = temp->siguiente;
                cont++;
            }
            return nullptr;
        }

        void mostrarPersonajes() {
            if (cabeza == nullptr) {
                cout << "No hay personajes registrados." << endl;
                return;
            }
            // Encabezado de la tabla
            cout << left << setw(5) << "No." 
                << setw(20) << "Nombre" 
                << setw(20) << "Especie" << endl;
            cout << "---------------------------------------------------\n";
            personaje* temp = cabeza;
            int cont = 1;
            while (temp != nullptr) {
                cout << left << setw(5) << cont 
                    << setw(20) << temp->nombre 
                    << setw(20) << temp->especie->nombre << endl; // Cambiado a temp->especie->nombre
                temp = temp->siguiente;
                cont++;
            }
            cout << "---------------------------------------------------\n";
        }

        void mostrarPersonajesConMochilas() {
            if (cabeza == nullptr) {
                cout << "No hay personajes registrados." << endl;
                return;
            }
            cout << left << setw(5) << "No." 
                << setw(20) << "Nombre" 
                << setw(30) << "Mochila" << endl;
            cout << "-------------------------------------------------------------\n";
            personaje* temp = cabeza;
            int cont = 1;
            while (temp != nullptr) {
                cout << left << setw(5) << cont 
                    << setw(20) << temp->nombre 
                    << setw(30);
                if (temp->mochila.numImplementos == 0) {
                    cout << "Vacía";
                } else {
                    for (int i = 0; i < temp->mochila.numImplementos; i++) {
                        cout << "'" << temp->mochila.implementos[i]->nombre << "'";
                        if (i < temp->mochila.numImplementos - 1) {
                            cout << ", ";
                        }
                    }
                }
                cout << endl;
                temp = temp->siguiente;
                cont++;
            }
            cout << "-------------------------------------------------------------\n";
        }

        personaje* seleccionarPersonajePorIndice() {
            if (!cabeza) {
                cout << "No hay personajes registrados.\n";
                return nullptr;
            }
            // Encabezado de la tabla
            cout << "\n=== Personajes disponibles ===\n";
            cout << left << setw(5) << "No." 
                << setw(20) << "Nombre" << endl;
            cout << "-------------------------------------\n";
            personaje* temp = cabeza;
            int i = 1;
            while (temp) {
                cout << left << setw(5) << i 
                    << setw(20) << temp->nombre << endl;
                temp = temp->siguiente;
                i++;
            }
            cout << "-------------------------------------\n";
            int seleccion;
            cout << "Selecciona el numero del personaje: ";
            seleccion = leerOpcion();
            temp = cabeza;
            for (int j = 1; temp && j < seleccion; j++) {
                temp = temp->siguiente;
            }
            if (!temp) {
                cout << "No es valido su numero.\n";
                return nullptr;
            }
            return temp;
        }   

        void eliminarPersonaje() {
            personaje* seleccionada = seleccionarPersonajePorIndice();
            if (!seleccionada) return;
            personaje* actual = cabeza;
            personaje* anterior = nullptr;
            while (actual) {
                if (actual == seleccionada) {
                    string nombreEliminado = actual->nombre;
                    if (!anterior) {
                        cabeza = actual->siguiente;
                    } else {
                        anterior->siguiente = actual->siguiente;
                    }
                    delete actual;
                    cout << "Personaje '" << nombreEliminado << "' eliminado." << endl;
                    return;
                }
                anterior = actual;
                actual = actual->siguiente;
            }
            cout << "Personaje no encontrado." << endl;
        }

        void modificarPersonaje(listaEspecies& lista) {
            personaje* seleccionada = seleccionarPersonajePorIndice();
            if (!seleccionada) return;

            personaje& pj = *seleccionada;
            while (true) {
                cout << "Ingrese el nombre del personaje: ";
                cin >> pj.nombre;

                bool valido = true;
                for (char c : pj.nombre) {
                    if (!isalpha(c)) {
                        valido = false;
                        break;
                    }
                }
                if (valido) {
                    break; 
                } else {
                    cout << "Nombre invalido, solo letras. Intenta de nuevo." << endl;
                }
            }

            cout << "\n__ Lista de Especies __\n";
            lista.mostrarEspecies();

            int op; 
            while (true) {
                cout << "Ingresa el numero de la especie: ";
                cin >> op;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Numero invalido, ingresa un numero." << endl;
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                especie* tempEsp = lista.obtenerCabeza();
                int cont = 1;
                while (tempEsp != nullptr && cont < op) {
                    tempEsp = tempEsp->siguiente;
                    cont++;
                }
                if (tempEsp == nullptr) {
                    cout << "No hay especies con ese numero, intenta de nuevo." << endl;   
                    continue;
                }
                pj.especie = tempEsp;
                break;
            }
            cout << "Personaje modificado." << endl;
        }

        void manejarMochila(listaImplementos& listaImplementos) {
            mostrarPersonajes();
            if (!cabeza) {
                cout << "No hay personajes disponibles.\n";
                return;
            }

            cout << "Selecciona el número del personaje: ";
            int seleccion = leerOpcion();
            personaje* personaje = obtenerPjInd(seleccion);
            if (!personaje) {
                cout << "Selección inválida.\n";
                return;
            }

            int opcion;
            do {
                cout << "\n--- Mochila de " << personaje->nombre << " ---\n";
                personaje->mochila.mostrarMochila();
                cout << "\n1. Agregar implemento\n";
                cout << "2. Eliminar implemento\n";
                cout << "3. Volver\n";
                cout << "Selecciona una opción: ";
                opcion = leerOpcion();

                switch (opcion) {
                    case 1:
                        listaImplementos.mostrarImplementos();
                        if (listaImplementos.obtenerCantidad() > 0) {
                            cout << "Selecciona el implemento a agregar: ";
                            int impSel = leerOpcion();
                            if (impSel > 0 && impSel <= listaImplementos.obtenerCantidad()) {
                                implemento* imp = listaImplementos.obtenerImplemento(impSel - 1);
                                personaje->mochila.agregarImplementoAMochila(imp);
                            } else {
                                cout << "Selección inválida.\n";
                            }
                        }
                        break;
                    case 2:
                        if (personaje->mochila.numImplementos > 0) {
                            cout << "Selecciona el implemento a eliminar: ";
                            int impSel = leerOpcion();
                            if (impSel > 0 && impSel <= personaje->mochila.numImplementos) {
                                personaje->mochila.eliminarImplementoEnMochila(impSel - 1);
                            } else {
                                cout << "Selección inválida.\n";
                            }
                        }
                        break;
                    case 3:
                        break;
                    default:
                        cout << "Opción inválida.\n";
                }
            } while (opcion != 3);
        }
};

//Funcion para eliminar especies (para evitar generar dependencias circulares entre las clases listaEspecies y listaPersonajes)
void eliminarEspecie(listaEspecies& especies, listaPersonajes& personajes) {
    if (especies.obtenerCabeza() == nullptr) {
        cout << "No hay especies registradas para eliminar." << endl;
        return;
    }

    cout << "\n___ Especies disponibles ___" << endl;
    especies.mostrarEspecies();

    especie* especieSeleccionada = especies.seleccionarEspecie();
    if (!especieSeleccionada) {
        return;
    }

    bool especieEnUso = false;
    personaje* personajeActual = personajes.obtenerCabeza();
    while (personajeActual) {
        if (personajeActual->especie == especieSeleccionada) {
            especieEnUso = true;
            break;
        }
        personajeActual = personajeActual->siguiente;
    }

    if (especieEnUso) {
        cout << "No se puede eliminar la especie '" << especieSeleccionada->nombre << "' porque hay personajes que la utilizan." << endl;
    } else {
        string nombreEspecie = especieSeleccionada->nombre;
        especie* actual = especies.obtenerCabeza();
        especie* anterior = nullptr;
        bool eliminado = false;

        while (actual && !eliminado) {
            if (actual == especieSeleccionada) {
                if (!anterior) {
                    especies.eliminarEspecie();
                } else {
                    anterior->siguiente = actual->siguiente;
                    delete actual;
                }
                eliminado = true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        if (eliminado) {
            cout << "Especie '" << nombreEspecie << "' eliminada correctamente." << endl;
        } else {
            cout << "Error: No se pudo eliminar la especie." << endl;
        }
    }
}

//Estructura y Lista de los Equipos
struct equipo {
    string nombre;
    personaje* personajes[4];
    int numPjs;
    bool PuertaDelDestino;
    equipo* siguiente;
};
class listaEquipos {
    private:
        equipo* cabeza;

    public:
        listaEquipos() {
            cabeza = nullptr;
        }

        ~listaEquipos() {
            limpieza();
        }

        void limpieza() {
            equipo* actual = cabeza;
            while (actual != nullptr) {
                equipo* siguiente = actual->siguiente;
                delete actual;
                actual = siguiente;
            }
            cabeza = nullptr;
        }

        void agregarEquipo(listaPersonajes& listaPersonajes) {
            equipo* nuevoEquipo = new equipo();
            cout << "Ingrese el nombre del equipo: ";
            cin >> nuevoEquipo->nombre;
            nuevoEquipo->numPjs = 0;
            nuevoEquipo->siguiente = nullptr;

            while (nuevoEquipo->numPjs < 4) {
                cout << endl << "Selecciona un personaje para el equipo (por numero)" << endl;
                listaPersonajes.mostrarPersonajes();

                int op;
                cout << "Ingresa el numero del personaje (0 para terminar): ";
                cin >> op;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Numero no valido, por favor ingresa un numero." << endl;
                    continue;
                }

                if (op == 0) {
                    break;
                }

                personaje* temp = listaPersonajes.obtenerPjInd(op);
                if (temp == nullptr) {
                    cout << "Numero no valido, intenta de nuevo." << endl;
                    continue;
                }

                bool rep = false; // rep = repetido
                for (int i = 0; i < nuevoEquipo->numPjs; i++) {
                    if (nuevoEquipo->personajes[i] == temp) {
                        rep = true;
                        break;
                    }
                }

                if (rep) {
                    cout << "Este personaje ya está en el equipo." << endl;
                    continue;
                }

                nuevoEquipo->personajes[nuevoEquipo->numPjs] = temp;
                nuevoEquipo->numPjs += 1;
                cout << "Personaje '" << temp->nombre << "' agregado al equipo" << endl;
            }

            if (nuevoEquipo->numPjs == 0) {
                cout << "No se agregó ningún personaje, no se creó el equipo." << endl;
                delete nuevoEquipo;
                return;
            }

            nuevoEquipo->siguiente = cabeza;
            cabeza = nuevoEquipo;

            cout << "Equipo '" << nuevoEquipo->nombre << "' creado." << endl;
        }

        void mostrarEquipos() {
            if (cabeza == nullptr) {
                cout << "No hay equipos registrados." << endl;
                return;
            }

            cout << "\n=== Equipos Registrados ===\n";
            cout << left << setw(5) << "No." 
                << setw(30) << "Nombre del Equipo" 
                << setw(25) << "Personajes" << endl;
            cout << string(60, '-') << endl;

            equipo* temp = cabeza;
            int cont = 1;
            while (temp != nullptr) {
                cout << left << setw(5) << cont++ 
                    << setw(30) << temp->nombre 
                    << setw(25);

                ostringstream personajesList;
                for (int i = 0; i < temp->numPjs; i++) {
                    personaje* personaje = temp->personajes[i];
                    if (personaje != nullptr) {
                        personajesList << personaje->nombre;
                        if (i < temp->numPjs - 1) {
                            personajesList << ", ";
                        }
                    }
                }
                cout << personajesList.str();
                cout << endl;

                temp = temp->siguiente;
            }
            cout << string(60, '-') << endl;
        }

        equipo* seleccionarEquipoPorIndice() {
            if (!cabeza) {
                cout << "No hay equipos registrados.\n";
                return nullptr;
            }
            cout << "\n=== Equipos disponibles ===\n";
            cout << left << setw(5) << "No." 
                << setw(30) << "Nombre del Equipo" << endl;
            cout << string(40, '-') << endl;
            equipo* temp = cabeza;
            int i = 1;
            while (temp) {
                cout << left << setw(5) << i++ 
                    << setw(30) << temp->nombre << endl;
                temp = temp->siguiente;
            }
            cout << string(40, '-') << endl;
            int seleccion;
            cout << "Selecciona el numero del equipo: ";
            seleccion = leerOpcion();
            temp = cabeza;
            for (int j = 1; temp && j < seleccion; j++) {
                temp = temp->siguiente;
            }
            if (!temp) {
                cout << "No es válido su número.\n";
                return nullptr;
            }
            return temp;
        }

        void eliminarEquipo() {
            equipo* seleccionada = seleccionarEquipoPorIndice();
            if (!seleccionada) return;

            equipo* actual = cabeza;
            equipo* anterior = nullptr;

            while (actual) {
                if (actual == seleccionada) {
                    if (!anterior) {
                        cabeza = actual->siguiente;
                    } else {
                        anterior->siguiente = actual->siguiente;
                    }
                    delete actual;
                    cout << "Equipo eliminado." << endl;
                    return;
                }
                anterior = actual;
                actual = actual->siguiente;
            }
            cout << "No se encontró el equipo." << endl;
        }
};

struct equipoOrco {
    especie* miembros[15];
    int numMiembros;
    equipoOrco() {
        numMiembros = 0;
    }
};

//Estructura y Lista de las Salas
struct Adyacencia {
    Sala* salaDestino;
    int distancia;
    Adyacencia* siguiente;
};
struct Sala {
    int id;
    string nombre;
    Adyacencia* adyacencias;
    Sala* siguiente;
    bool apto;
    bool visitada;
    int distanciaAcumulada;
    bool PuertaDelDestino;
    bool pddApto;
    equipoOrco equipoOrcos;
    Sala(int id, string nombre, Adyacencia* adyacencias, Sala* siguiente, bool apto = true) : id(id), nombre(nombre), adyacencias(adyacencias), siguiente(siguiente), apto(apto), visitada(false), distanciaAcumulada(0), PuertaDelDestino(false), pddApto(true) {}
};
class listaSalas {
    private:
        Sala* cabeza;

        Sala* obtenerSiguienteOriginal(Sala* sala) {
            Sala* temp = cabeza;
            while (temp != nullptr && temp->id != sala->id) {
                temp = temp->siguiente;
            }
            return temp ? temp->siguiente : nullptr;
        }

    public:
        listaSalas() {
            cabeza = nullptr;
        }

        ~listaSalas() {
            limpieza();
        }

        void limpieza() {
            while (cabeza != nullptr) {
                Sala* temp = cabeza;
                cabeza = cabeza->siguiente;

                Adyacencia* adyacenteActual = temp->adyacencias;
                while (adyacenteActual != nullptr) {
                    Adyacencia* tempAdyacente = adyacenteActual;
                    adyacenteActual = adyacenteActual->siguiente;
                    delete tempAdyacente;
                }

                delete temp;
            }
        }

        Sala* obtenerSalaPorId(int id) {
            Sala* actual = cabeza;
            while (actual != nullptr) {
                if (actual->id == id) {
                    return actual;
                }
                actual = actual->siguiente;
            }
            return nullptr;
        }

        int convertirAEntero(const string& str) {
            int resultado = 0;
            bool encontradoDigito = false;

            for (char c : str) {
                if (isspace(c)) {
                    continue;
                }
                if (isdigit(c)) {
                    resultado = resultado * 10 + (c - '0');
                    encontradoDigito = true;
                } else {
                    cout << "Error: se encontró un caracter que no es número: " << c << endl;
                    return -1;
                }
            }

            if (!encontradoDigito) {
                cout << "Error: no se encontraron dígitos." << endl;
                return -1;
            }

            return resultado;
        }

        void agregarSala(int id, const string& nombre, Adyacencia* adyacencias) {
            Sala* nuevaSala = new Sala{id, nombre, adyacencias, cabeza};
            cabeza = nuevaSala;
        }

        void agregarSala() {
            mostrarSalas();

            int id;
            string nombre;

            while (true) {
                cout << "Ingresa el ID de la sala: ";
                string input;
                cin >> input;
                id = convertirAEntero(input);

                Sala* actual = cabeza;
                bool idExistente = false;
                while (actual != nullptr) {
                    if (actual->id == id) {
                        idExistente = true;
                        break;
                    }
                    actual = actual->siguiente;
                }
                if (idExistente) {
                    cout << "Error: Ya existe una sala con el ID " << id << ". Intenta con otro ID." << endl;
                } else if (id != -1) {
                    break;
                }
            }

            while (true) {
                cout << "Ingresa el nombre de la sala: ";
                cin.ignore();
                getline(cin, nombre);

                bool valido = true;
                for (char c : nombre) {
                    if (!isalpha(c) && c != ' ') {
                        valido = false;
                        break;
                    }
                }

                if (valido) {
                    break; 
                } else {
                    cout << "Nombre no válido, solo letras y espacios. Intenta de nuevo." << endl;
                }
            }

            Adyacencia* adyacencias = nullptr;
            Adyacencia* ultimoAdyacente = nullptr;
            char continuar;

            do {
                int idAdyacente, distancia;

                while (true) {
                    mostrarSalas();
                    cout << "Ingresa el ID de la sala adyacente (o -1 para terminar): ";
                    cin >> idAdyacente;
                    if (idAdyacente == -1) break;

                    Sala* salaAdyacente = obtenerSalaPorId(idAdyacente);
                    if (!salaAdyacente) {
                        cout << "Error: Sala adyacente no encontrada." << endl;
                        continue;
                    }

                    while (true) {
                        cout << "Ingresa la distancia a la sala adyacente: ";
                        string input;
                        cin >> input;
                        distancia = convertirAEntero(input);
                        if (distancia != -1) break;
                    }

                    Adyacencia* nuevoAdyacente = new Adyacencia{salaAdyacente, distancia, nullptr};
                    if (adyacencias == nullptr) {
                        adyacencias = nuevoAdyacente;
                    } else {
                        ultimoAdyacente->siguiente = nuevoAdyacente;
                    }
                    ultimoAdyacente = nuevoAdyacente;
                    
                    cout << "Adyacencia añadida." << endl;
                }

                cout << "¿Quieres agregar otra adyacencia? (s/n): ";
                cin >> continuar;
            } while (continuar == 's' || continuar == 'S');

            agregarSala(id, nombre, adyacencias);
            cout << "Sala '" << nombre << "' agregada." << endl;
        }

        void mostrarSalas() {
            if (cabeza == nullptr) {
                cout << "No hay salas registradas." << endl;
                return;
            }
            cout << "\n=== Salas Registradas ===\n";
            cout << left << setw(5) << "ID" 
                << setw(30) << "Nombre" 
                << setw(50) << "Adyacencias" << endl;
            cout << string(85, '-') << endl;
            Sala* actual = cabeza;
            while (actual != nullptr) {
                cout << left << setw(5) << actual->id 
                    << setw(30) << actual->nombre 
                    << setw(50);
                
                Adyacencia* adyacenteActual = actual->adyacencias;
                if (adyacenteActual == nullptr) {
                    cout << "Ninguna"; 
                } else {
                    string adyacenciasStr;
                    while (adyacenteActual != nullptr) {
                        adyacenciasStr += to_string(adyacenteActual->salaDestino->id) + ":" + to_string(adyacenteActual->distancia) + " ";
                        adyacenteActual = adyacenteActual->siguiente;
                    }
                    if (adyacenciasStr.length() > 50) {
                        adyacenciasStr = adyacenciasStr.substr(0, 47) + "...";
                    }
                    cout << adyacenciasStr;
                }
                cout << endl;
                actual = actual->siguiente;
            }
            cout << string(85, '-') << endl; 
        }

        void eliminarSala() {
            mostrarSalas();
            cout << "__________________________\n";

            int id;
            while (true) {
                cout << "Ingresa el ID de la sala a eliminar: ";
                string input;
                cin >> input;
                id = convertirAEntero(input);
                if (id != -1) break;
            }

            Sala* actual = cabeza;
            Sala* anterior = nullptr;

            while (actual != nullptr && actual->id != id) {
                anterior = actual;
                actual = actual->siguiente;
            }

            if (actual == nullptr) {
                cout << "Sala no encontrada," << endl;
                return;
            }

            if (anterior == nullptr) {
                cabeza = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            Adyacencia* adyacenteActual = actual->adyacencias;
            while (adyacenteActual != nullptr) {
                Adyacencia* temp = adyacenteActual;
                adyacenteActual = adyacenteActual->siguiente;
                delete temp;
            }

            delete actual;
            cout << "Sala eliminada." << endl;
        }

        void modificarSala() {
            mostrarSalas();
            cout << "__________________________\n";

            int id;
            while (true) {
                cout << "Ingresa el ID de la sala a modificar: ";
                string input;
                cin >> input;
                id = convertirAEntero(input);
                if (id != -1) break;
            }

            Sala* actual = cabeza;
            while (actual != nullptr && actual->id != id) {
                actual = actual->siguiente;
            }

            if (actual == nullptr) {
                cout << "Sala no encontrada." << endl;
                return;
            }

            string nuevoNombre;
            while (true) {
                cout << "\nNombre actual: " << actual->nombre << endl;
                cout << "Ingresa el nuevo nombre de la sala: ";
                cin.ignore();
                getline(cin, nuevoNombre);

                bool valido = true;
                for (char c : nuevoNombre) {
                    if (!isalpha(c) && c != ' ') {
                        valido = false;
                        break;
                    }
                }

                if (valido) {
                    break; 
                } else {
                    cout << "Nombre no válido, solo letras y espacios. Intenta de nuevo." << endl;
                }
            }

            Adyacencia* nuevasAdyacencias = nullptr;
            Adyacencia* ultimoAdyacente = nullptr;
            char continuar;

            cout << "\n___ Adyacencias Actuales ___" << endl;
            Adyacencia* adyacenteActual = actual->adyacencias;
            while (adyacenteActual != nullptr) {
                cout << adyacenteActual->salaDestino->id << ":" << adyacenteActual->distancia << " ";
                adyacenteActual = adyacenteActual->siguiente;
            }
            cout << "\n__________________________\n";

            do {
                cout << "¿Qué quiere hacer con las adyacencias?" << endl;
                cout << "1. Agregar nueva adyacencia" << endl;
                cout << "2. Eliminar adyacencia existente" << endl;
                cout << "3. Cambiar distancia de una adyacencia" << endl;
                cout << "4. Terminar modificaciones" << endl;
                cout << "Selecciona una opción: ";
                int opcion;
                cin >> opcion;

                switch (opcion) {
                    case 1: {
                        int idAdyacente, distancia;

                        while (true) {
                            mostrarSalas();
                            cout << "Ingresa el ID de la nueva sala adyacente: ";
                            cin >> idAdyacente;

                            Sala* salaAdyacente = obtenerSalaPorId(idAdyacente);
                            if (!salaAdyacente) {
                                cout << "Error: Sala adyacente no encontrada." << endl;
                                continue;
                            }

                            while (true) {
                                cout << "Ingresa la distancia a la nueva sala adyacente: ";
                                string input;
                                cin >> input;
                                distancia = convertirAEntero(input);
                                if (distancia != -1) break;
                            }

                            Adyacencia* nuevoAdyacente = new Adyacencia{salaAdyacente, distancia, nullptr};
                            if (nuevasAdyacencias == nullptr) {
                                nuevasAdyacencias = nuevoAdyacente;
                            } else {
                                ultimoAdyacente->siguiente = nuevoAdyacente;
                            }
                            ultimoAdyacente = nuevoAdyacente;

                            cout << "Adyacencia añadida." << endl;
                            break;
                        }
                        break;
                    }
                    case 2: {
                        int idAdyacente;
                        cout << "Ingresa el ID de la sala adyacente a eliminar: ";
                        cin >> idAdyacente;

                        Adyacencia* actualAdyacente = actual->adyacencias;
                        Adyacencia* anteriorAdyacente = nullptr;

                        while (actualAdyacente != nullptr && actualAdyacente->salaDestino->id != idAdyacente) {
                            anteriorAdyacente = actualAdyacente;
                            actualAdyacente = actualAdyacente->siguiente;
                        }

                        if (actualAdyacente == nullptr) {
                            cout << "Adyacencia no encontrada." << endl;
                        } else {
                            if (anteriorAdyacente == nullptr) {
                                actual->adyacencias = actualAdyacente->siguiente; // Eliminar el primer elemento
                            } else {
                                anteriorAdyacente->siguiente = actualAdyacente->siguiente; // Eliminar el elemento intermedio
                            }
                            delete actualAdyacente;
                            cout << "Adyacencia eliminada." << endl;
                        }
                        break;
                    }
                    case 3: { // Cambiar distancia de una adyacencia
                        int idAdyacente;
                        cout << "Ingresa el ID de la sala adyacente para cambiar su distancia: ";
                        cin >> idAdyacente;

                        Adyacencia* actualAdyacente = actual->adyacencias;

                        while (actualAdyacente != nullptr && actualAdyacente->salaDestino->id != idAdyacente) {
                            actualAdyacente = actualAdyacente->siguiente;
                        }

                        if (actualAdyacente == nullptr) {
                            cout << "Adyacencia no encontrada." << endl;
                        } else {
                            int nuevaDistancia;
                            while (true) {
                                cout << "Ingresa la nueva distancia para la adyacencia: ";
                                string input;
                                cin >> input;
                                nuevaDistancia = convertirAEntero(input);
                                if (nuevaDistancia != -1) break;
                            }
                            actualAdyacente->distancia = nuevaDistancia;
                            cout << "Distancia actualizada." << endl;
                        }
                        break;
                    }
                    case 4:
                        continuar = 'n';
                        break;
                    default:
                        cout << "Opción no válida. Intenta de nuevo" << endl;
                }
            } while (continuar != 'n');
            actual->nombre = nuevoNombre;
            cout << "Sala modificada." << endl;
        }

        void leerArchivo(const string& nombreArchivo) {
            ifstream archivo(nombreArchivo);
            if (!archivo.is_open()) {
                cout << "Error al abrir el archivo." << endl;
                return;
            }

            string linea;
            int cantidadSalas;
            getline(archivo, linea);
            cantidadSalas = convertirAEntero(linea); // Leer la cantidad de salas
            if (cantidadSalas == -1) return; // Salir si hay un error

            // Primera pasada: Crear todas las salas sin adyacencias
            while (getline(archivo, linea)) {
                if (linea == "---") continue; // Separador entre registros

                // Leer ID de la sala
                int id = convertirAEntero(linea);
                if (id == -1) return; // Salir si hay un error

                getline(archivo, linea); // Leer nombre de la sala
                string nombre = linea;

                // Crear la sala sin adyacencias (temporalmente nullptr)
                agregarSala(id, nombre, nullptr);

                getline(archivo, linea); // Leer el separador "--"
                getline(archivo, linea); // Leer adyacencias (ignorar por ahora)
                getline(archivo, linea); // Leer el separador "---"
            }

            // Reiniciar la lectura del archivo para la segunda pasada
            archivo.clear();
            archivo.seekg(0, ios::beg);
            
            // Saltar la primera línea (cantidad de salas)
            getline(archivo, linea);

            // Segunda pasada: Asignar adyacencias
            while (getline(archivo, linea)) {
                if (linea == "---") continue;

                // Leer ID de la sala
                int id = convertirAEntero(linea);
                if (id == -1) return;

                getline(archivo, linea); // Leer nombre (ignorar en esta pasada)
                getline(archivo, linea); // Leer el separador "--"
                getline(archivo, linea); // Leer adyacencias

                Sala* salaActual = obtenerSalaPorId(id);
                if (!salaActual) continue;

                Adyacencia* adyacencias = nullptr;
                Adyacencia* ultimoAdyacente = nullptr;

                if (!linea.empty()) {
                    stringstream ss(linea);
                    string adyacente;
                    while (getline(ss, adyacente, '|')) {
                        size_t pos = adyacente.find(':');
                        if (pos == string::npos) {
                            cout << "Error: formato de adyacente incorrecto: " << adyacente << endl;
                            continue;
                        }

                        int idAdyacente = convertirAEntero(adyacente.substr(0, pos));
                        int distancia = convertirAEntero(adyacente.substr(pos + 1));

                        if (idAdyacente == -1 || distancia == -1) continue;

                        Sala* salaAdyacente = obtenerSalaPorId(idAdyacente);
                        if (!salaAdyacente) {
                            cout << "Error: Sala adyacente no encontrada para ID: " << idAdyacente << endl;
                            continue;
                        }

                        Adyacencia* nuevoAdyacente = new Adyacencia{salaAdyacente, distancia, nullptr};
                        if (adyacencias == nullptr) {
                            adyacencias = nuevoAdyacente;
                        } else {
                            ultimoAdyacente->siguiente = nuevoAdyacente;
                        }
                        ultimoAdyacente = nuevoAdyacente;
                    }
                }

                salaActual->adyacencias = adyacencias;
                getline(archivo, linea); // Leer el separador "---"
            }

            archivo.close();
        }

        void buscarSalasMasAptas() {
            // Primero: limpiar las marcas de visita
            Sala* temp = cabeza;
            while (temp != nullptr) {
                temp->apto = false;
                temp = temp->siguiente;
            }

            int maxSalas = 0;
            Sala* salaMasApta = nullptr;

            // Implementación manual de pila para DFS
            Sala** pila = new Sala*[100]; // Asumiendo un máximo de 100 salas
            int tope = -1;

            temp = cabeza;
            while (temp != nullptr) {
                if (!temp->apto) {
                    int contadorSalas = 0;
                    Sala* salaInicio = temp;

                    // DFS manual
                    pila[++tope] = temp;
                    while (tope >= 0) {
                        Sala* actual = pila[tope--];
                        
                        if (!actual->apto) {
                            actual->apto = true;
                            contadorSalas++;

                            // Procesar adyacencias
                            Adyacencia* ady = actual->adyacencias;
                            while (ady != nullptr) {
                                Sala* vecina = ady->salaDestino;
                                if (vecina && !vecina->apto) {
                                    pila[++tope] = vecina;
                                }
                                ady = ady->siguiente;
                            }
                        }
                    }

                    if (contadorSalas > maxSalas) {
                        maxSalas = contadorSalas;
                        salaMasApta = salaInicio;
                    }
                }
                temp = temp->siguiente;
            }
            delete[] pila;

            // Limpiar marcas excepto para el subgrafo más grande
            if (salaMasApta) {
                // Resetear todas las marcas primero
                temp = cabeza;
                while (temp != nullptr) {
                    temp->apto = false;
                    temp = temp->siguiente;
                }

                // Marcar solo el subgrafo más grande
                Sala** pila = new Sala*[100];
                int tope = -1;
                pila[++tope] = salaMasApta;

                while (tope >= 0) {
                    Sala* actual = pila[tope--];
                    
                    if (!actual->apto) {
                        actual->apto = true;
                        
                        Adyacencia* ady = actual->adyacencias;
                        while (ady != nullptr) {
                            Sala* vecina = ady->salaDestino;
                            if (vecina && !vecina->apto) {
                                pila[++tope] = vecina;
                            }
                            ady = ady->siguiente;
                        }
                    }
                }
                delete[] pila;
            }

            // Mostrar resultados
            if (salaMasApta != nullptr) {
                cout << "El conjunto de salas más aptas tiene poco más de " << maxSalas << " salas." << endl;
            } else {
                cout << "No se encontraron salas aptas." << endl;
            }
        }

        pair <Sala*, Sala*> buscarExtremosDeSalas() {
            if (cabeza == nullptr) {
                cout << "No hay salas registradas." << endl;
                return {nullptr, nullptr};
            }

            // Primero seleccionar cualquier sala apta como punto de inicio
            Sala* salaActual = cabeza;
            Sala* salaInicio = nullptr;
            while (salaActual != nullptr && salaInicio == nullptr) {
                if (salaActual->apto) {
                    salaInicio = salaActual;
                }
                salaActual = salaActual->siguiente;
            }

            if (salaInicio == nullptr) {
                cout << "No hay salas aptas disponibles." << endl;
                return {nullptr, nullptr};
            }

            // Limpiar marcas de visita y distancias
            salaActual = cabeza;
            while (salaActual != nullptr) {
                salaActual->visitada = false;
                salaActual->distanciaAcumulada = 0;
                salaActual = salaActual->siguiente;
            }

            // Implementar BFS con cola manual para encontrar el extremo más lejano
            Sala** cola = new Sala*[100];
            int frente = 0;
            int final = 0;
            
            cola[final++] = salaInicio;
            salaInicio->visitada = true;
            salaInicio->distanciaAcumulada = 0;
            
            Sala* extremoHeroes = salaInicio;
            int maxDistancia = 0;

            while (frente < final) {
                Sala* actual = cola[frente++];
                
                Adyacencia* ady = actual->adyacencias;
                while (ady != nullptr) {
                    Sala* vecina = ady->salaDestino;
                    if (vecina && vecina->apto && !vecina->visitada) {
                        vecina->visitada = true;
                        vecina->distanciaAcumulada = actual->distanciaAcumulada + ady->distancia;
                        cola[final++] = vecina;
                        
                        if (vecina->distanciaAcumulada > maxDistancia) {
                            maxDistancia = vecina->distanciaAcumulada;
                            extremoHeroes = vecina;
                        }
                    }
                    ady = ady->siguiente;
                }
            }

            // Segundo BFS desde el extremo hallado para encontrar el verdadero extremo opuesto
            // Resetear visitas y distancias
            salaActual = cabeza;
            while (salaActual != nullptr) {
                salaActual->visitada = false;
                salaActual->distanciaAcumulada = 0;
                salaActual = salaActual->siguiente;
            }

            frente = 0;
            final = 0;
            cola[final++] = extremoHeroes;
            extremoHeroes->visitada = true;
            
            Sala* extremoOrcos = extremoHeroes;
            maxDistancia = 0;

            while (frente < final) {
                Sala* actual = cola[frente++];
                
                Adyacencia* ady = actual->adyacencias;
                while (ady != nullptr) {
                    Sala* vecina = ady->salaDestino;
                    if (vecina && vecina->apto && !vecina->visitada) {
                        vecina->visitada = true;
                        vecina->distanciaAcumulada = actual->distanciaAcumulada + ady->distancia;
                        cola[final++] = vecina;
                        
                        if (vecina->distanciaAcumulada > maxDistancia) {
                            maxDistancia = vecina->distanciaAcumulada;
                            extremoOrcos = vecina;
                        }
                    }
                    ady = ady->siguiente;
                }
            }

            delete[] cola;

            // Mostrar resultados
            cout << "--------------------------------------------------" << endl;
            cout << " Punto de Partida de Heroes: " << extremoHeroes->nombre 
                << " (ID: " << extremoHeroes->id << ")" << endl;
            cout << " Punto de Generación de Orcos: " << extremoOrcos->nombre 
                << " (ID: " << extremoOrcos->id << ")" << endl;
            cout << " Distancia máxima total entre extremos: " << maxDistancia << endl;
            cout << "--------------------------------------------------" << endl;

            return{extremoHeroes, extremoOrcos};
        }

        void mostrarMapaAdyacencias(Sala* salaActual, int rapidezEquipo = -1) {
            if (!salaActual) {
                cout << "Sala no válida." << endl;
                return;
            }
            
            if (rapidezEquipo == -1) {
                cout << "Mapa de adyacencias para la sala: " << salaActual->nombre << endl;
                cout << left << setw(5) << "ID" 
                    << setw(30) << "Nombre" 
                    << setw(20) << "Distancia" << endl;
                cout << string(75, '-') << endl;
                Adyacencia* ady = salaActual->adyacencias;
                while (ady != nullptr) {
                    Sala* salaAdyacente = ady->salaDestino;
                    if (salaAdyacente) {
                        cout << left << setw(5) << salaAdyacente->id 
                            << setw(30) << salaAdyacente->nombre 
                            << setw(20) << ady->distancia << endl;
                    }
                    ady = ady->siguiente;
                }
                cout << string(75, '-') << endl;
            } else {
                cout << "Mapa de salas alcanzables desde: " << salaActual->nombre << endl;
                cout << "Rapidez del equipo: " << rapidezEquipo << endl;
                cout << left << setw(5) << "ID" 
                    << setw(30) << "Nombre" 
                    << setw(15) << "Distancia"
                    << setw(15) << "Salas en ruta"
                    << setw(15) << "Alcanzable" << endl;
                cout << string(90, '-') << endl;
                
                // Usar BFS para encontrar todas las salas alcanzables con conteo de salas
                Sala* visitadas[100];
                int distancias[100];
                int salasEnRuta[100];
                Sala* padres[100];
                int numVisitadas = 0;
                
                // Cola manual para BFS
                Sala* cola[100];
                int distanciasCola[100];
                int salasRutaCola[100];
                int frente = 0, final = 0;
                
                cola[final] = salaActual;
                distanciasCola[final] = 0;
                salasRutaCola[final] = 0;
                final++;
                
                visitadas[numVisitadas] = salaActual;
                distancias[numVisitadas] = 0;
                salasEnRuta[numVisitadas] = 0;
                padres[numVisitadas] = nullptr;
                numVisitadas++;
                
                while (frente < final) {
                    Sala* actual = cola[frente];
                    int distanciaActual = distanciasCola[frente];
                    int salasActuales = salasRutaCola[frente];
                    frente++;
                    
                    Adyacencia* ady = actual->adyacencias;
                    while (ady != nullptr) {
                        Sala* vecina = ady->salaDestino;
                        int nuevaDistancia = distanciaActual + ady->distancia;
                        int nuevasSalas = salasActuales + 1;  // Cada sala visitada cuenta como +1
                        
                        // Verificar si ya fue visitada
                        bool yaVisitada = false;
                        for (int i = 0; i < numVisitadas; i++) {
                            if (visitadas[i] == vecina) {
                                yaVisitada = true;
                                break;
                            }
                        }
                        
                        if (!yaVisitada && nuevaDistancia <= rapidezEquipo) {
                            visitadas[numVisitadas] = vecina;
                            distancias[numVisitadas] = nuevaDistancia;
                            salasEnRuta[numVisitadas] = nuevasSalas;
                            padres[numVisitadas] = actual;
                            numVisitadas++;
                            
                            cola[final] = vecina;
                            distanciasCola[final] = nuevaDistancia;
                            salasRutaCola[final] = nuevasSalas;
                            final++;
                        }
                        ady = ady->siguiente;
                    }
                }
                
                // Mostrar resultados
                for (int i = 0; i < numVisitadas; i++) {
                    if (visitadas[i] != salaActual) {
                        cout << left << setw(5) << visitadas[i]->id 
                            << setw(30) << visitadas[i]->nombre 
                            << setw(15) << distancias[i]
                            << setw(15) << salasEnRuta[i]
                            << setw(15) << "Sí" << endl;
                    }
                }
                cout << string(90, '-') << endl;
            }
        }

        void mostrarMapaSalasAptas() {
            if (cabeza == nullptr) {
                cout << "No hay salas registradas." << endl;
                return;
            }

            cout << "\n=== Mapa de Salas Aptas ===\n";
            cout << left << setw(5) << "ID" 
                << setw(30) << "Nombre" 
                << setw(20) << "Sala del Destino" << endl;
            cout << string(60, '-') << endl;

            Sala* actual = cabeza;
            while (actual != nullptr) {
                if (actual->apto) { // Solo mostrar salas aptas
                    cout << left << setw(5) << actual->id 
                        << setw(30) << actual->nombre 
                        << setw(20) << (actual->PuertaDelDestino ? "Sí" : "No") << endl;
                }
                actual = actual->siguiente;
            }
            cout << string(60, '-') << endl; 
        }

        void asignarPuertaDelDestino() {
            srand(static_cast<unsigned int>(time(0)));

            int contadorSalasAptas = 0;
            Sala* actual = cabeza;

            while (actual != nullptr) {
                if (actual->apto && actual->pddApto) {
                    contadorSalasAptas++;
                }
                actual = actual->siguiente;
            }

            if (contadorSalasAptas > 0) {
                int indiceAleatorio = rand() % contadorSalasAptas;
                actual = cabeza;
                int contador = 0;

                while (actual != nullptr) {
                    if (actual->apto && actual->pddApto) {
                        if (contador == indiceAleatorio) {
                            actual->PuertaDelDestino = true;
                            actual->pddApto = false;
                            cout << "La Puerta del Destino ha aparecido en la sala: " << actual->nombre << endl;
                            return;
                        }
                        contador++;
                    }
                    actual = actual->siguiente;
                }
            } else {
                cout << "No hay salas aptas para asignar la Puerta del Destino." << endl;
            }
        }

        bool existePuertaDelDestino() {
            Sala* actual = cabeza;
            while (actual != nullptr) {
                if (actual->PuertaDelDestino && actual->apto) {
                    return true;
                }
                actual = actual->siguiente;
            }
            return false;
        }

        especie* obtenerEspecieOrcoAleatoria(listaEspecies& listaEspecies) {
            int contadorOrcos = 0;
            especie* temp = listaEspecies.obtenerCabeza();
            while (temp != nullptr) {
                if (temp->tipo == "Orco") {
                    contadorOrcos++;
                }
                temp = temp->siguiente;
            }
            
            if (contadorOrcos == 0) return nullptr;
            
            int indiceAleatorio = rand() % contadorOrcos;
            temp = listaEspecies.obtenerCabeza();
            int contador = 0;
            
            while (temp != nullptr) {
                if (temp->tipo == "Orco") {
                    if (contador == indiceAleatorio) {
                        return temp;
                    }
                    contador++;
                }
                temp = temp->siguiente;
            }
            return nullptr;
        }

        void generarYDispersarOrcos(int cantRondas, listaEspecies& listaEspecies, Sala* salaOrigenOrcos) {
            srand(static_cast<unsigned int>(time(0)) + cantRondas);
            
            int numOrcosGenerar = (rand() % 5) + 1;
            
            cout << "\n=== RONDA " << cantRondas << " ===\n";
            cout << "Generando " << numOrcosGenerar << " orcos...\n";
            
            for (int i = 0; i < numOrcosGenerar; i++) {
                if (salaOrigenOrcos->equipoOrcos.numMiembros < 15) {
                    especie* orcoAleatorio = obtenerEspecieOrcoAleatoria(listaEspecies);
                    if (orcoAleatorio != nullptr) {
                        salaOrigenOrcos->equipoOrcos.miembros[salaOrigenOrcos->equipoOrcos.numMiembros] = orcoAleatorio;
                        salaOrigenOrcos->equipoOrcos.numMiembros++;
                        cout << "- " << orcoAleatorio->nombre << " generado en " << salaOrigenOrcos->nombre << "\n";
                    }
                }
            }
            dispersarOrcosAdyacentes(cantRondas);
        }

        void dispersarOrcosAdyacentes(int cantRondas) {
            // Determinar número de ondas basado en el último dígito de la ronda
            int ultimoDigito = cantRondas % 10;
            int maxOndas;
            
            if (ultimoDigito == 0) {
                maxOndas = 5;
                cout << "Ronda " << cantRondas << " (ultimo digito " << ultimoDigito << "): 5 ondas de dispersion (SUPER EXPANSION!)\n";
            } else if (ultimoDigito == 1 || ultimoDigito == 3 || ultimoDigito == 6 || ultimoDigito == 9) {
                maxOndas = 3;
                cout << "Ronda " << cantRondas << " (ultimo digito " << ultimoDigito << "): 3 ondas de dispersion\n";
            } else if (ultimoDigito == 2 || ultimoDigito == 4 || ultimoDigito == 8) {
                maxOndas = 2;
                cout << "Ronda " << cantRondas << " (ultimo digito " << ultimoDigito << "): 2 ondas de dispersion\n";
            } else { // Para 5 y 7
                maxOndas = 1;
                cout << "Ronda " << cantRondas << " (ultimo digito " << ultimoDigito << "): 1 onda de dispersion\n";
            }
            
            for (int onda = 0; onda < maxOndas; onda++) {
                cout << "--- Onda de dispersion " << (onda + 1) << " de " << maxOndas << " ---\n";
                
                // Lista temporal para almacenar movimientos de esta onda
                struct MovimientoOrco {
                    Sala* origen;
                    Sala* destino;
                    especie* orco;
                };
                MovimientoOrco movimientos[100]; // Asumiendo máximo 100 movimientos por onda
                int numMovimientos = 0;
                
                // Fase 1: Planificar movimientos
                Sala* actual = cabeza;
                while (actual != nullptr) {
                    if (actual->apto && actual->equipoOrcos.numMiembros > 0) {
                        // Calcular cuántos orcos mover (más agresivo pero controlado)
                        int orcosParaMover = max(1, actual->equipoOrcos.numMiembros / 2);
                        
                        // Crear lista de salas destino disponibles
                        Sala* salasDestino[20];
                        int numDestinos = 0;
                        
                        Adyacencia* ady = actual->adyacencias;
                        while (ady != nullptr) {
                            Sala* salaAdyacente = ady->salaDestino;
                            if (salaAdyacente && salaAdyacente->apto && 
                                salaAdyacente->equipoOrcos.numMiembros < 15) {
                                salasDestino[numDestinos++] = salaAdyacente;
                            }
                            ady = ady->siguiente;
                        }
                        
                        // Planificar movimientos para esta sala
                        for (int i = 0; i < orcosParaMover && i < actual->equipoOrcos.numMiembros && numDestinos > 0; i++) {
                            // Seleccionar destino (priorizar salas con menos orcos)
                            Sala* mejorDestino = nullptr;
                            int menorCantidad = 16; // Mayor que el límite
                            
                            for (int j = 0; j < numDestinos; j++) {
                                if (salasDestino[j]->equipoOrcos.numMiembros < menorCantidad) {
                                    menorCantidad = salasDestino[j]->equipoOrcos.numMiembros;
                                    mejorDestino = salasDestino[j];
                                }
                            }
                            
                            if (mejorDestino && numMovimientos < 100) {
                                movimientos[numMovimientos].origen = actual;
                                movimientos[numMovimientos].destino = mejorDestino;
                                movimientos[numMovimientos].orco = actual->equipoOrcos.miembros[i];
                                numMovimientos++;
                            }
                        }
                    }
                    actual = actual->siguiente;
                }
                
                // Fase 2: Ejecutar movimientos
                for (int i = 0; i < numMovimientos; i++) {
                    MovimientoOrco& mov = movimientos[i];
                    
                    // Verificar que el movimiento sigue siendo válido
                    if (mov.destino->equipoOrcos.numMiembros < 15) {
                        // Encontrar el orco en la sala origen
                        for (int j = 0; j < mov.origen->equipoOrcos.numMiembros; j++) {
                            if (mov.origen->equipoOrcos.miembros[j] == mov.orco) {
                                // Remover orco de la sala origen
                                for (int k = j; k < mov.origen->equipoOrcos.numMiembros - 1; k++) {
                                    mov.origen->equipoOrcos.miembros[k] = mov.origen->equipoOrcos.miembros[k + 1];
                                }
                                mov.origen->equipoOrcos.numMiembros--;
                                
                                // Agregar orco a la sala destino
                                mov.destino->equipoOrcos.miembros[mov.destino->equipoOrcos.numMiembros] = mov.orco;
                                mov.destino->equipoOrcos.numMiembros++;
                                
                                cout << "- " << mov.orco->nombre << " se movio de " << mov.origen->nombre 
                                    << " a " << mov.destino->nombre << " (Onda " << (onda + 1) << ")\n";
                                break;
                            }
                        }
                    }
                }
                
                // Si no hay movimientos en esta onda, terminar
                if (numMovimientos == 0) {
                    cout << "No hay mas movimientos posibles en esta onda.\n";
                    break;
                }
            }
            
            cout << "Dispersion completada.\n";
        }

        bool verificarEncuentroConOrcos(Sala* salaHeroes) {
            if (salaHeroes && salaHeroes->equipoOrcos.numMiembros > 0) {
                cout << "\n¡ALERTA! ¡Hay " << salaHeroes->equipoOrcos.numMiembros << " orcos en esta sala!\n";
                cout << "Orcos presentes:\n";
                for (int i = 0; i < salaHeroes->equipoOrcos.numMiembros; i++) {
                    especie* orco = salaHeroes->equipoOrcos.miembros[i];
                    cout << "- " << orco->nombre << " (Ataque: " << orco->ataque << ", Salud: " << orco->salud << ")\n";
                }
                return true;
            }
            return false;
        }

        void mostrarDistribucionOrcos() {
            cout << "\n=== Distribución de Orcos por Sala ===\n";
            cout << left << setw(5) << "ID" 
                << setw(30) << "Nombre de Sala" 
                << setw(15) << "Num. Orcos" 
                << setw(30) << "Tipos de Orcos" << endl;
            cout << string(80, '-') << endl;
            
            Sala* actual = cabeza;
            while (actual != nullptr) {
                if (actual->apto) {
                    cout << left << setw(5) << actual->id 
                        << setw(30) << actual->nombre 
                        << setw(15) << actual->equipoOrcos.numMiembros;
                    
                    if (actual->equipoOrcos.numMiembros > 0) {
                        string tiposOrcos = "";
                        for (int i = 0; i < actual->equipoOrcos.numMiembros; i++) {
                            tiposOrcos += actual->equipoOrcos.miembros[i]->nombre;
                            if (i < actual->equipoOrcos.numMiembros - 1) {
                                tiposOrcos += ", ";
                            }
                        }
                        cout << setw(30) << tiposOrcos;
                    } else {
                        cout << setw(30) << "Ninguno";
                    }
                    cout << endl;
                }
                actual = actual->siguiente;
            }
            cout << string(80, '-') << endl;
        }
    };

//Funciones del Juego
bool verificarVictoria(Sala* salaHeroes) {
    if (salaHeroes && salaHeroes->PuertaDelDestino) {
        cout << "\n¡¡¡VICTORIA!!!\n";
        cout << "¡Has encontrado la Puerta del Destino!\n";
        cout << "Gandalf aparece y te ayuda a escapar del subterraneo.\n";
        cout << "¡Has ganado el juego!\n";
        return true;
    }
    return false;
}
void elegirEquipo(listaEquipos& listaEquipos, listaPersonajes& listaPersonajes, equipo*& equipoSeleccionado) {
    int opcion;
    bool equipoValido = false;
    while (!equipoValido) {
        cout << "\n¿Quieres elegir un equipo precreado o crear uno nuevo?" << endl;
        cout << "1. Elegir equipo precreado" << endl;
        cout << "2. Crear un nuevo equipo" << endl;
        cout << "Selecciona una opción (1 o 2): ";
        opcion = leerOpcion();
        if (opcion == 1) {
            equipo* equipoElegido = listaEquipos.seleccionarEquipoPorIndice();
            if (equipoElegido != nullptr) {
                equipoSeleccionado = equipoElegido; // Asignar puntero
                cout << "Has elegido el equipo: " << equipoSeleccionado->nombre << endl;
                equipoValido = true;
            } else {
                cout << "No hay equipos precreados disponibles. Por favor, crea un nuevo equipo." << endl;
            }
        } else if (opcion == 2) {
            listaEquipos.agregarEquipo(listaPersonajes);
            cout << "Ahora selecciona el equipo recién creado:" << endl;
        } else {
            cout << "Opción no válida. Por favor, selecciona 1 o 2." << endl;
        }
    }
}
int calcularRapidezEquipo(equipo& equipoSeleccionado) {
    int rapidezMinima = INT_MAX;
    for (int i = 0; i < equipoSeleccionado.numPjs; i++) {
        personaje* pj = equipoSeleccionado.personajes[i];
        if (pj != nullptr && pj->especie != nullptr) {
            rapidezMinima = min(rapidezMinima, static_cast<int>(pj->especie->rapidez));
        }
    }
    return rapidezMinima;
}
int moverHeroes(listaSalas& listaSalas, equipo& equipoSeleccionado, Sala*& salaHeroes, listaEspecies& listaEspecies, Sala* salaOrcos, int& cantRondas) {
    int rapidezEquipo = calcularRapidezEquipo(equipoSeleccionado);
    int turnosExtra = 0;
    
    cout << "\n=== Movimiento del Equipo ===" << endl;
    cout << "Rapidez total disponible: " << rapidezEquipo << endl;
    
    cout << "\nSala actual: " << salaHeroes->nombre << " (ID: " << salaHeroes->id << ")" << endl;        
    listaSalas.mostrarMapaAdyacencias(salaHeroes, rapidezEquipo);
    
    Adyacencia* ady = salaHeroes->adyacencias;
    bool haySalasAlcanzables = false;
    
    while (ady != nullptr) {
        if (ady->distancia <= rapidezEquipo) {
            haySalasAlcanzables = true;
            break;
        }
        ady = ady->siguiente;
    }
    
    if (!haySalasAlcanzables) {
        cout << "No hay salas alcanzables con la rapidez disponible." << endl;
        return 0;
    }
    
    cout << "Selecciona el ID de la sala a la que deseas moverte: ";
    int idSeleccionada = leerOpcion();
    
    // Buscar la sala destino directamente en las adyacencias primero
    Adyacencia* adyDirecta = salaHeroes->adyacencias;
    bool esAdyacenteDirecto = false;
    int distanciaDirecta = 0;
    
    while (adyDirecta != nullptr) {
        if (adyDirecta->salaDestino->id == idSeleccionada && adyDirecta->distancia <= rapidezEquipo) {
            esAdyacenteDirecto = true;
            distanciaDirecta = adyDirecta->distancia;
            break;
        }
        adyDirecta = adyDirecta->siguiente;
    }
    
    if (esAdyacenteDirecto) {
        // Movimiento directo a sala adyacente
        salaHeroes = adyDirecta->salaDestino;
        turnosExtra = 0; // NO generar turnos extra para 1 sala
        
        cout << "Te has movido directamente a: " << salaHeroes->nombre << endl;
        cout << "Distancia recorrida: " << distanciaDirecta << endl;
        cout << "Salas recorridas: 1" << endl;
        cout << "No se generan turnos extra (solo 1 sala recorrida)" << endl;
        
        // Generar orcos DESPUÉS del movimiento para el turno principal
        if (cantRondas >= 1) {
            cout << "\n--- Generación de orcos después del movimiento ---" << endl;
            listaSalas.generarYDispersarOrcos(cantRondas, listaEspecies, salaOrcos);
        }
        
        if (listaSalas.verificarEncuentroConOrcos(salaHeroes)) {
            cout << "¡Encuentro con orcos! Debes luchar o huir." << endl;
        }
        
    } else {
        // Buscar camino usando BFS para salas no adyacentes
        Sala* visitadas[100];
        int distancias[100];
        int salasEnRuta[100];
        Sala* padres[100];
        int numVisitadas = 0;
        
        // Cola manual para BFS
        Sala* cola[100];
        int distanciasCola[100];
        int salasRutaCola[100];
        int frente = 0, final = 0;
        
        cola[final] = salaHeroes;
        distanciasCola[final] = 0;
        salasRutaCola[final] = 0;
        final++;
        
        visitadas[numVisitadas] = salaHeroes;
        distancias[numVisitadas] = 0;
        salasEnRuta[numVisitadas] = 0;
        padres[numVisitadas] = nullptr;
        numVisitadas++;
        
        Sala* salaDestino = nullptr;
        int distanciaDestino = 0;
        int salasDestino = 0;
        
        while (frente < final && !salaDestino) {
            Sala* actual = cola[frente];
            int distanciaActual = distanciasCola[frente];
            int salasActuales = salasRutaCola[frente];
            frente++;
            
            if (actual->id == idSeleccionada) {
                salaDestino = actual;
                distanciaDestino = distanciaActual;
                salasDestino = salasActuales;
                break;
            }
            
            Adyacencia* ady = actual->adyacencias;
            while (ady != nullptr) {
                Sala* vecina = ady->salaDestino;
                int nuevaDistancia = distanciaActual + ady->distancia;
                int nuevasSalas = salasActuales + 1;
                
                // Verificar si ya fue visitada
                bool yaVisitada = false;
                for (int i = 0; i < numVisitadas; i++) {
                    if (visitadas[i] == vecina) {
                        yaVisitada = true;
                        break;
                    }
                }
                
                if (!yaVisitada && nuevaDistancia <= rapidezEquipo) {
                    visitadas[numVisitadas] = vecina;
                    distancias[numVisitadas] = nuevaDistancia;
                    salasEnRuta[numVisitadas] = nuevasSalas;
                    padres[numVisitadas] = actual;
                    numVisitadas++;
                    
                    cola[final] = vecina;
                    distanciasCola[final] = nuevaDistancia;
                    salasRutaCola[final] = nuevasSalas;
                    final++;
                }
                ady = ady->siguiente;
            }
        }
        
        if (salaDestino && distanciaDestino <= rapidezEquipo) {
            salaHeroes = salaDestino;
            turnosExtra = salasDestino;
            
            cout << "Te has movido a: " << salaHeroes->nombre << endl;
            cout << "Distancia recorrida: " << distanciaDestino << endl;
            cout << "Salas recorridas en el camino: " << salasDestino << endl;
            
            // Generar orcos DESPUÉS del movimiento para el turno principal
            if (cantRondas >= 1) {
                cout << "\n--- Generación de orcos después del movimiento principal ---" << endl;
                listaSalas.generarYDispersarOrcos(cantRondas, listaEspecies, salaOrcos);
            }
            
            if (listaSalas.verificarEncuentroConOrcos(salaHeroes)) {
                cout << "¡Encuentro con orcos! Debes luchar o huir." << endl;
            }
            
            // Solo generar turnos extra si se recorrieron 2 o más salas
            if (salasDestino >= 2) {
                cout << "Generando " << (salasDestino - 1) << " turnos extra..." << endl;
                for (int i = 0; i < salasDestino - 1; i++) { // -1 porque el turno principal ya cuenta
                    cantRondas++;
                    cout << "\n--- Turno Extra " << cantRondas << " ---" << endl;
                    listaSalas.generarYDispersarOrcos(cantRondas, listaEspecies, salaOrcos);
                }
            } else {
                cout << "No se generan turnos extra (menos de 2 salas recorridas)" << endl;
            }
        } else {
            cout << "No puedes moverte a esa sala o no es alcanzable." << endl;
            return 0;
        }
    }
    
    return turnosExtra;
}
void menuJuego(listaEspecies& listaEspecies, listaPersonajes& listaPersonajes, listaEquipos& listaEquipos, listaImplementos& listaImplementos, listaSalas& listaSalas, equipo*& equipoSeleccionado) {
    cout << "Seleccione su equipo" << endl;
    elegirEquipo(listaEquipos, listaPersonajes, equipoSeleccionado);
    cout << endl;
    auto extremos = listaSalas.buscarExtremosDeSalas();
    Sala* salaHeroes = extremos.first;
    Sala* salaOrcos = extremos.second;
    listaSalas.asignarPuertaDelDestino();
    cout << endl;
    cout << "Bienvenido a Khazad-Dum" << endl;
    cout << "Llega a la Puerta del Destino en los túneles ancestrales para invocar la ayuda de Gandalf." << endl;

    int cantRondas = 0;
    
    while (true) {
        if (verificarVictoria(salaHeroes)) {
            break;
        }

        if (cantRondas % 5 == 0 && cantRondas > 0) {
            listaSalas.asignarPuertaDelDestino();
        }

        if (!listaSalas.existePuertaDelDestino() && cantRondas > 0) {
            cout << "La Puerta del Destino ha recorrido todas las salas y no has llegado a tiempo." << endl;
            cout << "¡Los orcos han invadido todo el subterráneo! ¡HAS PERDIDO!" << endl;
            break;
        }

        int op;
        cout << "\n--- Menú del Juego (Ronda " << cantRondas + 1 << ") ---" << endl;
        cout << "1. Moverse entre salas" << endl;
        cout << "2. Mostrar mapa" << endl;
        cout << "3. Usar implementos" << endl;
        cout << "4. Terminar Juego." << endl;
        cout << "Selecciona una opción: ";
        op = leerOpcion();

        switch (op) {
            case 1: {
                ++cantRondas;

                cout << "\n=== RONDA " << cantRondas << " ===\n";
                
                if (listaSalas.verificarEncuentroConOrcos(salaHeroes)) {
                    cout << "Debes luchar o huir!\n";
                }
                
                int turnosExtra = moverHeroes(listaSalas, *equipoSeleccionado, salaHeroes, listaEspecies, salaOrcos, cantRondas);
                
                cout << "Movimiento completado. Turnos extra generados: " << turnosExtra << endl;
                break;
            }
            case 2: {
                listaSalas.mostrarMapaSalasAptas();
                break;
            }
            case 3: {
                cout << "Funcionalidad de usar implementos no implementada aún." << endl;
                break;
            }
            case 4: {
                cout << "¿Estás seguro de querer salir? (Si/No): ";
                string opcion;
                cin >> opcion;
                if (opcion == "Si" || opcion == "si" || opcion == "SI" || opcion == "sI") {
                    cout << "Juego terminado." << endl;
                    return;
                }
                break;
            }
            default: {
                cout << "Opción no válida. Intenta de nuevo." << endl;
                break;
            }
        }
    }
    
    return;
}

// Función para eliminar espacios en blanco al inicio y final de una cadena
string trimear(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
// Carga de Especies
void leerEspeciesDesdeArchivo(listaEspecies& lista, const string& archivo) {
    ifstream archivoIn(archivo);
    if (!archivoIn.is_open()) {
        cout << "No se pudo abrir el archivo de especies.\n";
        return;
    }

    string linea;
    int cantidadEspecies;
    
    // Leer cantidad de especies
    getline(archivoIn, linea);
    cantidadEspecies = atoi(trimear(linea).c_str());
    
    for (int i = 0; i < cantidadEspecies; i++) {
        // Leer separador "---"
        getline(archivoIn, linea);
        
        // Leer ID (ignorar)
        getline(archivoIn, linea);
        
        // Leer nombre
        string nombre;
        getline(archivoIn, nombre);
        nombre = trimear(nombre);
        
        // Leer fortaleza o ataque
        getline(archivoIn, linea);
        linea = trimear(linea);
        int fortaleza = 0;
        double ataque = 0;
        string tipo;
        
        if (linea != "-") {
            fortaleza = atoi(linea.c_str());
            tipo = "Heroe";
        }
        
        // Leer ataque (si es orco)
        getline(archivoIn, linea);
        linea = trimear(linea);
        if (linea != "-") {
            ataque = atof(linea.c_str());
            tipo = "Orco";
            fortaleza = 0;
        }
        
        // Leer salud
        getline(archivoIn, linea);
        double salud = atof(trimear(linea).c_str());
        
        // Leer rapidez
        getline(archivoIn, linea);
        double rapidez = atof(trimear(linea).c_str());
        
        lista.agregarEspecie(nombre, tipo, fortaleza, ataque, salud, rapidez);
    }
    
    archivoIn.close();
    cout << "Especies cargadas exitosamente desde " << archivo << "\n";
}
// Carga de Implementos
void leerImplementosDesdeArchivo(listaImplementos& lista, const string& archivo) {
    ifstream archivoIn(archivo);
    if (!archivoIn.is_open()) {
        cout << "No se pudo abrir el archivo de implementos.\n";
        return;
    }

    string linea;
    int cantidadImplementos;
    
    // Leer cantidad de implementos
    getline(archivoIn, linea);
    cantidadImplementos = atoi(trimear(linea).c_str());
    
    for (int i = 0; i < cantidadImplementos; i++) {
        // Leer separador "---"
        getline(archivoIn, linea);
        
        // Leer ID (ignorar)
        getline(archivoIn, linea);
        
        // Leer nombre
        string nombre;
        getline(archivoIn, nombre);
        nombre = trimear(nombre);
        
        // Leer tipo y convertir a formato esperado
        string tipoArchivo;
        getline(archivoIn, tipoArchivo);
        tipoArchivo = trimear(tipoArchivo);
        string tipo;
        if (tipoArchivo == "Arma") {
            tipo = "atacar";
        } else if (tipoArchivo == "Defensa") {
            tipo = "defender";
        } else if (tipoArchivo == "Consumible") {
            tipo = "curar";
        } else {
            tipo = "atacar"; // valor por defecto
        }
        
        // Leer valores
        getline(archivoIn, linea);
        int valor1 = atoi(trimear(linea).c_str());
        
        getline(archivoIn, linea);
        int valor2 = atoi(trimear(linea).c_str());
        
        getline(archivoIn, linea);
        int usos = atoi(trimear(linea).c_str());
        
        // Asignar valores según el tipo
        int valorAtk = 0, valorDef = 0, valorHeal = 0;
        int fortaleza = valor2;
        
        if (tipo == "atacar") {
            valorAtk = valor1;
        } else if (tipo == "defender") {
            valorDef = valor1;
        } else if (tipo == "curar") {
            valorHeal = valor1;
        }
        
        lista.agregarImplemento(nombre, tipo, usos, fortaleza, valorAtk, valorDef, valorHeal);
    }
    
    archivoIn.close();
    cout << "Implementos cargados exitosamente desde " << archivo << "\n";
}
// Carga de Personajes
void leerPersonajesDesdeArchivo(listaPersonajes& lista, const string& archivo) {
    ifstream archivoIn(archivo);
    if (!archivoIn.is_open()) {
        cout << "No se pudo abrir el archivo de personajes.\n";
        return;
    }

    string linea;
    int cantidadPersonajes;
    
    // Leer cantidad de personajes
    getline(archivoIn, linea);
    cantidadPersonajes = atoi(trimear(linea).c_str());
    
    for (int i = 0; i < cantidadPersonajes; i++) {
        // Leer separador "---"
        getline(archivoIn, linea);
        
        // Leer ID (ignorar)
        getline(archivoIn, linea);
        
        // Leer nombre de especie
        string nombreEspecie;
        getline(archivoIn, nombreEspecie);
        nombreEspecie = trimear(nombreEspecie);
        
        // Leer nombre del personaje
        string nombrePersonaje;
        getline(archivoIn, nombrePersonaje);
        nombrePersonaje = trimear(nombrePersonaje);
        
        lista.agregarPersonaje(nombreEspecie, nombrePersonaje);
    }
    
    archivoIn.close();
    cout << "Personajes cargados exitosamente desde " << archivo << "\n";
}

//Funciones del subMenu
void verSubMenuModificar(listaEspecies& listaEspecies, listaPersonajes& listaPersonajes, listaEquipos& listaEquipos, listaImplementos& listaImplementos, listaSalas& listaSalas) {
    int op;
    cout<<"\n-- Modificar Elemento --"<<endl;
    cout<<"1. Especie"<<endl;
    cout<<"2. Personajes"<<endl;
    cout<<"3. Implementos"<<endl;
    cout<<"4. Mochilas"<<endl;
    cout<<"5. Mapa"<<endl;
    cout<<"6. Volver al menu principal"<<endl;
    cout<<"Seleccione una opcion: ";
    op=leerOpcion();
    cout<<"______________________"<<endl;

    switch (op) {
        case 1:
            cout<<"Modificando Especie..."<<endl;
            cout<<"__________________"<<endl;
            listaEspecies.modificarEspecie();
            break;        
        case 2:
            cout<<"Modificando Personaje..."<<endl;
            cout<<"__________________"<<endl;
            listaPersonajes.modificarPersonaje(listaEspecies);
            break;
        case 3:
            cout<<"Modificando Implemento..."<<endl;
            cout<<"__________________"<<endl;
            listaImplementos.modificarImplemento();
            break;
        case 4:
            cout<<"Modificando Mochila..."<<endl;
            cout<<"__________________"<<endl;
            listaPersonajes.manejarMochila(listaImplementos);
            break;
        case 5:
            cout<<"Modificando Sala..."<<endl;
            cout<<"__________________"<<endl;
            listaSalas.modificarSala();
            break;
        case 6:
            return;
    }
} 
void verSubMenuEliminar(listaEspecies& listaEspecies, listaPersonajes& listaPersonajes, listaEquipos& listaEquipos, listaImplementos& listaImplementos, listaSalas& listaSalas) {
    int op;
    cout<<"\n-- Eliminar Elemento --"<<endl;
    cout<<"1. Especie"<<endl;
    cout<<"2. Personajes"<<endl;
    cout<<"3. Implementos"<<endl;
    cout<<"4. Equipos "<<endl;
    cout<<"5. Mapa"<<endl;
    cout<<"6. Volver al menu principal"<<endl;
    cout<<"Seleccione una opcion: ";
    op=leerOpcion();
    cout<<"______________________"<<endl;


    switch (op) {
        case 1:
            cout<<"Eliminando Especie..."<<endl;
            cout<<"__________________"<<endl;
            eliminarEspecie(listaEspecies, listaPersonajes);
            break;        
        case 2:
            cout<<"Eliminando Personaje..."<<endl;
            cout<<"__________________"<<endl;
            listaPersonajes.eliminarPersonaje();
            break;
        case 3:
            cout<<"Eliminando Implemento..."<<endl;
            cout<<"__________________"<<endl;
            listaImplementos.eliminarImplemento();
            break;
        case 4:
            cout<<"Eliminando Equipo..."<<endl;
            cout<<"__________________"<<endl;
            listaEquipos.eliminarEquipo();
            break;
        case 5:
            cout<<"Eliminando Sala..."<<endl;
            cout<<"__________________"<<endl;
            listaSalas.eliminarSala();
            break;
        case 6:
            return;
    }
} 
void verSubMenuAgregar(listaEspecies& listaEspecies, listaPersonajes& listaPersonajes, listaEquipos& listaEquipos, listaImplementos& listaImplementos, listaSalas& listaSalas) {
    int op;
    cout<<"\n-- Crear Elemento --"<<endl;
    cout<<"1. Especie"<<endl;
    cout<<"2. Personajes"<<endl;
    cout<<"3. Implementos"<<endl;
    cout<<"4. Equipos "<<endl;
    cout<<"5. Mapa"<<endl;
    cout<<"6. Volver al menu principal"<<endl;
    cout<<"Seleccione una opcion: ";
    op=leerOpcion();
    cout<<"______________________"<<endl;


    switch (op) {
        case 1:
            cout<<"Creando Especie..."<<endl;
            cout<<"__________________"<<endl;
            listaEspecies.agregarEspecie();
            break;
        case 2:
            cout<<"Creando Personaje..."<<endl;
            cout<<"__________________"<<endl;
            listaPersonajes.agregarPersonaje();
            break;
        case 3:
            cout<<"Creando Implemento..."<<endl;
            cout<<"__________________"<<endl;
            listaImplementos.agregarImplemento();
            break;
        case 4:
            cout<<"Creando Equipo..."<<endl;
            cout<<"__________________"<<endl;
            listaEquipos.agregarEquipo(listaPersonajes);
            break;
        case 5:
            cout<<"Creando Sala..."<<endl;
            cout<<"__________________"<<endl;
            listaSalas.agregarSala();
            break;
        case 6:
            return;
    }
} 
void verSubMenuInformacion(listaEspecies& listaEspecies, listaPersonajes& listaPersonajes, listaEquipos& listaEquipos, listaImplementos& listaImplementos, listaSalas& listaSalas) {
    int op;
    cout<<"\n__Ver Informacion__"<<endl;
    cout<<"1. Especies"<<endl;
    cout<<"2. Personajes"<<endl;
    cout<<"3. Implementos"<<endl;
    cout<<"4. Equipos"<<endl;
    cout<<"5. Mochilas" << endl;
    cout<<"6. Mapa" << endl;
    cout<<"7. Volver al menu principal"<<endl;
    cout<<"Seleccione una opcion: ";
    op=leerOpcion();
    cout<<"______________________"<<endl;


    switch (op) {
        case 1:
            cout<<"Mostrando Especies..."<<endl;
            cout<<"__________________"<<endl;
                listaEspecies.mostrarEspecies();
            break;
        case 2:
            cout<<"Mostrando Personajes..."<<endl;
            cout<<"__________________"<<endl;
                listaPersonajes.mostrarPersonajes();
            break;
        case 3:
            cout<<"Mostrando Implementos..."<<endl;
            cout<<"__________________"<<endl;
            listaImplementos.mostrarImplementos();
            break;
        case 4:
            cout<<"Mostrando Equipos..."<<endl;
            cout<<"__________________"<<endl;
            listaEquipos.mostrarEquipos();
            break;
        case 5:
            cout<<"Mostrando Mochilas..."<<endl;
            cout<<"__________________"<<endl;
            listaPersonajes.mostrarPersonajesConMochilas();
            break;
        case 6:
            cout<<"Mostrando Salas..."<<endl;
            cout<<"__________________"<<endl;
            listaSalas.mostrarSalas();
            break;
        case 7:
            return;
    }
}
void verSubMenuOperaciones(listaEspecies& listaEspecies, listaPersonajes& listaPersonajes, listaEquipos& listaEquipos, listaImplementos& listaImplementos, listaSalas& listaSalas) {
    int op = 0;
    do {
        cout<<"____Menu de Operaciones____"<<endl;
        cout<<"1. Ver Informacion"<<endl;
        cout<<"2. Crear Elemento"<<endl;
        cout<<"3. Eliminar Elemento"<<endl;
        cout<<"4. Modificar Elemento"<<endl;
        cout<<"5. Salir"<<endl;
        cout<<"______________________"<<endl;
        cout<<"Selecciona una opcion: ";
        op=leerOpcion();

        switch (op) {
            case 1:
                verSubMenuInformacion(listaEspecies, listaPersonajes, listaEquipos, listaImplementos, listaSalas);
                break;
            case 2:
                verSubMenuAgregar(listaEspecies, listaPersonajes, listaEquipos, listaImplementos, listaSalas);
                break;
            case 3:
                verSubMenuEliminar(listaEspecies, listaPersonajes, listaEquipos, listaImplementos, listaSalas);
                break;
            case 4:
                verSubMenuModificar(listaEspecies, listaPersonajes, listaEquipos, listaImplementos, listaSalas);
                break;
            case 5:
                cout<<"Saliendo del programa..."<<endl;
                return;
        }
    }while (op!=5);
}

//Menu Principal
void menuInicial(listaEspecies& listaEspecies, listaPersonajes& listaPersonajes, listaEquipos& listaEquipos, listaImplementos& listaImplementos, listaSalas& listaSalas, equipo*& equipoSeleccionado, Sala*& salaActual) {
    int opcion;
    cout << "=====================================\n";
    cout << "      BIENVENIDO A KHAZAD-DÛM\n";
    cout << "=====================================\n";
    cout << "1. Cargar partida\n";
    cout << "2. Nueva partida\n";
    cout << "Selecciona una opción: ";
    opcion = leerOpcion();

    switch (opcion) {
        case 1:
            cout << "\nCargando archivos...\n";

            // Cargar especies, personajes e implementos desde archivos 
            leerEspeciesDesdeArchivo(listaEspecies, "especie.txt");
            leerPersonajesDesdeArchivo(listaPersonajes, "Personajes.txt");
            leerImplementosDesdeArchivo(listaImplementos, "implemento.txt");

            // Cargar y preparar salas
            listaSalas.leerArchivo("salas.txt");
            listaSalas.buscarSalasMasAptas();

            // Verificaciones
            if (listaPersonajes.obtenerCabeza() == nullptr) {
                cout << "No se encontraron personajes cargados.\n";
            }

            cout << "Partida cargada. Iniciando juego...\n\n";
            menuJuego(listaEspecies, listaPersonajes, listaEquipos, listaImplementos, listaSalas, equipoSeleccionado);
            break;

        case 2:
            cout << "\nCreando nueva partida...\n\n";
            verSubMenuOperaciones(listaEspecies, listaPersonajes, listaEquipos, listaImplementos, listaSalas);
            break;

        default:
            cout << "Opción inválida. Intenta nuevamente.\n";
            menuInicial(listaEspecies, listaPersonajes, listaEquipos, listaImplementos, listaSalas, equipoSeleccionado, salaActual);
    }
}

int main() {
    listaEspecies listaEspecies;
    listaPersonajes listaPersonajes(listaEspecies);
    listaEquipos listaEquipos;
    listaImplementos listaImplementos;
    listaSalas listaSalas;
    equipo* equipoSeleccionado = nullptr;
    Sala* salaActual = nullptr;

    // Iniciar el juego
    menuInicial(listaEspecies, listaPersonajes, listaEquipos, listaImplementos, listaSalas, equipoSeleccionado, salaActual);

    return 0;
}
