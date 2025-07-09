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
#include <cfloat>
#include <climits>

using namespace std;

//Funcion para escribir el archivo de registro
void escribirRegistro(const string& mensaje) {
    ofstream archivo("registros.txt", ios::app);
    if (archivo.is_open()) {
        archivo << mensaje << endl;
        archivo.close();
    }
}

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
        Sala* obtenerCabeza() {
            return cabeza;
        }

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
                << setw(50) << "Adyacencias:Distancia" << endl;
            cout << string(85, '-') << endl;

            Sala* actual = cabeza;
            while (actual != nullptr) {
                if (actual->apto) { // Solo mostrar salas aptas
                    cout << left << setw(5) << actual->id 
                        << setw(30) << actual->nombre 
                        << setw(50);
                    
                    // Mostrar adyacencias de salas aptas
                    Adyacencia* adyacenteActual = actual->adyacencias;
                    if (adyacenteActual == nullptr) {
                        cout << "Ninguna"; 
                    } else {
                        string adyacenciasStr;
                        while (adyacenteActual != nullptr) {
                            if (adyacenteActual->salaDestino->apto) { // Solo mostrar adyacencias aptas
                                adyacenciasStr += to_string(adyacenteActual->salaDestino->id) + ":" + to_string(adyacenteActual->distancia) + " ";
                            }
                            adyacenteActual = adyacenteActual->siguiente;
                        }
                        if (adyacenciasStr.empty()) {
                            cout << "Ninguna apta";
                        } else {
                            if (adyacenciasStr.length() > 50) {
                                adyacenciasStr = adyacenciasStr.substr(0, 47) + "...";
                            }
                            cout << adyacenciasStr;
                        }
                    }
                    cout << endl;
                }
                actual = actual->siguiente;
            }
            cout << string(85, '-') << endl; 
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
                            escribirRegistro("La Puerta del Destino ha aparecido en la sala: " + actual->nombre);
                            cout << "La Puerta del Destino ha cambiado de lugar" << endl;
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
void asignarImplementosAEquipo(equipo& equipoSeleccionado, listaImplementos& listaImplementos) {
    cout << "--------------------------------------------------\n";
    cout << " Asigna implementos a los personajes de tu equipo\n";
    cout << "--------------------------------------------------\n";

    for (int i = 0; i < equipoSeleccionado.numPjs; i++) {
        personaje* pj = equipoSeleccionado.personajes[i];
        
        cout << "-----------------------------------------\n";
        cout << "Personaje: " << pj->nombre << " (" << pj->especie->nombre << ")\n";
        cout << "-----------------------------------------\n";

        int agregarOtro = 1;
        while (agregarOtro == 1) {
            cout << "\nImplementos disponibles:\n";
            cout << left << setw(5) << "No." 
                 << setw(20) << "Nombre"
                 << setw(12) << "Tipo"
                 << setw(10) << "Valor"
                 << setw(10) << "Usos"
                 << setw(12) << "Fortaleza" << endl;
            cout << "---------------------------------------------------------------\n";

            int disponibles = 0;
            for (int j = 0; j < listaImplementos.obtenerCantidad(); j++) {
                implemento* imp = listaImplementos.obtenerImplemento(j);
                if (!imp->enUso) {
                    cout << left << setw(5) << j 
                         << setw(20) << imp->nombre 
                         << setw(12) << imp->tipo;

                    if (imp->tipo == "atacar") cout << setw(10) << imp->valorAtk;
                    else if (imp->tipo == "defender") cout << setw(10) << imp->valorDef;
                    else if (imp->tipo == "curar") cout << setw(10) << imp->valorHeal;
                    else cout << setw(10) << "-";

                    cout << setw(10) << imp->usos 
                         << setw(12) << imp->fortaleza << endl;
                    disponibles++;
                }
            }

            if (disponibles == 0) {
                cout << "No hay más implementos disponibles.\n";
                break;
            }

            cout << "\nSelecciona el número del implemento: ";
            int index = leerOpcion();

            implemento* seleccionado = listaImplementos.obtenerImplemento(index);
            if (seleccionado && !seleccionado->enUso) {
                pj->mochila.agregarImplementoAMochila(seleccionado);
                cout << ">> '" << seleccionado->nombre << "' asignado a " << pj->nombre << ".\n";
            } else {
                cout << "Índice inválido o implemento ya en uso.\n";
            }

            while (true) {
                cout << "¿Asignar otro implemento a " << pj->nombre << "? (1 = Sí, 0 = No): ";
                agregarOtro = leerOpcion();
                
                if (agregarOtro == 1 || agregarOtro == 0) {
                    break;
                } else {
                    cout << "Opción inválida. Por favor ingresa 1 (Sí) o 0 (No).\n";
                }
            }
        }
        cout << "\n=== Mochila actual de " << pj->nombre << " ===\n";
        pj->mochila.mostrarMochila();
        cout << "==========================================\n";
    }

    cout << " Implementos asignados exitosamente.\n";
    cout << "-------------------------------------\n";
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
void dispersarOrcosAdyacentes(int cantRondas, Sala* cabezaSalas, Sala* salaHeroes) {
    cout << "\n=== RONDA " << cantRondas << " - Movimiento de Orcos hacia Heroes ===\n";
    
    if (!salaHeroes) {
        cout << "No se puede determinar la posicion de los heroes.\n";
        return;
    }
    
    // Estructura para almacenar orcos con sus distancias a los héroes
    struct OrcoConDistancia {
        Sala* salaOrco;
        especie* orco;
        int indiceEnSala;
        int distanciaAHeroes;
        Sala* siguienteSala; // Próxima sala en el camino hacia los héroes
    };
    
    OrcoConDistancia orcosDisponibles[200]; // Máximo orcos en todas las salas
    int numOrcosDisponibles = 0;
    
    // Fase 1: Recopilar todos los orcos y calcular sus distancias a los héroes
    Sala* salaActual = cabezaSalas;
    while (salaActual != nullptr) {
        if (salaActual->apto && salaActual->equipoOrcos.numMiembros > 0) {
            // Calcular distancia de esta sala a los héroes usando BFS
            int distanciaAHeroes = INT_MAX;
            Sala* siguienteSalaEnCamino = nullptr;
            
            // BFS para encontrar el camino más corto a los héroes
            Sala* cola[100];
            Sala* padres[100];
            int distancias[100];
            bool visitado[100];
            int frente = 0, final = 0;
            
            // Inicializar arrays
            for (int i = 0; i < 100; i++) {
                visitado[i] = false;
                padres[i] = nullptr;
                distancias[i] = INT_MAX;
            }
            
            // Mapear salas a índices (simplificado)
            Sala* todasLasSalas[100];
            int numSalas = 0;
            Sala* temp = cabezaSalas;
            while (temp != nullptr && numSalas < 100) {
                todasLasSalas[numSalas] = temp;
                if (temp == salaActual) {
                    cola[final] = temp;
                    distancias[numSalas] = 0;
                    visitado[numSalas] = true;
                    final++;
                }
                temp = temp->siguiente;
                numSalas++;
            }
            
            // BFS
            while (frente < final) {
                Sala* actual = cola[frente++];
                
                // Encontrar índice de la sala actual
                int indiceActual = -1;
                for (int i = 0; i < numSalas; i++) {
                    if (todasLasSalas[i] == actual) {
                        indiceActual = i;
                        break;
                    }
                }
                
                if (actual == salaHeroes) {
                    distanciaAHeroes = distancias[indiceActual];
                    
                    // Reconstruir camino para encontrar la siguiente sala
                    if (padres[indiceActual] != nullptr) {
                        Sala* nodoActual = actual;
                        while (padres[indiceActual] != salaActual) {
                            nodoActual = padres[indiceActual];
                            // Encontrar nuevo índice
                            for (int i = 0; i < numSalas; i++) {
                                if (todasLasSalas[i] == nodoActual) {
                                    indiceActual = i;
                                    break;
                                }
                            }
                        }
                        siguienteSalaEnCamino = nodoActual;
                    }
                    break;
                }
                
                // Explorar adyacencias
                Adyacencia* ady = actual->adyacencias;
                while (ady != nullptr) {
                    Sala* vecina = ady->salaDestino;
                    if (vecina && vecina->apto) {
                        // Encontrar índice de la sala vecina
                        int indiceVecina = -1;
                        for (int i = 0; i < numSalas; i++) {
                            if (todasLasSalas[i] == vecina) {
                                indiceVecina = i;
                                break;
                            }
                        }
                        
                        if (indiceVecina != -1 && !visitado[indiceVecina]) {
                            visitado[indiceVecina] = true;
                            distancias[indiceVecina] = distancias[indiceActual] + ady->distancia;
                            padres[indiceVecina] = actual;
                            cola[final++] = vecina;
                        }
                    }
                    ady = ady->siguiente;
                }
            }
            
            // Agregar todos los orcos de esta sala a la lista
            for (int i = 0; i < salaActual->equipoOrcos.numMiembros && numOrcosDisponibles < 200; i++) {
                orcosDisponibles[numOrcosDisponibles].salaOrco = salaActual;
                orcosDisponibles[numOrcosDisponibles].orco = salaActual->equipoOrcos.miembros[i];
                orcosDisponibles[numOrcosDisponibles].indiceEnSala = i;
                orcosDisponibles[numOrcosDisponibles].distanciaAHeroes = distanciaAHeroes;
                orcosDisponibles[numOrcosDisponibles].siguienteSala = siguienteSalaEnCamino;
                numOrcosDisponibles++;
            }
        }
        salaActual = salaActual->siguiente;
    }
    
    // Fase 2: Ordenar orcos por distancia (los más cercanos primero)
    for (int i = 0; i < numOrcosDisponibles - 1; i++) {
        for (int j = 0; j < numOrcosDisponibles - i - 1; j++) {
            if (orcosDisponibles[j].distanciaAHeroes > orcosDisponibles[j + 1].distanciaAHeroes) {
                OrcoConDistancia temp = orcosDisponibles[j];
                orcosDisponibles[j] = orcosDisponibles[j + 1];
                orcosDisponibles[j + 1] = temp;
            }
        }
    }
    
    // Fase 3: Mover máximo 5 orcos más cercanos
    int orcosMovidos = 0;
    int maxOrcosAMover = 5;
    
    cout << "Moviendo los " << min(maxOrcosAMover, numOrcosDisponibles) << " orcos mas cercanos hacia los heroes...\n";
    
    for (int i = 0; i < numOrcosDisponibles && orcosMovidos < maxOrcosAMover; i++) {
        OrcoConDistancia& orcoActual = orcosDisponibles[i];
        
        // Verificar que el orco aún existe en su sala original
        bool orcoExiste = false;
        int indiceReal = -1;
        for (int j = 0; j < orcoActual.salaOrco->equipoOrcos.numMiembros; j++) {
            if (orcoActual.salaOrco->equipoOrcos.miembros[j] == orcoActual.orco) {
                orcoExiste = true;
                indiceReal = j;
                break;
            }
        }
        
        if (!orcoExiste) {
            continue; // El orco ya fue movido
        }
        
        // Si el orco ya está en la sala de los héroes, no moverlo
        if (orcoActual.salaOrco == salaHeroes) {
            escribirRegistro("- " + orcoActual.orco->nombre + " ya esta en la sala de los heroes");
            continue;
        }
        
        // Si no hay siguiente sala en el camino, el orco no puede moverse
        if (!orcoActual.siguienteSala) {
            escribirRegistro("- " + orcoActual.orco->nombre + " no puede encontrar camino hacia los heroes");
            continue;
        }
        
        // Verificar que la sala destino no esté llena
        if (orcoActual.siguienteSala->equipoOrcos.numMiembros >= 15) {
            escribirRegistro("- " + orcoActual.orco->nombre + " no puede moverse: sala destino llena");
            continue;
        }
        
        // Mover el orco
        // Remover de sala origen
        for (int j = indiceReal; j < orcoActual.salaOrco->equipoOrcos.numMiembros - 1; j++) {
            orcoActual.salaOrco->equipoOrcos.miembros[j] = orcoActual.salaOrco->equipoOrcos.miembros[j + 1];
        }
        orcoActual.salaOrco->equipoOrcos.numMiembros--;
        
        // Agregar a sala destino
        orcoActual.siguienteSala->equipoOrcos.miembros[orcoActual.siguienteSala->equipoOrcos.numMiembros] = orcoActual.orco;
        orcoActual.siguienteSala->equipoOrcos.numMiembros++;
        
        escribirRegistro("- " + orcoActual.orco->nombre + " se movio de " + orcoActual.salaOrco->nombre + 
                " hacia " + orcoActual.siguienteSala->nombre + " (distancia a heroes: " + 
                to_string(orcoActual.distanciaAHeroes) + ")");

        orcosMovidos++;
    }
    
    if (orcosMovidos == 0) {
        cout << "No se pudieron mover orcos hacia los heroes en esta ronda.\n";
    } else {
        cout << "Distancia del orco mas cercano: " << orcosDisponibles[0].distanciaAHeroes << endl;
    }
    
    cout << "Movimiento de orcos completado.\n";
}
void generarYDispersarOrcos(int cantRondas, listaEspecies& listaEspecies, Sala* salaOrigenOrcos, Sala* cabezaSalas, Sala* salaHeroes) {
    srand(static_cast<unsigned int>(time(0)) + cantRondas);
    
    int numOrcosGenerar = (rand() % 5) + 1;
    
    cout << "\n=== RONDA " << cantRondas << " ===\n";
    cout << "Generando " << numOrcosGenerar << " orcos...\n";
    
    for (int i = 0; i < numOrcosGenerar; i++) {
        if (salaOrigenOrcos->equipoOrcos.numMiembros < 15) {
            especie* orcoAleatorio = obtenerEspecieOrcoAleatoria(listaEspecies);
            orcoAleatorio->ataque*1.5;
            orcoAleatorio->salud*2.5;
            if (orcoAleatorio != nullptr) {
                salaOrigenOrcos->equipoOrcos.miembros[salaOrigenOrcos->equipoOrcos.numMiembros] = orcoAleatorio;
                salaOrigenOrcos->equipoOrcos.numMiembros++;
                escribirRegistro("- " + orcoAleatorio->nombre + " generado en " + salaOrigenOrcos->nombre);
            }
        }
    }
    dispersarOrcosAdyacentes(cantRondas, cabezaSalas, salaHeroes);
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
void mostrarDistribucionOrcos(Sala* cabezaSalas) {
    cout << "\n=== Distribución de Orcos por Sala ===\n";
    cout << left << setw(5) << "ID" 
        << setw(30) << "Nombre de Sala" 
        << setw(15) << "Num. Orcos" 
        << setw(30) << "Tipos de Orcos" << endl;
    cout << string(80, '-') << endl;
    
    Sala* actual = cabezaSalas;
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
    
    escribirRegistro("=== MOVIMIENTO RONDA " + to_string(cantRondas) + " ===");
    escribirRegistro("Equipo " + equipoSeleccionado.nombre + " en sala: " + salaHeroes->nombre + " (ID: " + to_string(salaHeroes->id) + ")");
    escribirRegistro("Rapidez del equipo: " + to_string(rapidezEquipo));
    
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
    
    // Bucle de validación para el ID de sala
    int idSeleccionada = -1;
    bool movimientoValido = false;
    
    while (!movimientoValido) {
        cout << "Selecciona el ID de la sala a la que deseas moverte (0 para cancelar): ";
        idSeleccionada = leerOpcion();
        
        // Opción para cancelar
        if (idSeleccionada == 0) {
            cout << "Movimiento cancelado." << endl;
            return 0;
        }
        
        // Verificar si el ID es válido y alcanzable
        bool idValido = false;
        
        // Primero verificar salas adyacentes directas
        Adyacencia* adyDirecta = salaHeroes->adyacencias;
        while (adyDirecta != nullptr) {
            if (adyDirecta->salaDestino->id == idSeleccionada && adyDirecta->distancia <= rapidezEquipo) {
                idValido = true;
                movimientoValido = true;
                break;
            }
            adyDirecta = adyDirecta->siguiente;
        }
        
        // Si no es adyacente directo, verificar con BFS
        if (!idValido) {
            // Usar BFS para verificar si es alcanzable
            Sala* visitadas[100];
            int distancias[100];
            int numVisitadas = 0;
            
            Sala* cola[100];
            int distanciasCola[100];
            int frente = 0, final = 0;
            
            cola[final] = salaHeroes;
            distanciasCola[final] = 0;
            final++;
            
            visitadas[numVisitadas] = salaHeroes;
            distancias[numVisitadas] = 0;
            numVisitadas++;
            
            while (frente < final && !idValido) {
                Sala* actual = cola[frente];
                int distanciaActual = distanciasCola[frente];
                frente++;
                
                if (actual->id == idSeleccionada) {
                    idValido = true;
                    movimientoValido = true;
                    break;
                }
                
                Adyacencia* ady = actual->adyacencias;
                while (ady != nullptr) {
                    Sala* vecina = ady->salaDestino;
                    int nuevaDistancia = distanciaActual + ady->distancia;
                    
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
                        numVisitadas++;
                        
                        cola[final] = vecina;
                        distanciasCola[final] = nuevaDistancia;
                        final++;
                    }
                    ady = ady->siguiente;
                }
            }
        }
        
        if (!idValido) {
            cout << "\n¡ERROR! El ID " << idSeleccionada << " no es válido o no es alcanzable con tu rapidez actual." << endl;
            cout << "Por favor, selecciona un ID de las salas mostradas en el mapa." << endl;
            cout << "Salas alcanzables:" << endl;
            escribirRegistro("Intento de movimiento inválido a sala ID: " + to_string(idSeleccionada));
        }
    }
    
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
        turnosExtra = 0;
        
        cout << "Te has movido directamente a: " << salaHeroes->nombre << endl;
        cout << "Distancia recorrida: " << distanciaDirecta << endl;
        cout << "Salas recorridas: 1" << endl;
        cout << "No se generan turnos extra (solo 1 sala recorrida)" << endl;
        
        escribirRegistro("Movimiento directo: -> " + salaHeroes->nombre);
        escribirRegistro("Distancia recorrida: " + to_string(distanciaDirecta));
        escribirRegistro("Salas recorridas: 1 (sin turnos extra)");
        
        // Generar orcos DESPUÉS del movimiento para el turno principal
        if (cantRondas >= 1) {
            cout << "\n--- Generación de orcos después del movimiento ---" << endl;
            generarYDispersarOrcos(cantRondas, listaEspecies, salaOrcos, listaSalas.obtenerCabeza(), salaHeroes);
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
            
            escribirRegistro("Movimiento complejo: -> " + salaHeroes->nombre);
            escribirRegistro("Distancia total recorrida: " + to_string(distanciaDestino));
            escribirRegistro("Salas recorridas en el camino: " + to_string(salasDestino));

            // Generar orcos DESPUÉS del movimiento para el turno principal
            if (cantRondas >= 1) {
                cout << "\n--- Generación de orcos después del movimiento principal ---" << endl;
                generarYDispersarOrcos(cantRondas, listaEspecies, salaOrcos, listaSalas.obtenerCabeza(), salaHeroes);
            }
            
            // Solo generar turnos extra si se recorrieron 2 o más salas
            if (salasDestino >= 2) {
                cout << "Generando " << (salasDestino - 1) << " turnos extra..." << endl;
                escribirRegistro("Generando " + to_string(salasDestino - 1) + " turnos extra por movimiento complejo");
                for (int i = 0; i < salasDestino - 1; i++) {
                    cantRondas++;
                    cout << "\n--- Turno Extra " << cantRondas << " ---" << endl;
                    escribirRegistro("=== TURNO EXTRA " + to_string(cantRondas) + " ===");
                    generarYDispersarOrcos(cantRondas, listaEspecies, salaOrcos, listaSalas.obtenerCabeza(), salaHeroes);
                }
            }
            
        }
    }
    escribirRegistro("Movimiento completado. Turnos extra generados: " + to_string(turnosExtra)); 
    return turnosExtra;
}

