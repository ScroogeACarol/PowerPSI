#include "EditableArea.h"

EditableArea* EditableArea::m_class_object = nullptr;

EditableArea::EditableArea() {
    qDebug() << "EditableArea::EditableArea()";
    this->m_class_object = this;
    { /* EditableArea.qml */
        QQmlComponent component(&(QtCommonClass::m_class_object->engine), QUrl(QStringLiteral("qrc:/qml/EditableArea.qml")));
        if (component.status() != QQmlComponent::Status::Ready) {
            qDebug() << component.status() << component.errorString();
            return;
        }
        this->m_qml_object = component.create();
        if (! this->m_qml_object) {
            qDebug() << "EditableArea::EditableArea() failed";
            return;
        }
    }
};

EditableArea::~EditableArea() {
    qDebug() << "EditableArea::~EditableArea()";
};