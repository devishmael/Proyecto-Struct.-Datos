#include <iostream>
#include <limits>
using namespace std;

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

struct personaje {
    string especie;
    string nombre;
};

struct nodoPersonaje {
    personaje dato;
    nodoPersonaje* siguiente;
};

struct equipo {
    string nombre;
    nodoPersonaje* personajes[4];
    int numPjs; //Numero de personajes
};

struct nodoEquipo {
    equipo dato;
    nodoEquipo* siguiente;
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

class listaEspecies {
    private:
        nodoEspecie* cabeza;

    public:
        listaEspecies() {
        cabeza = nullptr;
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
    
    void mostrarEspecie() {
        if (cabeza == nullptr) {
            cout<<"No hay especies registradas."<<endl;
            return;
        }

        int cont = 0;

        nodoEspecie* temp = cabeza;
        while (temp != nullptr) {
            cont += 1;
            cout<<cont<<". "<<"Especie: "<<temp->dato.nombre<<endl;
            cout<<"Forzaleza: "<<temp->dato.fortaleza<<endl;
            cout<<"Ataque: "<<temp->dato.ataque<<endl;
            cout<<"Salud: "<<temp->dato.salud<<endl;
            cout<<"Rapidez: "<<temp->dato.rapidez<<endl<<endl;
            temp = temp->siguiente;

        }
        cout<<"Ataque=0 Heroe, Fortaleza=0 Orco"<<endl;
    }

    nodoEspecie* obtenerCabeza() {
        return cabeza;
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
                cout << "Especie eliminada."<<endl;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }

        cout << "No se encontro la especie."<<endl;
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

class listaPersonajes {
    private:
        nodoPersonaje* cabeza;
    public:
        listaPersonajes() {
            cabeza = nullptr;
        }
    
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

        void agregarPersonaje(string especie, string nombre) {
            personaje nuevoPersonaje;
            nuevoPersonaje.nombre = nombre;
            nuevoPersonaje.especie = especie;

            nodoPersonaje* nuevoNodo = new nodoPersonaje;
            nuevoNodo->dato = nuevoPersonaje;
            nuevoNodo->siguiente = nullptr;

            if (cabeza==nullptr) {
                cabeza = nuevoNodo;
            } else {
                nodoPersonaje* temp = cabeza;
                while (temp->siguiente!=nullptr) {
                    temp = temp->siguiente;
                }
                temp->siguiente = nuevoNodo;
            }
        }
        
        void agregarPersonaje(listaEspecies& lista) {
            personaje nuevoPersonaje;

            //ingreso del nombre y vaidacion
            while (true) {
                cout<<"Ingrese el nombre del personaje: ";
                cin>>nuevoPersonaje.nombre;

                //esto valida q el nombre tenga letras
                bool valido = true;
                for (char c : nuevoPersonaje.nombre) {
                    if (!isalpha(c)) {
                        valido = false;
                        break;
                    }
                }

                if (valido) {
                    break; 
                } else {
                    cout<<"Nombre no valido. Solo letras. Intenta de nuevo." << endl;
                    }
            }

            cout<<"Selecciona una especie para el personaje"<<endl;
            cout<<"_________________________________"<<endl;
            lista.mostrarEspecie();

            int op; 
            while (true) {
                cout << "Ingresa el numero de la especie: ";
                cin >> op;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Numero no valido. Por favor ingresa un numero."<<endl;
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                nodoEspecie* tempEsp = lista.obtenerCabeza();
                int cont = 1;
                while (tempEsp != nullptr && cont < op) {
                    tempEsp = tempEsp->siguiente;
                    cont++;
                }

                if (tempEsp == nullptr || tempEsp->dato.tipo != "Heroe") {
                    cout << "No existe una especie con ese numero. Intenta de nuevo."<<endl;
                    continue;
                }

                nuevoPersonaje.especie = tempEsp->dato.nombre;
                break;
            }

            nodoPersonaje* nuevoNodo = new nodoPersonaje;
            nuevoNodo->dato = nuevoPersonaje;
            nuevoNodo->siguiente = nullptr;

            if (cabeza==nullptr) {
                cabeza = nuevoNodo;
            } else {
                nodoPersonaje* temp = cabeza;
                while (temp->siguiente != nullptr) {
                temp = temp->siguiente;
                }
                temp->siguiente = nuevoNodo;
            }
           cout<<"Personaje '"<<nuevoPersonaje.nombre<<"' agregado."<<endl;
        }

        void mostrarPersonaje() {
            if (cabeza == nullptr) {
                cout<<"No hay personajes registrados."<<endl;
                return;
                }

            nodoPersonaje* temp = cabeza;
            int cont = 1;
            while (temp != nullptr) {
                cout<<cont<<". Nombre: "<<temp->dato.nombre<<endl;
                cout<<"Especie: "<<temp->dato.especie<<endl<<endl;
                temp = temp->siguiente;
                cont++;
            }
        }

        nodoPersonaje* seleccionarPersonajePorIndice() {
            if (!cabeza) {
                cout << "No hay personajes registrados.\n";
                return nullptr;
            }

            cout << "\n=== Personajes disponibles ===\n";
            nodoPersonaje* temp = cabeza;
            int i = 1;
            while (temp) {
                cout << i << ". " << temp->dato.nombre << endl;
                temp = temp->siguiente;
                i++;
            }

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
                if (!anterior) cabeza = actual->siguiente;
                else anterior->siguiente = actual->siguiente;
                delete actual;
                cout << "Personaje '"<< actual->dato.nombre <<"' eliminado."<<endl;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }

        cout << "No se encontro el personaje."<<endl;
    }

    void modificarPersonaje(listaEspecies& lista) {
        nodoPersonaje* seleccionada = seleccionarPersonajePorIndice();
        if (!seleccionada) return;

        personaje& esp = seleccionada->dato;
        while (true) {
            cout<<"Ingrese el nombre del personaje: ";
            cin>>esp.nombre;

            //esto valida q el nombre tenga letras
            bool valido = true;
            for (char c : esp.nombre) {
                if (!isalpha(c)) {
                    valido = false;
                    break;
                }
            }

            if (valido) {
                break; 
            } else {
                cout<<"Nombre no valido. Solo letras. Intenta de nuevo." << endl;
                }
        }

        cout<<"\n --Lista de Especies--\n";
        lista.mostrarEspecie();

        int op; 
        while (true) {
            cout << "Ingresa el numero de la especie: ";
            cin >> op;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Numero no valido. Por favor ingresa un numero."<<endl;
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
                cout<<"No hay especies con ese numero, intenta denuevo."<<endl;   
                continue;
                
            }

            esp.especie = tempEsp->dato.nombre;
            break;
        }

        cout << "Personaje modificado."<<endl;
    }


};

class listaEquipos {
    private:
        nodoEquipo* cabeza;
    public:
        listaEquipos() {
            cabeza = nullptr;
        }

