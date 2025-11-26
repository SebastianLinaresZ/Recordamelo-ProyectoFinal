#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>

int miStrLen(const char* str);
void miStrCopiar(char* dest, const char* src);
void miStrConcatenar(char* dest, const char* src);

class MyString {
private:
    char* data;

public:

    MyString();
    MyString(const char* str);

    // Regla de 3
    MyString(const MyString& other); //culona
    MyString& operator=(const MyString& other); //asigna
    MyString& operator=(const char* str); //asinga el caracter
    ~MyString(); //destruye

    const char* c_str() const;
};

#endif
