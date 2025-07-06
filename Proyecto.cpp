//Modulos
#include <iostream>
#include <limits>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <regex>
#include <cctype>
#include <iomanip>

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
struct nodoEspecie;
struct nodoPersonaje;
class listaEspecies;
class listaPersonajes;
class listaMochilas;

//Estructuras de las Especies
struct especie {
    string nombre;
    int fortaleza;
    double ataque;
    double salud;
    double rapidez;
    string tipo;
};
struct nodoEspecie {
    especie dato;
    nodoEspecie* siguiente;
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

//Estructuras de los Personajes
struct personaje {
    nodoEspecie* especie;
    string nombre;
    mochila mochila;
};
struct nodoPersonaje {
    personaje dato;
    nodoPersonaje* siguiente;
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
            return nullptr; // Retorna nullptr si el índice es inválido
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

            // Encabezado de la tabla
            cout << left << setw(5) << "No." 
                << setw(20) << "Nombre" 
                << setw(15) << "Tipo" 
                << setw(10) << "Usos" << "\n";
            cout << "---------------------------------------------------\n";

            // Filas de la tabla
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
        nodoEspecie* cabeza;

    public:
        listaEspecies() {
            cabeza = nullptr;
        }
        ~listaEspecies() {
            limpieza();
        }

        void limpieza(){
            nodoEspecie* actual = cabeza;
            while(actual!=nullptr) {
                nodoEspecie* siguiente= actual->siguiente;
                delete actual;
                actual=siguiente;
            }
            cabeza= nullptr;
        }

        void agregarEspecie(string nombre, string tipo, int fortaleza,int ataque, int salud, int rapidez) {
            especie nuevaEspecie;
            nuevaEspecie.nombre = nombre;
            nuevaEspecie.salud = salud;
            nuevaEspecie.rapidez = rapidez;

            if (tipo == "Heroe") {
                nuevaEspecie.fortaleza = fortaleza;
                nuevaEspecie.ataque = 0; 
            } else if (tipo == "Orco") {
                nuevaEspecie.ataque = ataque;
                nuevaEspecie.fortaleza = 0;
            }

            nodoEspecie* nuevoNodo = new nodoEspecie;
            nuevoNodo->dato = nuevaEspecie;
            nuevoNodo->siguiente = nullptr;

            if (cabeza==nullptr) {
                cabeza = nuevoNodo;
            } else {
                nodoEspecie* temp = cabeza;
                while (temp->siguiente!=nullptr) {
                    temp = temp->siguiente;
                }
                temp->siguiente = nuevoNodo;
            }
        }