void usarPoderMagico(listaEspecies& listaEspecies, listaSalas& listaSalas, listaImplementos& listaImplementos, bool poderesUsados[4]) {
    int opcion;
    cout << "\n=== Poderes Mágicos Disponibles ===\n";
    cout << "1. Revivir y fortalecer enanos";
    if (poderesUsados[0]) cout << " (YA USADO)";
    cout << "\n";
    cout << "2. Mover orcos de una sala a otra";
    if (poderesUsados[1]) cout << " (YA USADO)";
    cout << "\n";
    cout << "3. Reducir salud de orcos en una sala a 1";
    if (poderesUsados[2]) cout << " (YA USADO)";
    cout << "\n";
    cout << "4. Duplicar ataque y reducir fortaleza de implementos";
    if (poderesUsados[3]) cout << " (YA USADO)";
    cout << "\n";
    cout << "Selecciona un poder mágico: ";
    opcion = leerOpcion();
    cout << "-----------------------------------\n";

    switch (opcion) {
        case 1: {
            if (poderesUsados[0]) {
                cout << "\n¡Este poder mágico ya ha sido usado!" << endl;
                cout << "Cada poder mágico solo se puede usar una vez por partida." << endl;
                escribirRegistro("PODER MAGICO DENEGADO: Poder 1 (Revivir enanos) ya fue usado anteriormente");
                return;
            }
            
            // Poder 1: Revivir y fortalecer especie seleccionada
            cout << "\n=== Seleccionar Especie para Fortalecer ===\n";
            listaEspecies.mostrarEspecies();
            
            especie* especieSeleccionada = listaEspecies.seleccionarEspecie();
            if (!especieSeleccionada) {
                cout << "No se seleccionó ninguna especie.\n";
                return;
            }
            
            cout << "\nEspecie seleccionada: " << especieSeleccionada->nombre << endl;
            cout << "Valores actuales:" << endl;
            cout << "- Salud: " << especieSeleccionada->salud << endl;
            
            if (especieSeleccionada->tipo == "Heroe") {
                cout << "- Fortaleza: " << especieSeleccionada->fortaleza << endl;
                especieSeleccionada->salud += 100;
                especieSeleccionada->fortaleza += 1000;
                cout << "\n¡La especie " << especieSeleccionada->nombre << " ha sido revitalizada!" << endl;
                cout << "Nueva salud: " << especieSeleccionada->salud << endl;
                cout << "Nueva fortaleza: " << especieSeleccionada->fortaleza << endl;
                
                escribirRegistro("Poder magico 1 usado: " + especieSeleccionada->nombre + " revitalizado - Salud: " + 
                                to_string(especieSeleccionada->salud) + ", Fortaleza: " + to_string(especieSeleccionada->fortaleza));
            } else {
                cout << "- Ataque: " << especieSeleccionada->ataque << endl;
                especieSeleccionada->salud += 100;
                especieSeleccionada->ataque += 50;
                cout << "\n¡La especie " << especieSeleccionada->nombre << " ha sido revitalizada!" << endl;
                cout << "Nueva salud: " << especieSeleccionada->salud << endl;
                cout << "Nuevo ataque: " << especieSeleccionada->ataque << endl;
                
                escribirRegistro("Poder magico 1 usado: " + especieSeleccionada->nombre + " revitalizado - Salud: " + 
                                to_string(especieSeleccionada->salud) + ", Ataque: " + to_string(especieSeleccionada->ataque));
            }
            poderesUsados[0] = true;
            break;
        }

        case 2: {
            if (poderesUsados[1]) {
                cout << "\n¡Este poder mágico ya ha sido usado!" << endl;
                cout << "Cada poder mágico solo se puede usar una vez por partida." << endl;
                escribirRegistro("PODER MAGICO DENEGADO: Poder 2 (Mover orcos) ya fue usado anteriormente");
                return;
            }
            
            // Poder 2: Mover orcos de una sala a otra
            listaSalas.mostrarSalas();
            cout << "ID de la sala ORIGEN (donde están los orcos): ";
            int idOrigen = leerOpcion();
            Sala* salaOrigen = listaSalas.obtenerSalaPorId(idOrigen);

            cout << "ID de la sala DESTINO (a donde se moverán los orcos): ";
            int idDestino = leerOpcion();
            Sala* salaDestino = listaSalas.obtenerSalaPorId(idDestino);

            if (!salaOrigen || !salaDestino) {
                cout << "Una o ambas salas no existen.\n";
                return;
            }

            int orcosMovidos = salaOrigen->equipoOrcos.numMiembros;
            for (int i = 0; i < orcosMovidos && salaDestino->equipoOrcos.numMiembros < 15; i++) {
                salaDestino->equipoOrcos.miembros[salaDestino->equipoOrcos.numMiembros++] =
                    salaOrigen->equipoOrcos.miembros[i];
            }
            salaOrigen->equipoOrcos.numMiembros = 0;
            
            escribirRegistro("Poder magico 2 usado: Se movieron " + to_string(orcosMovidos) + " orcos de " + 
                            salaOrigen->nombre + " a " + salaDestino->nombre);
            cout << "Se han movido " << orcosMovidos << " orcos de " << salaOrigen->nombre
                << " a " << salaDestino->nombre << ".\n";
            poderesUsados[1] = true;
            break;
        }

        case 3: {
            if (poderesUsados[2]) {
                cout << "\n¡Este poder mágico ya ha sido usado!" << endl;
                cout << "Cada poder mágico solo se puede usar una vez por partida." << endl;
                escribirRegistro("PODER MAGICO DENEGADO: Poder 3 (Reducir salud orcos) ya fue usado anteriormente");
                return;
            }
            
            // Poder 3: Reducir salud de todos los orcos de una sala a 1
            listaSalas.mostrarSalas();
            cout << "ID de la sala donde reducir la salud de los orcos: ";
            int id = leerOpcion();
            Sala* sala = listaSalas.obtenerSalaPorId(id);
            if (!sala) {
                cout << "Sala no encontrada.\n";
                return;
            }

            int orcosAfectados = sala->equipoOrcos.numMiembros;
            for (int i = 0; i < sala->equipoOrcos.numMiembros; i++) {
                sala->equipoOrcos.miembros[i]->salud = 1;
            }
            
            escribirRegistro("Poder magico 3 usado: Reducida salud a 1 de " + to_string(orcosAfectados) + 
                            " orcos en sala " + sala->nombre);
            cout << "Todos los orcos en la sala " << sala->nombre << " tienen ahora 1 de salud.\n";
            poderesUsados[2] = true;
            break;
        }

        case 4: {
            if (poderesUsados[3]) {
                cout << "\n¡Este poder mágico ya ha sido usado!" << endl;
                cout << "Cada poder mágico solo se puede usar una vez por partida." << endl;
                escribirRegistro("PODER MAGICO DENEGADO: Poder 4 (Duplicar ataque implementos) ya fue usado anteriormente");
                return;
            }
            
            // Poder 4: Duplicar ataque y reducir fortaleza a 0
            int total = listaImplementos.obtenerCantidad();
            int implementosAfectados = 0;
            for (int i = 0; i < total; i++) {
                implemento* imp = listaImplementos.obtenerImplemento(i);
                if (imp->tipo == "atacar") {
                    imp->valorAtk *= 2;
                    imp->fortaleza = 0;
                    implementosAfectados++;
                }
            }
            
            escribirRegistro("Poder magico 4 usado: Duplicado ataque y eliminada fortaleza de " + 
                            to_string(implementosAfectados) + " implementos de ataque");
            cout << "¡Los implementos de ataque ahora hacen el doble de daño y no requieren fortaleza!\n";
            poderesUsados[3] = true;
            break;
        }

        default:
            cout << "Opción inválida.\n";
            escribirRegistro("PODER MAGICO: Opcion invalida seleccionada: " + to_string(opcion));
    }
}

