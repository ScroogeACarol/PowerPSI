#pragma once
#include "main.h"

class EditableArea;

class EditableArea {
    public:
        EditableArea();
        ~EditableArea();
        static EditableArea* m_class_object;
    public:
        QObject* m_qml_object = nullptr;
};