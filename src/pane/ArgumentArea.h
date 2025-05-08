#pragma once
#include "main.h"

class ArgumentArea;

class ArgumentArea {
    public:
        ArgumentArea();
        ~ArgumentArea();
        static ArgumentArea* m_class_object;
    public:
        QObject* m_qml_object = nullptr;
};