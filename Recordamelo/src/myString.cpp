#include "myString.h"

int miStrLen(const char* str) {
    if (!str) return 0;
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void miStrCopiar(char* dest, const char* src) {
    if (!dest || !src) return;
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

bool sonIguales(const char* a, const char* b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return (a[i] == '\0' && b[i] == '\0');
}

void miStrConcatenar(char* dest, const char* src) {
    if (!dest || !src) return;
    int len = miStrLen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[len + i] = src[i];
        i++;
    }
    dest[len + i] = '\0';
}

MyString::MyString() {
    data = new char[1];
    data[0] = '\0';
}

MyString::MyString(const char* str) {
    if (str) {
        int len = miStrLen(str);
        data = new char[len + 1];
        miStrCopiar(data, str);
    } else {
        data = new char[1];
        data[0] = '\0';
    }
}

MyString::MyString(const MyString& other) {
    int len = miStrLen(other.data);
    data = new char[len + 1];
    miStrCopiar(data, other.data);
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data;
        int len = miStrLen(other.data);
        data = new char[len + 1];
        miStrCopiar(data, other.data);
    }
    return *this;
}

MyString& MyString::operator=(const char* str) {
    if (data) delete[] data;
    if (str) {
        int len = miStrLen(str);
        data = new char[len + 1];
        miStrCopiar(data, str);
    } else {
        data = new char[1];
        data[0] = '\0';
    }
    return *this;
}

MyString::~MyString() {
    delete[] data;
}

const char* MyString::c_str() const {
    return data;
}