        void agregarEquipo(listaPersonajes& listaPersonajes) {
            equipo nuevoEquipo;
            cout<<"Ingrese el nombre del equipo: ";
            cin>>nuevoEquipo.nombre;
            nuevoEquipo.numPjs = 0;

            while(nuevoEquipo.numPjs<4) {
                cout<<endl<<"Selecciona un personaje para el equipo (por numero)"<<endl;
                listaPersonajes.mostrarPersonaje();

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

        void mostrarEquipo() {
            if (cabeza == nullptr) {
                cout<<"No hay equipos registrados."<<endl;
                return;
                }

            nodoEquipo* temp = cabeza;
            int cont = 1;
            while (temp != nullptr) {
                cout<<"Equipo #"<<cont++<<": "<<temp->dato.nombre<<endl;
                cout<<"Personajes del equipo: "<<endl;

                for (int i = 0; i < temp->dato.numPjs; i++) {
                    nodoPersonaje* personaje = temp->dato.personajes[i];
                    if (personaje!=nullptr) {
                        cout<<" -"<<personaje->dato.nombre<<endl;
                    }
                }
                cout<<"______________"<<endl;
                temp = temp->siguiente;
            }
        }
    
};

class listaImplementos {
private:
    implemento* implementos;
    int capacidad;
    int cantidad;

public:
    listaImplementos() {
        capacidad = 10;
        cantidad = 0;
        implementos = new implemento[capacidad];
    }

    ~listaImplementos() {
        delete[] implementos;
    }

    void agregarImplemento() {
        if (cantidad == capacidad) {
            capacidad *= 2;
            implemento* nuevoArray = new implemento[capacidad];
            for (int i = 0; i < cantidad; i++) {
                nuevoArray[i] = implementos[i];
            }
            delete[] implementos;
            implementos = nuevoArray;
        }

        implemento nuevo;
        cin.ignore();
        cout << "Nombre del implemento: ";
        getline(cin, nuevo.nombre);

        string tipo;
        while (true) {
            cout << "Tipo (atacar / defender / curar): ";
            getline(cin, tipo);
            if (tipo == "atacar" || tipo == "defender" || tipo == "curar") {
                nuevo.tipo = tipo;
                break;
            } else {
                cout << "Tipo no válido. Por favor escribe 'atacar', 'defender' o 'curar'.\n";
            }
        }

        cout << "Usos: ";
        while (!(cin >> nuevo.usos)) {
            cout << "Entrada inválida. Ingrese un número entero: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Fortaleza: ";
        while (!(cin >> nuevo.fortaleza)) {
            cout << "Entrada inválida. Ingrese un número entero: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Valor de ataque: ";
        while (!(cin >> nuevo.valorAtk)) {
            cout << "Entrada inválida. Ingrese un número decimal: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Valor de defensa: ";
        while (!(cin >> nuevo.valorDef)) {
            cout << "Entrada inválida. Ingrese un número decimal: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Valor de curación: ";
        while (!(cin >> nuevo.valorHeal)) {
            cout << "Entrada inválida. Ingrese un número decimal: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        implementos[cantidad++] = nuevo;
        cout << "Implemento agregado correctamente.\n";
    }

    void mostrarImplementos() {
        if (cantidad == 0) {
            cout << "No hay implementos registrados.\n";
            return;
        }
        for (int i = 0; i < cantidad; i++) {
            cout << i+1 << ". " << implementos[i].nombre << " (" << implementos[i].tipo << ") - Usos: " << implementos[i].usos << "\n";
        }
    }

    void eliminarImplemento() {
        mostrarImplementos();
        cout << "Seleccione el número del implemento a eliminar: ";
        int sel = leerOpcion();
        if (sel < 1 || sel > cantidad) {
            cout << "Opción inválida.\n";
            return;
        }
        for (int i = sel - 1; i < cantidad - 1; i++) {
            implementos[i] = implementos[i + 1];
        }
        cantidad--;
        cout << "Implemento eliminado.\n";
    }

    void modificarImplemento() {
        mostrarImplementos();
        cout << "Seleccione el número del implemento a modificar: ";
        int sel = leerOpcion();
        if (sel < 1 || sel > cantidad) {
            cout << "Opción inválida.\n";
            return;
        }
        implemento& imp = implementos[sel - 1];
        cin.ignore();
        cout << "Nuevo nombre: ";
        getline(cin, imp.nombre);

        string tipo;
        while (true) {
            cout << "Nuevo tipo (atacar / defender / curar): ";
            getline(cin, tipo);
            if (tipo == "atacar" || tipo == "defender" || tipo == "curar") {
                imp.tipo = tipo;
                break;
            } else {
                cout << "Tipo no válido. Por favor escribe 'atacar', 'defender' o 'curar'.\n";
            }
        }

        cout << "Nuevos usos: ";
        cin >> imp.usos;
        cout << "Nueva fortaleza: ";
        cin >> imp.fortaleza;
        cout << "Nuevo valor de ataque: ";
        cin >> imp.valorAtk;
        cout << "Nuevo valor de defensa: ";
        cin >> imp.valorDef;
        cout << "Nuevo valor de curación: ";
        cin >> imp.valorHeal;
        cout << "Implemento modificado.\n";
    }
};

void verSubMenuModificar(listaEspecies& listaEspecies, listaPersonajes& listaPersonajes, listaEquipos& listaEquipos, listaImplementos& listaImplementos) {
    int op;
    cout<<"\n-- Modificar Elemento --"<<endl;
    cout<<"1. Especie"<<endl;
    cout<<"2. Personajes"<<endl;
    cout<<"3. Implementos"<<endl;
    cout<<"4. Equipos "<<endl;
    cout<<"5. Mochilas"<<endl;
    cout<<"6. Mapa"<<endl;
    cout<<"7. Volver al menu principal"<<endl;
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
            cout<<"Ingresando a la modificacion de personajes..."<<endl;
            cout<<"__________________"<<endl;
            listaPersonajes.modificarPersonaje(listaEspecies);
            break;
        case 3:
            cout<<"Ingresando a la modificacion de implementos..."<<endl;
            cout<<"__________________"<<endl;
            listaImplementos.modificarImplemento();
            break;
        case 4:
            cout<<"Ingresando a la modificacion de equipos..."<<endl;
            break;
        case 5:
            cout<<"Ingresando a la modificacion de mochilas..."<<endl;
            break;
        case 6:
            cout<<"Ingresando a la modificacion de mapas..."<<endl;
            break;
        case 7:
            return;
    }
} 

void verSubMenuEliminar(listaEspecies& listaEspecies, listaPersonajes& listaPersonajes, listaEquipos& listaEquipos, listaImplementos& listaImplementos) {
    int op;
    cout<<"\n-- Eliminar Elemento --"<<endl;
    cout<<"1. Especie"<<endl;
    cout<<"2. Personajes"<<endl;
    cout<<"3. Implementos"<<endl;
    cout<<"4. Equipos "<<endl;
    cout<<"5. Mochilas"<<endl;
    cout<<"6. Mapa"<<endl;
    cout<<"7. Volver al menu principal"<<endl;
    cout<<"Seleccione una opcion: ";
    op=leerOpcion();
    cout<<"______________________"<<endl;


    switch (op) {
        case 1:
            cout<<"Eliminando especie..."<<endl;
            cout<<"__________________"<<endl;
            listaEspecies.eliminarEspecie();
            break;        
        case 2:
            cout<<"Eliminando Personaje..."<<endl;
            cout<<"__________________"<<endl;
            listaPersonajes.eliminarPersonaje();
            break;
        case 3:
            cout<<"Ingresando a la eliminacion de implementos..."<<endl;
            cout<<"__________________"<<endl;
            listaImplementos.eliminarImplemento();
            break;
        case 4:
            cout<<"Ingresando a la eliminacion de equipos..."<<endl;
            break;
        case 5:
            cout<<"Ingresando a la eliminacion de mochilas..."<<endl;
            break;
        case 6:
            cout<<"Ingresando a la eliminacion de mapas..."<<endl;
            break;
        case 7:
            return;
    }
} 

void verSubMenuAgregar(listaEspecies& listaEspecies, listaPersonajes& listaPersonajes, listaEquipos& listaEquipos, listaImplementos& listaImplementos) {
    int op;
    cout<<"\n-- Crear Elemento --"<<endl;
    cout<<"1. Especie"<<endl;
    cout<<"2. Personajes"<<endl;
    cout<<"3. Implementos"<<endl;
    cout<<"4. Equipos "<<endl;
    cout<<"5. Mochilas"<<endl;
    cout<<"6. Mapa"<<endl;
    cout<<"7. Volver al menu principal"<<endl;
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
            listaPersonajes.agregarPersonaje(listaEspecies);
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
            cout<<"Ingresando a la creacion de mochilas..."<<endl;
            break;
        case 6:
            cout<<"Ingresando a la creacion de mapas..."<<endl;
            break;
        case 7:
            return;
    }
} 

void verSubMenuInformacion(listaEspecies& listaEspecies, listaPersonajes& listaPersonajes, listaEquipos& listaEquipos, listaImplementos& listaImplementos) {
    int op;
    cout<<"\n__Ver Informacion__"<<endl;
    cout<<"1. Especies"<<endl;
    cout<<"2. Personajes"<<endl;
    cout<<"3. Implementos"<<endl;
    cout<<"4. Equipos (Soldados)"<<endl;
    cout<<"5. Mochilas" << endl;
    cout<<"6. Mapas" << endl;
    cout<<"7. Resultados de Misiones"<<endl;
    cout<<"8. Bitacora"<<endl;
    cout<<"9. Volver al menu principal"<<endl;
    cout<<"Seleccione una opcion: ";
    op=leerOpcion();
    cout<<"______________________"<<endl;


    switch (op) {
        case 1:
            cout<<"Mostrando Especies..."<<endl;
            cout<<"__________________"<<endl;
                listaEspecies.mostrarEspecie();
            break;
        case 2:
            cout<<"Mostrando Personajes..."<<endl;
            cout<<"__________________"<<endl;
                listaPersonajes.mostrarPersonaje();
            break;
        case 3:
            cout<<"Mostrando Implementos..."<<endl;
            cout<<"__________________"<<endl;
                listaImplementos.mostrarImplementos();
            break;
        case 4:
            cout<<"Mostrando Equipos..."<<endl;
            cout<<"__________________"<<endl;
                listaEquipos.mostrarEquipo();
            break;
        case 5:
            cout<<"Mostrando Mochilas..."<<endl;
            break;
        case 6:
            cout<<"Mostrando Mapas..."<<endl;
            break;
        case 7:
            cout<<"Mostrando resultados de misiones..."<<endl;
            cout<<"En construccion..."<<endl;
            cout<<"__________________"<<endl;
            break;
        case 8:
            cout<<"Mostrando bitacora..."<<endl;
            break;
        case 9:
            return;
    }
}

int main() {
    listaEspecies listaEspecies;
    listaPersonajes listaPersonajes;
    listaEquipos listaEquipos;
    listaImplementos listaImplementos;

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

    
    int op = 0;
    cout<<"\n___Bienvenido a Khazad-Dum___"<<endl;
    do {
        cout<<"____Menu de Interacciones____"<<endl;
        cout<<"1. Ver Informacion"<<endl;
        cout<<"2. Crear Elemento"<<endl;
        cout<<"3. Eliminar Elemento"<<endl;
        cout<<"4. Modificar Elemento"<<endl;
        cout<<"5. Visualizar Mapa"<<endl;
        cout<<"6. Salir"<<endl;
        cout<<"______________________"<<endl;
        cout<<"Selecciona una opcion: ";
        op=leerOpcion();

        switch (op) {
            case 1:
                verSubMenuInformacion(listaEspecies, listaPersonajes, listaEquipos, listaImplementos);
                break;
            case 2:
                verSubMenuAgregar(listaEspecies, listaPersonajes, listaEquipos, listaImplementos);
                break;
            case 3:
                verSubMenuEliminar(listaEspecies, listaPersonajes, listaEquipos, listaImplementos);
                break;
            case 4:
                verSubMenuModificar(listaEspecies, listaPersonajes, listaEquipos, listaImplementos);
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
