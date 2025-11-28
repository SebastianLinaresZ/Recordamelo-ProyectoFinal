#include <iostream>
#include "myString.h"
#include "User.h"
#include "Tarea.h"

using namespace std;

int main() {
    cout << "¡Bienvenido a Recordamelo!" << endl;

    int totalUsuarios = 0;
    User* usuarios = User::cargarUsuariosSistema(totalUsuarios);

    while (true) {
        int eleccion = seleccionarUsuario(usuarios, totalUsuarios);
        User* usuarioActual = &usuarios[eleccion];

        cout << "\nHola, " << usuarioActual->getNombre() << "." << endl;

        bool corriendo = true;
        while (corriendo) {
            cout << "\n MENU DE " << usuarioActual->getNombre() << endl;
            cout << "1. Agregar Tarea" << endl;
            cout << "2. Ver Mis Tareas" << endl;
            cout << "3. Completar Tarea" << endl;
            cout << "4. Eliminar Tarea" << endl;
            cout << "5. Modificar Tarea" << endl;
            cout << "6. Cambiar de usuario" << endl;
            cout << "7. Salir" << endl;
            cout << "Elige una opcion: ";

            int opcion;
            if (!(cin >> opcion)) {
                cin.clear(); cin.ignore(1000, '\n');
                opcion = 0;
            }

            if (opcion == 1) {
                Tarea* t = crearTarea();
                usuarioActual->agregarTareaUsuario(t);
            }
            else if (opcion == 2) {
                usuarioActual->mostrarMisTareas();
            }
            else if (opcion == 3) {
                usuarioActual->mostrarMisTareas();
                cout << "Numero de tareas para completar: ";
                int num = 0; cin >> num;
                usuarioActual->marcarTareaCompletada(num);
            }
            else if (opcion == 4) {
                usuarioActual->mostrarMisTareas();
                cout << "Numero para ELIMINAR: ";
                int num = 0; cin >> num;
                usuarioActual->eliminarTarea(num);
            }
            else if (opcion == 5) {
                usuarioActual->mostrarMisTareas();
                cout << "Numero de la tarea a modificar: ";
                int num;
                cin >> num;
                usuarioActual->modificarTarea(num);
            }
            else if (opcion == 6) {
                corriendo = false;
            }
            else if (opcion == 7) {
                cout << "Saliendo..." << endl;
                delete[] usuarios;
                return 0;
            }
        }
    }
    delete[] usuarios;
    return 0;
}