// Estructura para manejar estadisticas de combate
struct EstadisticasCombate {
    personaje* personajeRef;  // Referencia al personaje del equipo
    double saludActual;
    double fortalezaActual;
    double fortalezaInicial;
    bool puedeActuar;
    int rondasSinCombate;     // Para recuperación de fortaleza

    EstadisticasCombate(personaje* pj) {
        personajeRef = pj;
        saludActual = pj->especie->salud;
        fortalezaActual = pj->especie->fortaleza;
        fortalezaInicial = pj->especie->fortaleza;
        puedeActuar = true;
        rondasSinCombate = 0;
    }
    
    // Función para recuperar fortaleza entre rondas sin combate
    void recuperarFortaleza() {
        if (fortalezaActual < fortalezaInicial) {
            fortalezaActual = min(fortalezaInicial, fortalezaActual * 1.1);
            rondasSinCombate++;
        }
    }
};
void armarBatalla(listaSalas& listaSalas, equipo& equipoHeroes, Sala*& salaActual, int& cantRondas, listaEspecies& listaEspecies, listaImplementos& listaImplementos) {
    cout << "\n=== ¡COMBATE INICIADO! ===" << endl;
    
    escribirRegistro("=== COMBATE INICIADO EN RONDA " + to_string(cantRondas) + " ===");
    escribirRegistro("Sala de combate: " + salaActual->nombre + " (ID: " + to_string(salaActual->id) + ")");
    escribirRegistro("Equipo: " + equipoHeroes.nombre);

    // Crear estadísticas de combate para héroes
    EstadisticasCombate* estadisticasHeroes[4];
    int numHeroesVivos = 0;
    
    for (int i = 0; i < equipoHeroes.numPjs; i++) {
        personaje* heroe = equipoHeroes.personajes[i];
        if (heroe && heroe->especie) {
            estadisticasHeroes[numHeroesVivos] = new EstadisticasCombate(heroe);
            escribirRegistro("Heroe en combate: " + heroe->nombre + " (" + heroe->especie->nombre + ") - Salud: " + to_string(heroe->especie->salud) + ", Fortaleza: " + to_string(heroe->especie->fortaleza));
            numHeroesVivos++;
        }
    }
    
    // Crear estadísticas de combate para orcos
    EstadisticasCombate* estadisticasOrcos[15];
    int numOrcosVivos = salaActual->equipoOrcos.numMiembros;
    
    escribirRegistro("Numero de orcos enemigos: " + to_string(numOrcosVivos));
    for (int i = 0; i < numOrcosVivos; i++) {
        especie* orco = salaActual->equipoOrcos.miembros[i];
        if (orco) {
            // Crear un personaje temporal para el orco
            personaje* orcoTemp = new personaje();
            orcoTemp->especie = orco;
            orcoTemp->nombre = orco->nombre;
            estadisticasOrcos[i] = new EstadisticasCombate(orcoTemp);
            escribirRegistro("Orco enemigo: " + orco->nombre + " - Ataque: " + to_string(orco->ataque) + ", Salud: " + to_string(orco->salud));
        }
    }
    
    // Verificar proporción 3:1 para opción de huida
    if (numOrcosVivos >= numHeroesVivos * 3) {
        cout << "\n¡ALERTA! Los orcos superan en proporción 3:1 a tu equipo." << endl;
        cout << "Opciones disponibles:" << endl;
        cout << "1. Huir a la sala con menor distancia" << endl;
        cout << "2. Continuar con el combate" << endl;
        cout << "Selecciona una opción: ";
        
        escribirRegistro("ALERTA: Proporcion 3:1 detectada (" + to_string(numOrcosVivos) + " orcos vs " + to_string(numHeroesVivos) + " heroes)");

        int opcionHuida = leerOpcion();
        
        if (opcionHuida == 1) {
            // Buscar sala adyacente con menor distancia
            Adyacencia* ady = salaActual->adyacencias;
            Sala* salaMasCercana = nullptr;
            int menorDistancia = INT_MAX;
            
            while (ady != nullptr) {
                if (ady->distancia < menorDistancia) {
                    menorDistancia = ady->distancia;
                    salaMasCercana = ady->salaDestino;
                }
                ady = ady->siguiente;
            }
            
            if (salaMasCercana) {
                cout << "¡Has huido exitosamente a " << salaMasCercana->nombre << "!" << endl;
                escribirRegistro("HUIDA EXITOSA: Equipo huyo de " + salaActual->nombre + " a " + salaMasCercana->nombre + " (distancia: " + to_string(menorDistancia) + ")");
                salaActual = salaMasCercana;
                
                // Limpiar memoria
                for (int i = 0; i < numHeroesVivos; i++) {
                    delete estadisticasHeroes[i];
                }
                for (int i = 0; i < numOrcosVivos; i++) {
                    delete estadisticasOrcos[i]->personajeRef;
                    delete estadisticasOrcos[i];
                }
                return;
            } else {
                cout << "No hay salas adyacentes para huir. ¡Debes luchar!" << endl;
                escribirRegistro("HUIDA FALLIDA: No hay salas adyacentes disponibles");
            }
        } else {
            escribirRegistro("El equipo decidio continuar con el combate a pesar de la desventaja");
        }
    }
    
    // Bucle principal de combate
    bool combateActivo = true;
    int turno = 1;
    
    while (combateActivo && numHeroesVivos > 0 && numOrcosVivos > 0) {
        cout << "\n=== TURNO " << turno << " ===" << endl;
        escribirRegistro("--- TURNO DE COMBATE " + to_string(turno) + " ---");
        
        // Turno de los héroes (atacan primero)
        for (int i = 0; i < numHeroesVivos && numOrcosVivos > 0; i++) {
            personaje* heroeActual = estadisticasHeroes[i]->personajeRef;
            if (!heroeActual || !estadisticasHeroes[i]->puedeActuar || estadisticasHeroes[i]->saludActual <= 0) {
                continue;
            }
            
            cout << "\n--- Turno de " << heroeActual->nombre << " ---" << endl;
            cout << "Salud: " << estadisticasHeroes[i]->saludActual << "/" << heroeActual->especie->salud << endl;
            cout << "Fortaleza: " << estadisticasHeroes[i]->fortalezaActual << "/" << estadisticasHeroes[i]->fortalezaInicial << endl;
            
            cout << "\nOpciones de combate:" << endl;
            cout << "1. Atacar" << endl;
            cout << "2. Curar" << endl;
            cout << "Selecciona una opción: ";
            
            int accion = leerOpcion();
            
            switch (accion) {
                case 1: { // Atacar
                    cout << "\nTipo de ataque:" << endl;
                    cout << "1. Ataque normal" << endl;
                    cout << "2. Usar arma" << endl;
                    cout << "Selecciona: ";
                    
                    int tipoAtaque = leerOpcion();
                    double danoInfligido = 0;
                    
                    if (tipoAtaque == 1) {
                        // Ataque normal con daño de la fortaleza actual
                        danoInfligido = estadisticasHeroes[i]->fortalezaActual;
                        cout << "Ataque normal realizado. Daño: " << danoInfligido << endl;
                    } else if (tipoAtaque == 2) {
                        // Usar arma de la mochila
                        cout << "\nArmas disponibles en la mochila:" << endl;
                        bool tieneArmas = false;
                        
                        for (int j = 0; j < heroeActual->mochila.numImplementos; j++) {
                            implemento* imp = heroeActual->mochila.implementos[j];
                            if (imp && imp->tipo == "atacar" && imp->usos > 0) {
                                cout << (j + 1) << ". " << imp->nombre << " (Daño: " << imp->valorAtk << ", Usos: " << imp->usos << ")" << endl;
                                tieneArmas = true;
                            }
                        }
                        
                        if (tieneArmas) {
                            cout << "Selecciona el arma (0 para cancelar): ";
                            int selArma = leerOpcion();
                            
                            if (selArma > 0 && selArma <= heroeActual->mochila.numImplementos) {
                                implemento* armaSeleccionada = heroeActual->mochila.implementos[selArma - 1];
                                if (armaSeleccionada && armaSeleccionada->tipo == "atacar" && armaSeleccionada->usos > 0) {
                                    danoInfligido = armaSeleccionada->valorAtk;
                                    armaSeleccionada->usos--;
                                    estadisticasHeroes[i]->fortalezaActual *= 0.9; // Reducir fortaleza 10%
                                    
                                    cout << "Usaste " << armaSeleccionada->nombre << ". Daño: " << danoInfligido << endl;
                                    cout << "Usos restantes: " << armaSeleccionada->usos << endl;
                                    cout << "Tu fortaleza se redujo a: " << estadisticasHeroes[i]->fortalezaActual << endl;
                                } else {
                                    cout << "Arma no válida. Ataque perdido." << endl;
                                    escribirRegistro(heroeActual->nombre + " intento usar arma invalida - turno perdido");
                                    continue;
                                }
                            } else {
                                cout << "Ataque cancelado." << endl;
                                escribirRegistro(heroeActual->nombre + " cancelo el ataque con arma");
                                continue;
                            }
                        } else {
                            cout << "No tienes armas disponibles. Usando ataque normal." << endl;
                            danoInfligido = estadisticasHeroes[i]->fortalezaActual;
                        }
                    }
                    
                    // Seleccionar objetivo (orco más débil en salud, luego fortaleza, luego al azar)
                    int objetivoOrco = -1;
                    double menorSalud = DBL_MAX;
                    
                    for (int j = 0; j < numOrcosVivos; j++) {
                        if (estadisticasOrcos[j]->saludActual > 0 && estadisticasOrcos[j]->saludActual < menorSalud) {
                            menorSalud = estadisticasOrcos[j]->saludActual;
                            objetivoOrco = j;
                        }
                    }
                    
                    if (objetivoOrco != -1) {
                        estadisticasOrcos[objetivoOrco]->saludActual -= danoInfligido;
                        cout << "Atacaste a " << salaActual->equipoOrcos.miembros[objetivoOrco]->nombre 
                             << " causando " << danoInfligido << " de daño." << endl;
                        cout << "Salud del enemigo: " << estadisticasOrcos[objetivoOrco]->saludActual << endl;
                        
                        escribirRegistro(heroeActual->nombre + " ataco a " + salaActual->equipoOrcos.miembros[objetivoOrco]->nombre + " - Dano: " + to_string(danoInfligido) + " (Salud: -> " + to_string(estadisticasOrcos[objetivoOrco]->saludActual) + ")");

                        if (estadisticasOrcos[objetivoOrco]->saludActual <= 0) {
                            cout << "¡" << salaActual->equipoOrcos.miembros[objetivoOrco]->nombre << " ha muerto!" << endl;
                            escribirRegistro("MUERTE: " + salaActual->equipoOrcos.miembros[objetivoOrco]->nombre + " fue eliminado por " + heroeActual->nombre);
                        }
                    }
                    break;
                }
                
                case 2: { // Curar
                    cout << "\nConsumibles disponibles en la mochila:" << endl;
                    bool tieneConsumibles = false;
                    
                    for (int j = 0; j < heroeActual->mochila.numImplementos; j++) {
                        implemento* imp = heroeActual->mochila.implementos[j];
                        if (imp && imp->tipo == "curar" && imp->usos > 0) {
                            cout << (j + 1) << ". " << imp->nombre << " (Curación: " << imp->valorHeal << ", Usos: " << imp->usos << ")" << endl;
                            tieneConsumibles = true;
                        }
                    }
                    
                    if (tieneConsumibles) {
                        cout << "Selecciona el consumible (0 para cancelar): ";
                        int selConsumible = leerOpcion();
                        
                        if (selConsumible > 0 && selConsumible <= heroeActual->mochila.numImplementos) {
                            implemento* consumibleSeleccionado = heroeActual->mochila.implementos[selConsumible - 1];
                            if (consumibleSeleccionado && consumibleSeleccionado->tipo == "curar" && consumibleSeleccionado->usos > 0) {
                                estadisticasHeroes[i]->saludActual += consumibleSeleccionado->valorHeal;
                                if (estadisticasHeroes[i]->saludActual > heroeActual->especie->salud) {
                                    estadisticasHeroes[i]->saludActual = heroeActual->especie->salud;
                                }
                                consumibleSeleccionado->usos--;
                                
                                cout << "Usaste " << consumibleSeleccionado->nombre << ". Salud restaurada: " << consumibleSeleccionado->valorHeal << endl;
                                cout << "Salud actual: " << estadisticasHeroes[i]->saludActual << endl;
                                cout << "Usos restantes: " << consumibleSeleccionado->usos << endl;
                                escribirRegistro(heroeActual->nombre + " uso " + consumibleSeleccionado->nombre + " - Curacion: " + to_string(consumibleSeleccionado->valorHeal) + " (Salud: -> " + to_string(estadisticasHeroes[i]->saludActual) + ")");
                            }
                        }
                    } else {
                        cout << "No tienes consumibles disponibles." << endl;
                        escribirRegistro(heroeActual->nombre + " intento curar pero no tiene consumibles disponibles");
                    }
                    break;
                }
                
                default:
                    cout << "Opción no válida. Turno perdido." << endl;
                    escribirRegistro(heroeActual->nombre + " selecciono opcion invalida - turno perdido");
                    break;
            }
        }
        
        // Contar orcos vivos
        int orcosVivosActuales = 0;
        for (int i = 0; i < numOrcosVivos; i++) {
            if (estadisticasOrcos[i]->saludActual > 0) {
                orcosVivosActuales++;
            }
        }
        numOrcosVivos = orcosVivosActuales;
        
        if (numOrcosVivos == 0) {
            cout << "\n¡VICTORIA! ¡Todos los orcos han sido derrotados!" << endl;
            escribirRegistro("VICTORIA: Todos los orcos fueron derrotados en el turno " + to_string(turno));
            break;
        }
        
        // Turno de los orcos
        cout << "\n--- Turno de los Orcos ---" << endl;
        escribirRegistro("Turno de los orcos - " + to_string(numOrcosVivos) + " orcos vivos");

        for (int i = 0; i < salaActual->equipoOrcos.numMiembros && numHeroesVivos > 0; i++) {
            if (estadisticasOrcos[i]->saludActual <= 0) {
                continue;
            }
            
            especie* orcoActual = salaActual->equipoOrcos.miembros[i];
            
            // Seleccionar objetivo héroe (menor salud, luego al azar)
            int objetivoHeroe = -1;
            double menorSaludHeroe = DBL_MAX;
            
            for (int j = 0; j < numHeroesVivos; j++) {
                if (estadisticasHeroes[j]->saludActual > 0 && estadisticasHeroes[j]->saludActual < menorSaludHeroe) {
                    menorSaludHeroe = estadisticasHeroes[j]->saludActual;
                    objetivoHeroe = j;
                }
            }
            
            if (objetivoHeroe != -1) {
                personaje* heroeObjetivo = estadisticasHeroes[objetivoHeroe]->personajeRef;
                double danoOrco = orcoActual->ataque;
                
                // Verificar si el héroe tiene implementos de defensa
                bool tieneDefensa = false;
                for (int j = 0; j < heroeObjetivo->mochila.numImplementos; j++) {
                    implemento* imp = heroeObjetivo->mochila.implementos[j];
                    if (imp && imp->tipo == "defender" && imp->usos > 0) {
                        tieneDefensa = true;
                        break;
                    }
                }
                
                if (tieneDefensa) {
                    cout << "\n" << heroeObjetivo->nombre << " tiene implementos de defensa disponibles." << endl;
                    cout << "¿Quieres usar un implemento de defensa?" << endl;
                    cout << "1. Sí, usar defensa" << endl;
                    cout << "2. No, recibir daño completo" << endl;
                    cout << "Selecciona: ";
                    
                    int usarDefensa = leerOpcion();
                    
                    if (usarDefensa == 1) {
                        cout << "\nImplementos de defensa disponibles:" << endl;
                        for (int j = 0; j < heroeObjetivo->mochila.numImplementos; j++) {
                            implemento* imp = heroeObjetivo->mochila.implementos[j];
                            if (imp && imp->tipo == "defender" && imp->usos > 0) {
                                cout << (j + 1) << ". " << imp->nombre << " (Defensa: " << imp->valorDef << ", Usos: " << imp->usos << ")" << endl;
                            }
                        }
                        
                        cout << "Selecciona el implemento de defensa: ";
                        int selDefensa = leerOpcion();
                        
                        if (selDefensa > 0 && selDefensa <= heroeObjetivo->mochila.numImplementos) {
                            implemento* defensaSeleccionada = heroeObjetivo->mochila.implementos[selDefensa - 1];
                            if (defensaSeleccionada && defensaSeleccionada->tipo == "defender" && defensaSeleccionada->usos > 0) {
                                double reduccionDano = (defensaSeleccionada->valorDef / 100.0) * danoOrco;
                                danoOrco -= reduccionDano;
                                if (danoOrco < 0) danoOrco = 0;
                                
                                defensaSeleccionada->usos--;
                                
                                cout << "Usaste " << defensaSeleccionada->nombre << ". Daño reducido en " << reduccionDano << endl;
                                cout << "Usos restantes: " << defensaSeleccionada->usos << endl;
                            }
                        }
                    }
                }
                
                estadisticasHeroes[objetivoHeroe]->saludActual -= danoOrco;
                cout << orcoActual->nombre << " atacó a " << heroeObjetivo->nombre << " causando " << danoOrco << " de daño." << endl;
                cout << "Salud de " << heroeObjetivo->nombre << ": " << estadisticasHeroes[objetivoHeroe]->saludActual << endl;
                
                escribirRegistro(orcoActual->nombre + " ataco a " + heroeObjetivo->nombre + " - Dano: " + to_string(danoOrco) + " (Salud: -> " + to_string(estadisticasHeroes[objetivoHeroe]->saludActual) + ")");

                if (estadisticasHeroes[objetivoHeroe]->saludActual <= 0) {
                    cout << "¡" << heroeObjetivo->nombre << " ha muerto!" << endl;
                    escribirRegistro("MUERTE: " + heroeObjetivo->nombre + " fue eliminado por " + orcoActual->nombre);
                    estadisticasHeroes[objetivoHeroe]->puedeActuar = false;
                }
            }
        }
        
        // Contar héroes vivos
        int heroesVivosActuales = 0;
        for (int i = 0; i < numHeroesVivos; i++) {
            if (estadisticasHeroes[i]->saludActual > 0) {
                heroesVivosActuales++;
            }
        }
        numHeroesVivos = heroesVivosActuales;
        
        if (numHeroesVivos == 0) {
            cout << "\n¡DERROTA! ¡Todos los héroes han muerto!" << endl;
            cout << "Los orcos han ganado. ¡FIN DEL JUEGO!" << endl;
            escribirRegistro("DERROTA TOTAL: Todos los heroes murieron en el turno " + to_string(turno));
            escribirRegistro("FIN DEL JUEGO - Victoria de los orcos");
            combateActivo = false;
            
            // Limpiar memoria y salir del programa
            for (int i = 0; i < equipoHeroes.numPjs; i++) {
                if (estadisticasHeroes[i]) delete estadisticasHeroes[i];
            }
            for (int i = 0; i < salaActual->equipoOrcos.numMiembros; i++) {
                if (estadisticasOrcos[i]) {
                    delete estadisticasOrcos[i]->personajeRef;
                    delete estadisticasOrcos[i];
                }
            }
            exit(0);
        }
        
        turno++;
    }
    
    // Si los héroes ganaron, limpiar orcos de la sala
    if (numOrcosVivos == 0) {
        salaActual->equipoOrcos.numMiembros = 0;
        cout << "La sala ha sido liberada de orcos." << endl;
        escribirRegistro("SALA LIBERADA: " + salaActual->nombre + " ha sido liberada de orcos");        

        // Aplicar recuperación de fortaleza para próximas rondas sin combate
        cout << "Los héroes recuperarán fortaleza gradualmente en las próximas rondas sin combate." << endl;
        escribirRegistro("Los heroes iniciaran recuperacion de fortaleza");

        for (int i = 0; i < numHeroesVivos; i++) {
            estadisticasHeroes[i]->rondasSinCombate = 0; // Reiniciar contador
        }
    }
    
    for (int i = 0; i < equipoHeroes.numPjs; i++) {
        if (estadisticasHeroes[i]) delete estadisticasHeroes[i];
    }
    for (int i = 0; i < salaActual->equipoOrcos.numMiembros; i++) {
        if (estadisticasOrcos[i]) {
            delete estadisticasOrcos[i]->personajeRef;
            delete estadisticasOrcos[i];
        }
    }
    
    cout << "\n=== FIN DEL COMBATE ===" << endl;
    escribirRegistro("=== FIN DEL COMBATE ===");
}

