#include "User.h"
#include "myString.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// Constructores
User::User() {
    nombre = "Invitado"; numTareas = 0; capacidad = 2;
    listaTareas = new Tarea*[capacidad];
}

User::User(const char* nom) {
    nombre = nom; numTareas = 0; capacidad = 2;
    listaTareas = new Tarea*[capacidad];

    char buffer[100];
    miStrCopiar(buffer, nom);
    miStrConcatenar(buffer, ".txt");
    archivoTareas = buffer;

    cargarTareas();
}

User::User(const User& other) {
    nombre = other.nombre; archivoTareas = other.archivoTareas;
    numTareas = other.numTareas; capacidad = other.capacidad;
    listaTareas = new Tarea*[capacidad];
    for(int i = 0; i < numTareas; i++) {
        listaTareas[i] = other.listaTareas[i]->clone();
    }
}

User& User::operator=(const User& other) {
    if (this != &other) {
        for(int i = 0; i < numTareas; i++) delete listaTareas[i];
        delete[] listaTareas;

        nombre = other.nombre; archivoTareas = other.archivoTareas;
        numTareas = other.numTareas; capacidad = other.capacidad;

        listaTareas = new Tarea*[capacidad];
        for(int i = 0; i < numTareas; i++) {
            listaTareas[i] = other.listaTareas[i]->clone();
        }
    }
    return *this;
}

User::~User() {
    for(int i = 0; i < numTareas; i++) delete listaTareas[i];
    delete[] listaTareas;
}

User* User::cargarUsuariosSistema(int& total) {
    total = 3;
    User* lista = new User[total];
    lista[0] = User("Derek");
    lista[1] = User("Sebastian");
    lista[2] = User("Rocio");
    return lista;
}

const char* User::getNombre() const { return nombre.c_str(); }

void User::redimensionar() {
    int nuevaCapacidad = (capacidad == 0) ? 2 : capacidad * 2;
    Tarea** nuevaLista = new Tarea*[nuevaCapacidad];
    for (int i = 0; i < numTareas; ++i) {
        nuevaLista[i] = listaTareas[i];
    }
    delete[] listaTareas;
    listaTareas = nuevaLista;
    capacidad = nuevaCapacidad;
}

void User::agregarTareaUsuario(Tarea* nuevaTarea) {
    if (numTareas == capacidad) redimensionar();
    listaTareas[numTareas] = nuevaTarea;
    numTareas++;
    guardarTareas();
}

int seleccionarUsuario(User usuarios[], int total) {
    cout << "\n--- SELECCIONAR USUARIO ---" << endl;
    for (int i = 0; i < total; i++) {
        cout << i + 1 << ". " << usuarios[i].getNombre() << endl;
    }
    cout << "Elige: ";
    int opcion;
    cin >> opcion;
    if (opcion < 1 || opcion > total) return 0;
    return opcion - 1;
}

void User::mostrarMisTareas() const {
    cout << "\n--- TAREAS DE " << nombre.c_str() << " ---" << endl;
    if (numTareas == 0) {
        cout << "No tienes tareas registradas." << endl;
        return;
    }
    time_t ahora = time(0); // Hora actual

    for (int i = 0; i < numTareas; ++i) {
        const char* estadoVisual = listaTareas[i]->isCompletada() ? "[X]" : "[ ]";

        char fechaTxt[50];
        listaTareas[i]->obtenerFechaFormateada(fechaTxt);

        // Calcula la diferencia en segundos
        double segundosDiff = difftime(listaTareas[i]->getFechaLimite(), ahora);

        // Convierte a dias (segundos / 60*60*24)
        // 86400 son los segundos en un dia
        int diasFaltan = (int)(segundosDiff / 86400);

        // Verifica si ya pasó el tiempo
        bool vencida = (!listaTareas[i]->isCompletada() && segundosDiff < 0);

        cout << "Tarea " << i + 1 << " " << estadoVisual
             << " [" << listaTareas[i]->getTipo() << "] "
             << listaTareas[i]->getTitulo();

        // Muestra el mensaje segun los dias
        if (vencida) {
            cout << " <!SE TE PASO EL TREN ARAÑA!>";
        } else if (!listaTareas[i]->isCompletada()) {
            if (diasFaltan == 0) cout << " (La fecha limite es hoy)";
            else if (diasFaltan > 0) cout << " (Todavia te faltan " << diasFaltan << " dias)";
        }

        cout << endl;

        cout << "      Desc: " << listaTareas[i]->getDescripcion()
             << " | Limite: " << fechaTxt << endl;

        listaTareas[i]->mostrarDetalles();
    }
}

void User::marcarTareaCompletada(int indiceUsuario) {
    int indiceReal = indiceUsuario - 1;
    if (indiceReal >= 0 && indiceReal < numTareas) {
        listaTareas[indiceReal]->setCompletada(true);
        cout << "Tarea completada." << endl;
        guardarTareas();
    } else cout << "Indice no valido." << endl;
}

void User::eliminarTarea(int indiceUsuario) {
    int indiceReal = indiceUsuario - 1;
    if (indiceReal >= 0 && indiceReal < numTareas) {
        delete listaTareas[indiceReal];
        for (int i = indiceReal; i < numTareas - 1; i++) {
            listaTareas[i] = listaTareas[i + 1];
        }
        numTareas--;
        guardarTareas();
        cout << "Tarea eliminada." << endl;
    } else cout << "Indice no valido." << endl;
}

void User::guardarTareas() const {
    ofstream ofs(archivoTareas.c_str());
    if (!ofs.is_open()) return;
    ofs << numTareas << endl;
    for (int i = 0; i < numTareas; ++i) {
        listaTareas[i]->guardar(ofs);
        ofs << endl;
    }
    ofs.close();
}

void User::cargarTareas() {
    ifstream ifs(archivoTareas.c_str());
    if (!ifs.is_open()) return;

    int total=0;
    ifs >> total;
    ifs.ignore(1000, '\n');

    while (total > capacidad) redimensionar();

    char buffer[300];
    char tipoStr[50];

    for (int i = 0; i < total; ++i) {
        ifs.getline(buffer, 300, '|'); MyString tit = buffer;
        ifs.getline(buffer, 300, '|'); MyString desc = buffer;
        ifs.getline(buffer, 300, '|'); time_t fecha = (time_t)atol(buffer);
        ifs.getline(buffer, 300, '|'); miStrCopiar(tipoStr, buffer);
        ifs.getline(buffer, 300, '|'); int prio = atoi(buffer);

        string tempDone;
        char c;
        while(ifs.get(c)) {
            if(c == '|' || c == '\n') break;
            tempDone += c;
        }
        bool done = (tempDone == "1");

        Tarea* nueva = nullptr;
        if (strcmp(tipoStr, "Universidad") == 0) {
            nueva = new TareaUniversidad(tit.c_str(), desc.c_str(), fecha, prio, "");
        } else if (strcmp(tipoStr, "Hogar") == 0) {
            nueva = new TareaHogar(tit.c_str(), desc.c_str(), fecha, prio, "");
        } else {
            nueva = new TareaOcio(tit.c_str(), desc.c_str(), fecha, prio, "");
        }

        nueva->setCompletada(done);

        if (c == '|') nueva->cargarExtra(ifs);

        listaTareas[i] = nueva;
    }
    numTareas = total;
    ifs.close();
}
