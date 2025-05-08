#pragma once
#include "main.h"

class MenuBar;

class MenuBar {
    public:
        MenuBar();
        ~MenuBar();
        static MenuBar* m_class_object;
    public:
        QObject* m_qml_object = nullptr;
};