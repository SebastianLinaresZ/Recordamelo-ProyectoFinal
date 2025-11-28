#ifndef TAREA_H
#define TAREA_H
#include "myString.h"
#include <fstream>
#include <ctime>

//padre
class Tarea {
protected:
    MyString titulo;
    MyString descripcion;
    time_t fechaLimite;
    MyString tipo;
    int prioridad;
    bool completada;

    MyString* subDescripciones;
    bool* subEstados;
    int numSubtareas;
    int capSubtareas;

    void redimensionarSubtareas();

public:
    Tarea();
    Tarea(const char* tit, const char* desc, time_t fecha, const char* tip, int prio);

    virtual ~Tarea();

    const char* getTitulo() const;
    const char* getDescripcion() const;
    const char* getTipo() const;
    time_t getFechaLimite() const;
    int getPrioridad() const;
    bool isCompletada() const;
    void setCompletada(bool estado);

    virtual Tarea* clone() const;
    virtual void guardar(std::ofstream& ofs) const;
    virtual void cargarExtra(std::ifstream& ifs);
    virtual void mostrarDetalles() const;

    const char* obtenerPrioridadTexto() const;
    void obtenerFechaFormateada(char* buffer) const;

    void setTitulo(const MyString& t) { titulo = t; }
    void setDescripcion(const MyString& d) { descripcion = d; }  // porque los atributos son protected
    void setFechaLimite(time_t f) { fechaLimite = f; }
    void setPrioridad(int p) { prioridad = p; }

    void agregarSubtarea(const char* desc);
    void mostrarSubtareas() const;

};

//hijas
class TareaHogar : public Tarea {
private:
    MyString habitacion;

public:
    TareaHogar();
    TareaHogar(const char* tit, const char* desc, time_t fecha, int prio, const char* hab);

    Tarea* clone() const override;
    void guardar(std::ofstream& ofs) const override;
    void cargarExtra(std::ifstream& ifs) override;
    void mostrarDetalles() const override;

    MyString getHabitacion() const { return habitacion; }
    void setHabitacion(const MyString& h) { habitacion = h; } //porq es privado

};

class TareaUniversidad : public Tarea {
private:
    MyString materia;

public:
    TareaUniversidad();
    TareaUniversidad(const char* tit, const char* desc, time_t fecha, int prio, const char* mat);

    Tarea* clone() const override;
    void guardar(std::ofstream& ofs) const override;
    void cargarExtra(std::ifstream& ifs) override;
    void mostrarDetalles() const override;

    MyString getMateria() const { return materia; }
    void setMateria(const MyString& m) { materia = m; } //porq es privado

};

class TareaOcio : public Tarea {
private:
    MyString lugar;

public:
    TareaOcio();
    TareaOcio(const char* tit, const char* desc, time_t fecha, int prio, const char* lug);

    Tarea* clone() const override;
    void guardar(std::ofstream& ofs) const override;
    void cargarExtra(std::ifstream& ifs) override;
    void mostrarDetalles() const override;

    MyString getlugar() const { return lugar; }
    void setLugar(const MyString& l) { lugar = l; } //porq es privado

};

Tarea* crearTarea();

#endif
