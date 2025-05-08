#pragma once
#include "main.h"

class MainWnd;

class MainWnd {
    public:
        MainWnd();
        ~MainWnd();
        static MainWnd* m_class_object;
    public:
        QObject* m_qml_object = nullptr;
};