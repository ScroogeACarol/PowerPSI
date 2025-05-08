#pragma once
#include "main.h"

class TimeAxisArea;

class TimeAxisArea {
    public:
        TimeAxisArea();
        ~TimeAxisArea();
        static TimeAxisArea* m_class_object;
    public:
        QObject* m_qml_object = nullptr;
};