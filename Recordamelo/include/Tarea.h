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

public:
    Tarea();
    Tarea(const char* tit, const char* desc, time_t fecha, const char* tip, int prio);

    virtual ~Tarea() {}

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
};

Tarea* crearTareaPolimorfica();

#endif