//Menu de Juego
void menuJuego(listaEspecies& listaEspecies, listaPersonajes& listaPersonajes, listaEquipos& listaEquipos, listaImplementos& listaImplementos, listaSalas& listaSalas, equipo*& equipoSeleccionado) {
    cout << "Seleccione su equipo" << endl;
    elegirEquipo(listaEquipos, listaPersonajes, equipoSeleccionado);
    asignarImplementosAEquipo(*equipoSeleccionado, listaImplementos);
    cout << endl;
    
    // Registrar inicio del juego
    escribirRegistro("=== INICIO DEL JUEGO ===");
    escribirRegistro("Equipo seleccionado: " + equipoSeleccionado->nombre);
    escribirRegistro("Miembros del equipo:");
    for (int i = 0; i < equipoSeleccionado->numPjs; i++) {
        personaje* pj = equipoSeleccionado->personajes[i];
        if (pj && pj->especie) {
            escribirRegistro("- " + pj->nombre + " (" + pj->especie->nombre + ") - Salud: " + to_string(pj->especie->salud) + ", Rapidez: " + to_string(pj->especie->rapidez));
        }
    }
    
    auto extremos = listaSalas.buscarExtremosDeSalas();
    Sala* salaHeroes = extremos.first;
    Sala* salaOrcos = extremos.second;
    
    // Registrar posiciones iniciales
    escribirRegistro("Posicion inicial de heroes: " + salaHeroes->nombre + " (ID: " + to_string(salaHeroes->id) + ")");
    escribirRegistro("Posicion de generacion de orcos: " + salaOrcos->nombre + " (ID: " + to_string(salaOrcos->id) + ")");
    
    listaSalas.asignarPuertaDelDestino();
    cout << endl;
    cout << "Bienvenido a Khazad-Dum" << endl;
    cout << "Llega a la Puerta del Destino en los túneles ancestrales para invocar la ayuda de Gandalf." << endl;

    int cantRondas = 0;
    int ultimaRondaPoderMagico = -5;
    bool poderesUsados[4] = {false, false, false, false}; // Array para rastrear qué poderes han sido usados
    
    while (true) {
        if (verificarVictoria(salaHeroes)) {
            escribirRegistro("VICTORIA FINAL: El equipo " + equipoSeleccionado->nombre + " ha encontrado la Puerta del Destino!");
            escribirRegistro("Juego completado exitosamente en la ronda " + to_string(cantRondas));
            break;
        }

        if (cantRondas % 5 == 0 && cantRondas > 0) {
            escribirRegistro("Ronda " + to_string(cantRondas) + ": La Puerta del Destino se mueve a una nueva ubicacion");
            listaSalas.asignarPuertaDelDestino();
        }

        if (!listaSalas.existePuertaDelDestino() && cantRondas > 0) {
            cout << "La Puerta del Destino ha recorrido todas las salas y no has llegado a tiempo." << endl;
            cout << "¡Los orcos han invadido todo el subterráneo! ¡HAS PERDIDO!" << endl;
            escribirRegistro("DERROTA FINAL: La Puerta del Destino desaparecio - Los orcos invadieron todo el subterraneo");
            escribirRegistro("Juego terminado en derrota en la ronda " + to_string(cantRondas));
            break;
        }

        int op;
        cout << "\n--- Menú del Juego (Ronda " << cantRondas + 1 << ") ---" << endl;
        cout << "1. Moverse entre salas" << endl;
        cout << "2. Mostrar mapa" << endl;
        cout << "3. Usar Poder Magico";
        
        int rondasDesdeUltimoPoder = cantRondas - ultimaRondaPoderMagico;
        if (rondasDesdeUltimoPoder < 5) {
            int rondasRestantes = 5 - rondasDesdeUltimoPoder;
            cout << " (DISPONIBLE EN " << rondasRestantes << " RONDAS)";
        } else {
            // Verificar si quedan poderes disponibles
            bool hayPoderesDisponibles = false;
            for (int i = 0; i < 4; i++) {
                if (!poderesUsados[i]) {
                    hayPoderesDisponibles = true;
                    break;
                }
            }
            
            if (hayPoderesDisponibles) {
                cout << " (DISPONIBLE)";
            } else {
                cout << " (TODOS LOS PODERES USADOS)";
            }
        }
        cout << endl;
        cout << "4. Terminar Juego." << endl;
        cout << "Selecciona una opción: ";
        op = leerOpcion();

        escribirRegistro("Ronda " + to_string(cantRondas + 1) + " - Opcion seleccionada: " + to_string(op));

        switch (op) {
            case 1: {
                ++cantRondas;
                escribirRegistro("=== INICIO RONDA " + to_string(cantRondas) + " ===");

                cout << "\n=== RONDA " << cantRondas << " ===\n";
                
                // Verificar encuentro con orcos ANTES del movimiento
                if (verificarEncuentroConOrcos(salaHeroes)) {
                    cout << "¡Encuentro con orcos! Debes luchar o huir." << endl;
                    escribirRegistro("ENCUENTRO CON ORCOS en " + salaHeroes->nombre + " - " + to_string(salaHeroes->equipoOrcos.numMiembros) + " orcos presentes");
                    armarBatalla(listaSalas, *equipoSeleccionado, salaHeroes, cantRondas, listaEspecies, listaImplementos);
                }

                int turnosExtra = moverHeroes(listaSalas, *equipoSeleccionado, salaHeroes, listaEspecies, salaOrcos, cantRondas);
                
                cout << "Movimiento completado. Turnos extra generados: " << turnosExtra << endl;
                escribirRegistro("Ronda " + to_string(cantRondas) + " completada - Turnos extra: " + to_string(turnosExtra));
                escribirRegistro("Posicion actual del equipo: " + salaHeroes->nombre + " (ID: " + to_string(salaHeroes->id) + ")");
                break;
            }
            case 2: {
                escribirRegistro("Jugador consulto el mapa de salas aptas");
                listaSalas.mostrarMapaSalasAptas();
                break;
            }
            case 3: {
                int rondasDesdeUltimoPoder = cantRondas - ultimaRondaPoderMagico;
                if (rondasDesdeUltimoPoder < 5) {
                    int rondasRestantes = 5 - rondasDesdeUltimoPoder;
                    cout << "\n¡No puedes usar un poder mágico aún!" << endl;
                    cout << "Debes esperar " << rondasRestantes << " rondas más." << endl;
                    cout << "Último uso: Ronda " << ultimaRondaPoderMagico << ", Ronda actual: " << cantRondas << endl;
                    escribirRegistro("PODER MAGICO DENEGADO: Faltan " + to_string(rondasRestantes) + " rondas (ultimo uso: ronda " + to_string(ultimaRondaPoderMagico) + ")");
                } else {
                    // Verificar si quedan poderes disponibles
                    bool hayPoderesDisponibles = false;
                    for (int i = 0; i < 4; i++) {
                        if (!poderesUsados[i]) {
                            hayPoderesDisponibles = true;
                            break;
                        }
                    }
                    
                    if (!hayPoderesDisponibles) {
                        cout << "\n¡Todos los poderes mágicos ya han sido usados!" << endl;
                        cout << "Cada poder mágico solo se puede usar una vez por partida." << endl;
                        escribirRegistro("PODER MAGICO DENEGADO: Todos los poderes magicos ya fueron usados");
                    } else {
                        escribirRegistro("Jugador accedio al menu de poderes magicos en ronda " + to_string(cantRondas));
                        usarPoderMagico(listaEspecies, listaSalas, listaImplementos, poderesUsados);
                        ultimaRondaPoderMagico = cantRondas; // Actualizar la ronda del último uso
                        escribirRegistro("PODER MAGICO: Registrado acceso en ronda " + to_string(cantRondas) + " - Proximo uso disponible en ronda " + to_string(cantRondas + 5));
                    }
                }
                break;
            }
            case 4: {
                cout << "¿Estás seguro de querer salir? (Si/No): ";
                string opcion;
                cin >> opcion;
                if (opcion == "Si" || opcion == "si" || opcion == "SI" || opcion == "sI") {
                    cout << "Juego terminado." << endl;
                    escribirRegistro("JUEGO TERMINADO: El jugador decidio salir en la ronda " + to_string(cantRondas + 1));
                    escribirRegistro("Posicion final del equipo: " + salaHeroes->nombre + " (ID: " + to_string(salaHeroes->id) + ")");
                    
                    // Registrar estado final de poderes mágicos
                    escribirRegistro("Estado final de poderes magicos:");
                    string poderes[4] = {"Revivir enanos", "Mover orcos", "Reducir salud orcos", "Duplicar ataque implementos"};
                    for (int i = 0; i < 4; i++) {
                        escribirRegistro("- " + poderes[i] + ": " + (poderesUsados[i] ? "USADO" : "NO USADO"));
                    }
                    return;
                } else {
                    escribirRegistro("Jugador cancelo la salida del juego");
                }
                break;
            }
            default: {
                cout << "Opción no válida. Intenta de nuevo." << endl;
                escribirRegistro("Opcion invalida seleccionada: " + to_string(op));
                break;
            }
        }
    }
    
    escribirRegistro("=== FIN DEL JUEGO ===");
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

            cout << "Partida cargada exitosamente.\n\n";
            
            // Preguntar si quiere modificar los datos
            int modificar;
            do {
                cout << "¿Deseas modificar los datos cargados antes de iniciar el juego?\n";
                cout << "1. Sí, modificar datos\n";
                cout << "2. No, iniciar juego directamente\n";
                cout << "Selecciona una opción: ";
                modificar = leerOpcion();
                
                switch (modificar) {
                    case 1:
                        cout << "\nAccediendo al menú de operaciones...\n";
                        verSubMenuOperaciones(listaEspecies, listaPersonajes, listaEquipos, listaImplementos, listaSalas);
                        // Después de salir del menú de operaciones, volver a preguntar
                        break;
                    case 2:
                        cout << "\nIniciando juego...\n\n";
                        menuJuego(listaEspecies, listaPersonajes, listaEquipos, listaImplementos, listaSalas, equipoSeleccionado);
                        return; // Salir de la función después de terminar el juego
                    default:
                        cout << "Opción inválida. Por favor selecciona 1 o 2.\n";
                        break;
                }
            } while (modificar != 2);
            
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
    ofstream archivo("registros.txt");
    if (archivo.is_open()) {
        archivo << "=== INICIO DEL JUEGO ===" << endl;
        archivo.close();
    }

    listaEspecies listaEspecies;
    listaPersonajes listaPersonajes(listaEspecies);
    listaEquipos listaEquipos;
    listaImplementos listaImplementos;
    listaSalas listaSalas;
    equipo* equipoSeleccionado = nullptr;
    Sala* salaActual = nullptr;

    //Inicializar algunos implementos para comodidad al inicio
    listaImplementos.agregarImplemento("Sting de Bilbo", "atacar", 80, 140, 95, 0, 0);
    listaImplementos.agregarImplemento("Martillo de Durin", "atacar", 25, 220, 160, 0, 0);
    listaImplementos.agregarImplemento("Vara de Radagast", "atacar", 15, 90, 85, 0, 0);
    listaImplementos.agregarImplemento("Cimitarra de Haradrim", "atacar", 60, 130, 110, 0, 0);
    listaImplementos.agregarImplemento("Lanza de Rohan", "atacar", 40, 160, 125, 0, 0);
    listaImplementos.agregarImplemento("Escudo de Erebor", "defender", 120, 180, 0, 130, 0);
    listaImplementos.agregarImplemento("Cota de Malla Élfica", "defender", 200, 200, 0, 90, 0);
    listaImplementos.agregarImplemento("Brazaletes de Poder", "defender", 50, 120, 0, 70, 0);
    listaImplementos.agregarImplemento("Casco de Isengard", "defender", 80, 140, 0, 85, 0);
    listaImplementos.agregarImplemento("Elixir de Rivendel", "curar", 5, 100, 0, 0, 50);
    listaImplementos.agregarImplemento("Lembas Élfico", "curar", 10, 60, 0, 0, 25);
    listaImplementos.agregarImplemento("Agua de Lothlórien", "curar", 8, 80, 0, 0, 40);
    listaImplementos.agregarImplemento("Hierba de Athelas", "curar", 15, 50, 0, 0, 20);
    listaImplementos.agregarImplemento("Bálsamo de Gondor", "curar", 6, 90, 0, 0, 45);


    // Iniciar el juego
    menuInicial(listaEspecies, listaPersonajes, listaEquipos, listaImplementos, listaSalas, equipoSeleccionado, salaActual);

    return 0;
}