        void agregarEspecie() {
            especie nuevaEspecie;
            string tipo;
            bool tipoInvalido;

            //ingreso del nombre y vaidacion
            while (true) {
                cout<<"Ingrese el nombre de la especie: ";
                cin>>nuevaEspecie.nombre;

                //esto valida q el nombre tenga letras
                bool valido = true;
                for (char c : nuevaEspecie.nombre) {
                    if (!isalpha(c)) {
                        valido = false;
                        break;
                    }
                }

                if (valido) {
                    break; 
                } else {
                    cout<<"Nombre no valido. Solo se permiten letras. Intenta de nuevo." << endl;
                }
            }

            //esto es para validar el tipo de especie heroe o orco
            while (true) {
                cout<<"La especie es un Heroe o un Orco? (H/O): ";
                cin>>tipo;

                if (tipo=="h" || tipo=="H") {
                    cout<<"Ingrese la fortaleza del heroe: ";
                    while (!(cin>>nuevaEspecie.fortaleza)) {
                        cout<<"Numero invalido. Ingresa un numero para la fortaleza del heroe: ";
                        cin.clear();//limpia la entrada fea
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');//ignora el resto de la entrada fea
                    }
                    nuevaEspecie.ataque = 0;
                    nuevaEspecie.tipo = "Heroe";
                    break;
                } else if (tipo=="o" || tipo=="O") {
                    cout<<"Ingrese el ataque del orco: ";
                    while (!(cin>>nuevaEspecie.ataque)) {
                        cout<<"Numero invalido. Ingresa un numero para el ataque: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    nuevaEspecie.fortaleza = 0;
                    nuevaEspecie.tipo = "Orco";
                    break;
                } else {
                    cout<<"Su tipo no es valido. Intenta de nuevo."<<endl;
                }
            }

            //esto valida la rapidez y la salud
            cout<<"Ingrese la salud de la especie: ";
            while (!(cin>>nuevaEspecie.salud)) {
                cout<<"Numero invalido. Ingresa un numero para la salud: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout<<"Ingrese la rapidez de la especie: ";
            while (!(cin>>nuevaEspecie.rapidez)) {
                cout<<"Numero invalido. Ingresa un numero para la rapidez: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            nodoEspecie* nuevoNodo = new nodoEspecie;
            nuevoNodo->dato = nuevaEspecie;
            nuevoNodo->siguiente = nullptr;

            if (cabeza==nullptr) {
                cabeza = nuevoNodo;
            } else {
                nodoEspecie* temp = cabeza;
                while (temp->siguiente != nullptr) {
                    temp = temp->siguiente;
                }
                temp->siguiente = nuevoNodo;
            }
            cout<<"Especie '"<<nuevaEspecie.nombre<<"' agregada."<<endl;
        }
    
        void mostrarEspecies() {
            if (cabeza == nullptr) {
                cout << "No hay especies registradas." << endl;
                return;
            }
            // Encabezado de la tabla
            cout << left << setw(5) << "No." 
                << setw(20) << "Especie" 
                << setw(15) << "Fortaleza" 
                << setw(10) << "Ataque" 
                << setw(10) << "Salud" 
                << setw(10) << "Rapidez" << endl;
            cout << "-------------------------------------------------------------------\n";
            int cont = 0;
            nodoEspecie* temp = cabeza;
            while (temp != nullptr) {
                cont += 1;
                cout << left << setw(5) << cont 
                    << setw(20) << temp->dato.nombre 
                    << setw(15) << temp->dato.fortaleza 
                    << setw(10) << temp->dato.ataque 
                    << setw(10) << temp->dato.salud 
                    << setw(10) << temp->dato.rapidez << endl;
                temp = temp->siguiente;
            }
            cout << "-------------------------------------------------------------------\n";
            cout << "Ataque=0 Heroe, Fortaleza=0 Orco" << endl;
        }

        nodoEspecie* obtenerCabeza() {
            return cabeza;
        }

        nodoEspecie* seleccionarEspeciePorIndice() {
            if (!cabeza) {
                cout << "No hay especies registradas.\n";
                return nullptr;
            }
            // Encabezado de la tabla
            cout << "\n=== Especies disponibles ===\n";
            cout << left << setw(5) << "No." 
                << setw(20) << "Especie" << endl;
            cout << "-------------------------------------\n";
            nodoEspecie* temp = cabeza;
            int i = 1;
            while (temp) {
                cout << left << setw(5) << i 
                    << setw(20) << temp->dato.nombre << endl;
                temp = temp->siguiente;
                i++;
            }
            cout << "-------------------------------------\n";
            int seleccion;
            cout << "Selecciona el numero de la especie: ";
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

        void eliminarPrimeraEspecie() {
            if (cabeza) {
                nodoEspecie* temp = cabeza;
                cabeza = cabeza->siguiente;
                delete temp;
            }
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
                cout << "¿Sera un Heroe o un Orco? (H/O): ";
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
                    cout << "Opcion no valida. Intenta de nuevo."<<endl;
                }
            }

            cout << "Nueva salud: ";
            cin >> esp.salud;

            cout << "Nueva rapidez: ";
            cin >> esp.rapidez;

            cout << "Especie modificada exitosamente."<<endl;
        }
};

//Lista de los Personajes
class listaPersonajes {
    private:
        nodoPersonaje* cabeza;
        listaEspecies* lista_especies;
        listaImplementos* lista_implementos;

    public:
        listaPersonajes(listaEspecies& especies) : cabeza(nullptr), lista_especies(&especies) {}

        ~listaPersonajes() {
            limpieza();
        }

        void limpieza() {
            nodoPersonaje* actual = cabeza;
            while(actual != nullptr) {
                nodoPersonaje* siguiente = actual->siguiente;
                delete actual;
                actual = siguiente;
            }
            cabeza = nullptr;
        }

        nodoPersonaje* obtenerCabeza() {
            return cabeza;
        }

        void agregarPersonaje(string nombre_especie, string nombre_personaje) {
            nodoEspecie* especie_ptr = buscarEspecie(nombre_especie);
            if (!especie_ptr) {
                cout<<"Error: Especie '"<<nombre_especie<<"' no encontrada."<<endl;
                return;
            }

            personaje nuevo;
            nuevo.nombre = nombre_personaje;
            nuevo.especie = especie_ptr;

            nodoPersonaje* nuevo_nodo = new nodoPersonaje{nuevo, nullptr};

            if (cabeza == nullptr) {
                cabeza = nuevo_nodo;
            } else {
                nodoPersonaje* temp = cabeza;
                while (temp->siguiente != nullptr) {
                    temp = temp->siguiente;
                }
                temp->siguiente = nuevo_nodo;
            }
        }

        void agregarPersonaje() {
            personaje nuevo;

            while (true) {
                cout<<"Ingresa el nombre del personaje: ";
                cin>>nuevo.nombre;

                bool valido = true;
                for (char c : nuevo.nombre) {
                    if (!isalpha(c)) {
                        valido = false;
                        break;
                    }
                }

                if (valido) break;
                cout<<"Nombre invalido, solo letras. Intenta denuevo."<<endl;
            }

            cout<<"Selecciona una especie para el personaje"<<endl;
            cout<<"_________________________________"<<endl;
            lista_especies->mostrarEspecies();

            int op;
            while (true) {
                cout<<"Ingresa el numero de la especie: ";
                cin>>op;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout<<"Numero invalido. Ingresa un numero."<<endl;
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                nodoEspecie* tempEsp = lista_especies->obtenerCabeza();
                int cont = 1;
                while (tempEsp != nullptr && cont < op) {
                    tempEsp = tempEsp->siguiente;
                    cont++;
                }

                if (tempEsp == nullptr) {
                    cout<<"No existe una especie con ese numero. Intenta denuevo."<<endl;
                    continue;
                }

                nuevo.especie = tempEsp;
                break;
                }

            nodoPersonaje* nuevo_nodo = new nodoPersonaje{nuevo, nullptr};

            if (cabeza == nullptr) {
                cabeza = nuevo_nodo;
            } else {
                nodoPersonaje* temp = cabeza;
                while (temp->siguiente != nullptr) {
                    temp = temp->siguiente;
                }
                temp->siguiente = nuevo_nodo;
            }        
            cout<<"Personaje '"<<nuevo.nombre <<"' agregado exitosamente."<<endl;
            }

    private:
        nodoEspecie* buscarEspecie(string nombre) {
            nodoEspecie* temp = lista_especies->obtenerCabeza();
            while (temp != nullptr) {
                if (temp->dato.nombre == nombre) {
                    return temp;
                }
                temp = temp->siguiente;
            }
            return nullptr;
        }

    public:

        nodoPersonaje* obtenerPjInd(int ind) { //obtener indice del personaje
            nodoPersonaje* temp = cabeza;
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
            nodoPersonaje* temp = cabeza;
            int cont = 1;
            while (temp != nullptr) {
                cout << left << setw(5) << cont 
                    << setw(20) << temp->dato.nombre 
                    << setw(20) << temp->dato.especie->dato.nombre << endl;
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
            // Encabezado de la tabla
            cout << left << setw(5) << "No." 
                << setw(20) << "Nombre" 
                << setw(30) << "Mochila" << endl;
            cout << "-------------------------------------------------------------\n";
            nodoPersonaje* temp = cabeza;
            int cont = 1;
            while (temp != nullptr) {
                cout << left << setw(5) << cont 
                    << setw(20) << temp->dato.nombre 
                    << setw(30);
                if (temp->dato.mochila.numImplementos == 0) {
                    cout << "Vacía";
                } else {
                    for (int i = 0; i < temp->dato.mochila.numImplementos; i++) {
                        cout << "'" << temp->dato.mochila.implementos[i]->nombre << "'";
                        if (i < temp->dato.mochila.numImplementos - 1) {
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

        nodoPersonaje* seleccionarPersonajePorIndice() {
            if (!cabeza) {
                cout << "No hay personajes registrados.\n";
                return nullptr;
            }
            // Encabezado de la tabla
            cout << "\n=== Personajes disponibles ===\n";
            cout << left << setw(5) << "No." 
                << setw(20) << "Nombre" << endl;
            cout << "-------------------------------------\n";
            nodoPersonaje* temp = cabeza;
            int i = 1;
            while (temp) {
                cout << left << setw(5) << i 
                    << setw(20) << temp->dato.nombre << endl;
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
            nodoPersonaje* seleccionada = seleccionarPersonajePorIndice();
            if (!seleccionada) return;
            nodoPersonaje* actual = cabeza;
            nodoPersonaje* anterior = nullptr;
            while (actual) {
                if (actual == seleccionada) {
                    string nombreEliminado = actual->dato.nombre;
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
            nodoPersonaje* seleccionada = seleccionarPersonajePorIndice();
            if (!seleccionada) return;

            personaje& pj = seleccionada->dato;
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
                    cout << "Nombre invalido, solo letras. Intenta denuevo." << endl;
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

                nodoEspecie* tempEsp = lista.obtenerCabeza();
                int cont = 1;
                while (tempEsp != nullptr && cont < op) {
                    tempEsp = tempEsp->siguiente;
                    cont++;
                }
                if (tempEsp == nullptr) {
                    cout << "No hay especies con ese numero, intenta denuevo." << endl;   
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
            nodoPersonaje* personaje = obtenerPjInd(seleccion);
            if (!personaje) {
                cout << "Selección inválida.\n";
                return;
            }

            int opcion;
            do {
                cout << "\n--- Mochila de " << personaje->dato.nombre << " ---\n";
                personaje->dato.mochila.mostrarMochila();
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
                                implemento* imp = listaImplementos.obtenerImplemento(impSel-1);
                                personaje->dato.mochila.agregarImplementoAMochila(imp);
                            } else {
                                cout << "Selección inválida.\n";
                            }
                        }
                        break;
                    case 2:
                        if (personaje->dato.mochila.numImplementos > 0) {
                            cout << "Selecciona el implemento a eliminar: ";
                            int impSel = leerOpcion();
                            if (impSel > 0 && impSel <= personaje->dato.mochila.numImplementos) {
                                personaje->dato.mochila.eliminarImplementoEnMochila(impSel-1);
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

//Funcion para eliminar especies (para evitar generar mas dependencias circulares entre las clases listaEspecies y listaPersonajes)
void eliminarEspecie(listaEspecies& especies, listaPersonajes& personajes) {
    if (especies.obtenerCabeza() == nullptr) {
        cout<<"No hay especies registradas para eliminar."<<endl;
        return;
    }

    cout<<"\n___ Especies disponibles ___"<<endl;
    especies.mostrarEspecies();

    nodoEspecie* especieSeleccionada = especies.seleccionarEspeciePorIndice();
    if (!especieSeleccionada) {
        return;
    }

    bool especieEnUso = false;
    nodoPersonaje* personajeActual = personajes.obtenerCabeza();
    while (personajeActual) {
        if (personajeActual->dato.especie == especieSeleccionada) {
            especieEnUso = true;
            break;
        }
        personajeActual = personajeActual->siguiente;
    }

    if (especieEnUso) {
        cout<<"No se puede eliminar la especie '"<<especieSeleccionada->dato.nombre<<"' porque hay personajes que la utilizan."<<endl;
    } else {
        string nombreEspecie = especieSeleccionada->dato.nombre;
        nodoEspecie* actual = especies.obtenerCabeza();
        nodoEspecie* anterior = nullptr;
        bool eliminado = false;

        while (actual && !eliminado) {
            if (actual == especieSeleccionada) {
                if (!anterior) {
                    especies.eliminarPrimeraEspecie();
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
            cout<<"Especie '"<<nombreEspecie<<"' eliminada correctamente."<<endl;
        } else {
            cout<<"Error: No se pudo eliminar la especie."<<endl;
        }
    }
}

//Estructura de los Equipos
struct equipo {
    string nombre;
    nodoPersonaje* personajes[4];
    int numPjs; //Numero de personajes
};
struct nodoEquipo {
    equipo dato;
    nodoEquipo* siguiente;
};

//Estructura de las Salas
struct Adyacencia {
    int idSala;
    int distancia;
    Adyacencia* siguiente;
};
struct Sala {
    int id;
    string nombre;
    Adyacencia* adyacencias;
    Sala* siguiente;
};

//Lista de los Equipos
class listaEquipos {
    private:
        nodoEquipo* cabeza;
    public:
        listaEquipos() {
            cabeza = nullptr;
        }

        ~listaEquipos() {
            limpieza();
        }

    void limpieza(){
        nodoEquipo* actual = cabeza;
        while(actual!=nullptr) {
            nodoEquipo* siguiente= actual->siguiente;
            delete actual;
            actual=siguiente;
        }
        cabeza= nullptr;
    }

        void agregarEquipo(listaPersonajes& listaPersonajes) {
            equipo nuevoEquipo;
            cout<<"Ingrese el nombre del equipo: ";
            cin>>nuevoEquipo.nombre;
            nuevoEquipo.numPjs = 0;

            while(nuevoEquipo.numPjs<4) {
                cout<<endl<<"Selecciona un personaje para el equipo (por numero)"<<endl;
                listaPersonajes.mostrarPersonajes();

                int op;
                cout<<"Ingresa el numero del personaje (0 para terminar): ";
                cin>>op;

                if(cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout<<"Numero no valido, por favor ingresa un numero."<<endl;
                    continue;
                }
                
                if (op==0) {
                    break;
                }

                nodoPersonaje* temp = listaPersonajes.obtenerPjInd(op);
                if (temp==nullptr) {
                    cout<<"Numero no valido, intenta denuevo."<<endl;
                    continue;
                }

                bool rep = false; //rep = repetido
                for(int i = 0; i<nuevoEquipo.numPjs; i++) {
                    if (nuevoEquipo.personajes[i]==temp) {
                        rep = true;
                        break;
                    }
                }

                if (rep) {
                    cout<<"Este personaje ya esta en el equipo."<<endl;
                    continue;
                }

                nuevoEquipo.personajes[nuevoEquipo.numPjs] = temp;
                nuevoEquipo.numPjs += 1;
                cout<<"Personaje '"<<temp->dato.nombre<<"' agregado al equipo"<<endl;
            }
            
            if (nuevoEquipo.numPjs == 0) {
                cout<<"No se agrego ningun personaje, no se creo el equipo."<<endl;
                return;
            }

            nodoEquipo* nuevoNodo = new nodoEquipo;
            nuevoNodo->dato = nuevoEquipo;
            nuevoNodo->siguiente = cabeza;
            cabeza = nuevoNodo;

            cout<<"Equipo '"<<nuevoEquipo.nombre<<"' creado.";
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

            nodoEquipo* temp = cabeza;
            int cont = 1;
            while (temp != nullptr) {
                cout << left << setw(5) << cont++ 
                    << setw(30) << temp->dato.nombre 
                    << setw(25);

                ostringstream personajesList;
                for (int i = 0; i < temp->dato.numPjs; i++) {
                    nodoPersonaje* personaje = temp->dato.personajes[i];
                    if (personaje != nullptr) {
                        personajesList << personaje->dato.nombre;
                        if (i < temp->dato.numPjs - 1) {
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

        nodoEquipo* seleccionarEquipoPorIndice() {
            if (!cabeza) {
                cout << "No hay equipos registrados.\n";
                return nullptr;
            }
            cout << "\n=== Equipos disponibles ===\n";
            cout << left << setw(5) << "No." 
                << setw(30) << "Nombre del Equipo" << endl;
            cout << string(40, '-') << endl;
            nodoEquipo* temp = cabeza;
            int i = 1;
            while (temp) {
                cout << left << setw(5) << i++ 
                    << setw(30) << temp->dato.nombre << endl;
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
            nodoEquipo* seleccionada = seleccionarEquipoPorIndice();
            if (!seleccionada) return;

            nodoEquipo* actual = cabeza;
            nodoEquipo* anterior = nullptr;

            while (actual) {
                if (actual == seleccionada) {
                    if (!anterior) cabeza = actual->siguiente;
                    else anterior->siguiente = actual->siguiente;
                    delete actual;
                    cout << "Equipo eliminado."<<endl;
                    return;
                }
                anterior = actual;
                actual = actual->siguiente;
            }
            cout << "No se encontro el equipo."<<endl;
        }
    
};

//Lista de las Salas
class listaSalas {
private:
    Sala* cabeza;

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
                cout<<"Error: se encontre un caracter que no es numero: "<<c<< endl;
                return -1;
            }
        }

        if (!encontradoDigito) {
            cout<<"Error: no se encontraron digitos."<<endl;
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
            cout<<"Ingresa el nombre de la sala: ";
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
                cout<<"Nombre no valido, solo letras y espacios. Intenta denuevo."<<endl;
            }
        }

        Adyacencia* adyacencias = nullptr;
        Adyacencia* ultimoAdyacente = nullptr;
        char continuar;

        do {
            int idAdyacente, distancia;

            while (true) {
                mostrarSalas();
                cout<<"Ingresa el ID de la sala adyacente (o -1 para terminar): ";
                cin>>idAdyacente;
                if (idAdyacente == -1) break;

                while (true) {
                    cout<<"Ingresa la distancia a la sala adyacente: ";
                    string input;
                    cin>>input;
                    distancia = convertirAEntero(input);
                    if (distancia != -1) break;
                }

                Adyacencia* nuevoAdyacente = new Adyacencia{idAdyacente, distancia, nullptr};
                if (adyacencias == nullptr) {
                    adyacencias = nuevoAdyacente;
                } else {
                    ultimoAdyacente->siguiente = nuevoAdyacente;
                }
                ultimoAdyacente = nuevoAdyacente;
                
                cout<<"Adyacencia añadida."<<endl;
            }

            cout<<"Quiere agregar otra adyacencia? (s/n): ";
            cin>>continuar;
        } while (continuar == 's' || continuar == 'S');

        agregarSala(id, nombre, adyacencias);
        cout<<"Sala '"<<nombre<<"' agregada."<<endl;
    }

    void eliminarSala() {
        mostrarSalas();
        cout<<"__________________________\n";

        int id;
        while (true) {
            cout<<"Ingresa el ID de la sala a eliminar: ";
            string input;
            cin>>input;
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
            cout<<"Sala no encontrada,"<<endl;
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
        cout<<"Sala eliminada."<<endl;
    }

    void modificarSala() {
    mostrarSalas();
        cout<<"__________________________\n";

        int id;
        while (true) {
            cout<<"Ingresa el ID de la sala a modificar: ";
            string input;
            cin>>input;
            id = convertirAEntero(input);
            if (id != -1) break;
        }

        Sala* actual = cabeza;
        while (actual != nullptr && actual->id != id) {
            actual = actual->siguiente;
        }

        if (actual == nullptr) {
            cout<<"Sala no encontrada."<<endl;
            return;
        }

        string nuevoNombre;
        while (true) {
            cout<<"\nNombre actual: "<<actual->nombre<<endl;
            cout<<"Ingresa el nuevo nombre de la sala: ";
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
                cout<<"Nombre no valido, solo letras y espacios. Intenta denuevo." << endl;
            }
        }

        Adyacencia* nuevasAdyacencias = nullptr;
        Adyacencia* ultimoAdyacente = nullptr;
        char continuar;

        cout<<"\n___ Adyacencias Actuales ___"<<endl;
        Adyacencia* adyacenteActual = actual->adyacencias;
        while (adyacenteActual != nullptr) {
            cout<<adyacenteActual->idSala<<":"<<adyacenteActual->distancia<<" ";
            adyacenteActual = adyacenteActual->siguiente;
        }
        cout<<"\n__________________________\n";

        do {
            cout<<"Que quiere hacer con las adyacencias?"<<endl;
            cout<<"1. Agregar nueva adyacencia"<<endl;
            cout<<"2. Eliminar adyacencia existente"<<endl;
            cout<<"3. Cambiar distancia de una adyacencia"<<endl;
            cout<<"4. Terminar modificaciones"<<endl;
            cout<<"Selecciona una opcion: ";
            int opcion;
            cin>>opcion;

            switch (opcion) {
                case 1: {
                    int idAdyacente, distancia;

                    while (true) {
                        mostrarSalas();
                        cout<<"Ingresa el ID de la nueva sala adyacente: ";
                        cin>>idAdyacente;

                        while (true) {
                            cout<<"Ingresa la distancia a la nueva sala adyacente: ";
                            string input;
                            cin>>input;
                            distancia = convertirAEntero(input);
                            if (distancia != -1) break;
                        }

                        Adyacencia* nuevoAdyacente = new Adyacencia{idAdyacente, distancia, nullptr};
                        if (nuevasAdyacencias == nullptr) {
                            nuevasAdyacencias = nuevoAdyacente;
                        } else {
                            ultimoAdyacente->siguiente = nuevoAdyacente;
                        }
                        ultimoAdyacente = nuevoAdyacente;

                        cout<<"Adyacencia añadida."<<endl;
                        break;
                    }
                    break;
                }
                case 2: {
                    int idAdyacente;
                    cout<<"Ingresa el ID de la sala adyacente a eliminar: ";
                    cin>>idAdyacente;

                    Adyacencia* actualAdyacente = actual->adyacencias;
                    Adyacencia* anteriorAdyacente = nullptr;

                    while (actualAdyacente != nullptr && actualAdyacente->idSala != idAdyacente) {
                        anteriorAdyacente = actualAdyacente;
                        actualAdyacente = actualAdyacente->siguiente;
                    }

                    if (actualAdyacente == nullptr) {
                        cout<<"Adyacencia no encontrada."<<endl;
                    } else {
                        if (anteriorAdyacente == nullptr) {
                            actual->adyacencias = actualAdyacente->siguiente; // Eliminar el primer elemento
                        } else {
                            anteriorAdyacente->siguiente = actualAdyacente->siguiente; // Eliminar el elemento intermedio
                        }
                        delete actualAdyacente;
                        cout<<"Adyacencia eliminada."<<endl;
                    }
                    break;
                }
                case 3: { // Cambiar distancia de una adyacencia
                    int idAdyacente;
                    cout<<"Ingresa el ID de la sala adyacente para cambiar su distancia: ";
                    cin>>idAdyacente;

                    Adyacencia* actualAdyacente = actual->adyacencias;

                    while (actualAdyacente != nullptr && actualAdyacente->idSala != idAdyacente) {
                        actualAdyacente = actualAdyacente->siguiente;
                    }

                    if (actualAdyacente == nullptr) {
                        cout<<"Adyacencia no encontrada."<<endl;
                    } else {
                        int nuevaDistancia;
                        while (true) {
                            cout<<"Ingresa la nueva distancia para la adyacencia: ";
                            string input;
                            cin>>input;
                            nuevaDistancia = convertirAEntero(input);
                            if (nuevaDistancia != -1) break;
                        }
                        actualAdyacente->distancia = nuevaDistancia;
                        cout<<"Distancia actualizada."<<endl;
                    }
                    break;
                }
                case 4:
                    continuar = 'n';
                    break;
                default:
                    cout<<"Opción no valida. Intenta denuevo"<<endl;
            }
        } while (continuar != 'n');
        actual->nombre = nuevoNombre;
        cout << "Sala modificada." << endl;
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
                while (adyacenteActual != nullptr) {
                    cout << adyacenteActual->idSala << ":" << adyacenteActual->distancia << " ";
                    adyacenteActual = adyacenteActual->siguiente;
                }
            }
            cout << endl;
            actual = actual->siguiente;
        }
        cout << string(85, '-') << endl; 
    }

    void leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout<<"Error al abrir el archivo."<<endl;
        return;
    }

    string linea;
    int cantidadSalas;
    getline(archivo, linea);
    cantidadSalas = convertirAEntero(linea); //Leer la cantidad de salas

    while (getline(archivo, linea)) {
        if (linea == "---") continue; //Separador entre registros

        //Leer ID de la sala
        int id = convertirAEntero(linea);
        if (id == -1) return; // Salir si hay un error

        getline(archivo, linea);// Leer nombre de la sala
        string nombre = linea;

        getline(archivo, linea); //Leer el separador "--"
        getline(archivo, linea); //Leer adyacencias
        Adyacencia* adyacencias = nullptr;
        Adyacencia* ultimoAdyacente = nullptr;

        if (!linea.empty()) {
            stringstream ss(linea);
            string adyacente;
            while (getline(ss, adyacente, '|')) {
                //Obtener ID y distancia
                size_t pos = adyacente.find(':');
                int idAdyacente = convertirAEntero(adyacente.substr(0, pos));
                int distancia = convertirAEntero(adyacente.substr(pos + 1));

                if (idAdyacente == -1 || distancia == -1) return; // Salir si hay un error

                Adyacencia* nuevoAdyacente = new Adyacencia{idAdyacente, distancia, nullptr};
                if (adyacencias == nullptr) {
                    adyacencias = nuevoAdyacente;
                } else {
                    ultimoAdyacente->siguiente = nuevoAdyacente;
                }
                ultimoAdyacente = nuevoAdyacente;
            }
        }

        agregarSala(id, nombre, adyacencias);
        getline(archivo, linea); //Leer el separador "---"
    }
    archivo.close();
    }
};

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

int main() {
    listaEspecies listaEspecies;
    listaPersonajes listaPersonajes(listaEspecies);
    listaEquipos listaEquipos;
    listaImplementos listaImplementos;
    listaSalas listaSalas;

    //especies
    listaEspecies.agregarEspecie("Elfo", "Heroe", 50, 0, 120, 25);
    listaEspecies.agregarEspecie("Hombre", "Heroe", 110, 0, 100, 15);
    listaEspecies.agregarEspecie("Enano", "Heroe", 80, 0, 80, 10);
    listaEspecies.agregarEspecie("Hobbit", "Heroe", 75, 0, 70, 20);
    listaEspecies.agregarEspecie("Mago", "Heroe", 95, 0, 90, 15);

    //personajes
    listaPersonajes.agregarPersonaje("Enano", "Manolo");
    listaPersonajes.agregarPersonaje("Hobbit", "Rufus");
    listaPersonajes.agregarPersonaje("Mago", "Bartolo");
    listaPersonajes.agregarPersonaje("Hombre", "Lucius");
    listaPersonajes.agregarPersonaje("Elfo", "Erd");

    //implementos
    listaImplementos.agregarImplemento("Espada", "atacar", 10, 100, 25, 0, 0);
    listaImplementos.agregarImplemento("Arco", "atacar", 15, 50, 10, 0, 0);
    listaImplementos.agregarImplemento("Pocion de curacion", "curar", 3, 25, 0, 0, 40);
    listaImplementos.agregarImplemento("Palo", "atacar", 1, 10, 100, 0, 0);
    listaImplementos.agregarImplemento("Escudo", "defender", 5, 125, 0, 0, 0);

    //salas
    listaSalas.leerArchivo("salas.txt");

    int op = 0;
    cout<<"\n___Bienvenido a Khazad-Dum___"<<endl;
    do {
        cout<<"____Menu de Interacciones____"<<endl;
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
                return 0;
        }
    }while (op!=5);
    return 0;
}

