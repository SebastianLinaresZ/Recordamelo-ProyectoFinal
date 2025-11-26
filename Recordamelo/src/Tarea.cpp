#include "Tarea.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Tarea::Tarea() {
    titulo = " "; descripcion = " "; fechaLimite = time(0);
    tipo = "Generica"; prioridad = 3; completada = false;
}

Tarea::Tarea(const char* tit, const char* desc, time_t fecha, const char* tip, int prio) {
    titulo = tit; descripcion = desc; fechaLimite = fecha;
    tipo = tip; prioridad = prio; completada = false;
}

//gets
const char* Tarea::getTitulo() const {
    return titulo.c_str();
    }

const char* Tarea::getDescripcion() const {
    return descripcion.c_str();
    }

const char* Tarea::getTipo() const {
    return tipo.c_str();
    }

time_t Tarea::getFechaLimite() const {
    return fechaLimite;
    }

int Tarea::getPrioridad() const {
    return prioridad;
    }

bool Tarea::isCompletada() const {
    return completada;
}

void Tarea::setCompletada(bool estado) {
    completada = estado;
}

Tarea* Tarea::clone() const {
    return new Tarea(*this);
    }

void Tarea::guardar(std::ofstream& ofs) const {
    ofs << titulo.c_str() << "|"
        << descripcion.c_str() << "|"
        << (long long)fechaLimite << "|"
        << tipo.c_str() << "|"
        << prioridad << "|"
        << (completada ? "1" : "0");
}

void Tarea::cargarExtra(std::ifstream& ifs) {}

void Tarea::mostrarDetalles() const {}

const char* Tarea::obtenerPrioridadTexto() const {
    if (prioridad == 1) return "ALTA";
    if (prioridad == 2) return "MEDIA";
    return "BAJA";
}

void Tarea::obtenerFechaFormateada(char* buffer) const {
    struct tm* infoTiempo = localtime(&fechaLimite);
    sprintf(buffer, "%02d/%02d/%04d", infoTiempo->tm_mday, infoTiempo->tm_mon + 1, infoTiempo->tm_year + 1900);
}


//hogar
TareaHogar::TareaHogar() : Tarea() { habitacion = "Casa"; }

TareaHogar::TareaHogar(const char* tit, const char* desc, time_t fecha, int prio, const char* hab)
    : Tarea(tit, desc, fecha, "Hogar", prio) {
    habitacion = hab;
}

Tarea* TareaHogar::clone() const { return new TareaHogar(*this); }

void TareaHogar::guardar(std::ofstream& ofs) const {
    Tarea::guardar(ofs);
    ofs << "|" << habitacion.c_str();
}

void TareaHogar::cargarExtra(std::ifstream& ifs) {
    char buffer[100];
    ifs.getline(buffer, 100, '\n');
    if (buffer[0] == '|') habitacion = buffer + 1;
    else habitacion = buffer;
}

void TareaHogar::mostrarDetalles() const {
    cout << "[Hogar] Habitacion: " << habitacion.c_str() << endl;
}


//universidad
TareaUniversidad::TareaUniversidad() : Tarea() { materia = "General"; }

TareaUniversidad::TareaUniversidad(const char* tit, const char* desc, time_t fecha, int prio, const char* mat)
    : Tarea(tit, desc, fecha, "Universidad", prio) {
    materia = mat;
}

Tarea* TareaUniversidad::clone() const { return new TareaUniversidad(*this); }

void TareaUniversidad::guardar(std::ofstream& ofs) const {
    Tarea::guardar(ofs);
    ofs << "|" << materia.c_str();
}

void TareaUniversidad::cargarExtra(std::ifstream& ifs) {
    char buffer[100];
    ifs.getline(buffer, 100, '\n');
    if (buffer[0] == '|')
        materia = buffer + 1;
    else
        materia = buffer;
}

void TareaUniversidad::mostrarDetalles() const {
    cout << "  [Universidad] Materia: " << materia.c_str() << endl;
}

//Ocio
TareaOcio::TareaOcio() : Tarea() { lugar = " "; }

TareaOcio::TareaOcio(const char* tit, const char* desc, time_t fecha, int prio, const char* lug)
    : Tarea(tit, desc, fecha, "Ocio", prio) {
    lugar = lug;
}

Tarea* TareaOcio::clone() const { return new TareaOcio(*this); }

void TareaOcio::guardar(std::ofstream& ofs) const {
    Tarea::guardar(ofs);
    ofs << "|" << lugar.c_str();
}

void TareaOcio::cargarExtra(std::ifstream& ifs) {
    char buffer[100];
    ifs.getline(buffer, 100, '\n');
    if (buffer[0] == '|') lugar = buffer + 1;
    else lugar = buffer;
}

void TareaOcio::mostrarDetalles() const {
    cout << "  [Ocio] Lugar: " << lugar.c_str() << endl;
}


Tarea* crearTareaPolimorfica() {
    char tit[100], desc[200], extra[100];
    int dia, mes, prio, opcionTipo;

    time_t t_now = time(0);
    struct tm* now = localtime(&t_now);
    int anioActual = now->tm_year + 1900;

    cout << "\n--- TIPO DE TAREA ---" << endl;
    cout << "1. Universidad (Materia)" << endl;
    cout << "2. Hogar (Habitacion)" << endl;
    cout << "3. Ocio (Lugar)" << endl;
    cout << "Elige: "; cin >> opcionTipo;
    cin.ignore(1000, '\n');

    cout << "Titulo: "; cin.getline(tit, 100);
    cout << "Descripcion: "; cin.getline(desc, 200);
    cout << "Fecha Limite (Dia Mes, ej: 25 12): "; cin >> dia >> mes;
    cin.ignore(1000, '\n');
    cout << "Prioridad (1-3): "; cin >> prio;
    cin.ignore(1000, '\n');

    struct tm t = {0};
    t.tm_year = anioActual - 1900; t.tm_mon = mes - 1; t.tm_mday = dia;
    time_t fecha = mktime(&t);

    if (opcionTipo == 1) {
        cout << "Materia: "; cin.getline(extra, 100);
        return new TareaUniversidad(tit, desc, fecha, prio, extra);
    }
    else if (opcionTipo == 2) {
        cout << "Habitacion: "; cin.getline(extra, 100);
        return new TareaHogar(tit, desc, fecha, prio, extra);
    }
    else {
        cout << "Lugar/Actividad: "; cin.getline(extra, 100);
        return new TareaOcio(tit, desc, fecha, prio, extra);
    }
}
