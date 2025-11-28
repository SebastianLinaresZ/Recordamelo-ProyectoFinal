#ifndef USER_H
#define USER_H

#include "myString.h"
#include "Tarea.h"

class User {
private:
    MyString nombre;
    MyString archivoTareas;
    Tarea** listaTareas;
    int numTareas;
    int capacidad;

    void redimensionar();
    void guardarTareas() const;
    void cargarTareas();

public:
    User();
    User(const char* nombre);

    // Regla de 3
    User(const User& other); //clona
    User& operator=(const User& other); //asigna
    ~User(); //destruye

    const char* getNombre() const;

    void agregarTareaUsuario(Tarea* nuevaTarea);
    void mostrarMisTareas() const;
    void marcarTareaCompletada(int indiceUsuario);
    void eliminarTarea(int indiceUsuario);
    void agregarSubtareaATarea(int indiceUsuario, const char* descSubtarea);

    static User* cargarUsuariosSistema(int& total);
    //nuevo metodo
    void modificarTarea(int indiceUsuario);
};

int seleccionarUsuario(User usuarios[], int total);


#endif
