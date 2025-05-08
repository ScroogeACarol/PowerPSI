#include "MenuBar.h"

MenuBar* MenuBar::m_class_object = nullptr;

MenuBar::MenuBar() {
    qDebug() << "MenuBar::MenuBar()";
    this->m_class_object = this;
    { /* MenuBar.qml */
        QQmlComponent component(&(QtCommonClass::m_class_object->engine), QUrl(QStringLiteral("qrc:/qml/MenuBar.qml")));
        if (component.status() != QQmlComponent::Status::Ready) {
            qDebug() << component.status() << component.errorString();
            return;
        }
        this->m_qml_object = component.create();
        if (! this->m_qml_object) {
            qDebug() << "MenuBar::MenuBar() failed";
            return;
        }
    }
};

MenuBar::~MenuBar() {
    qDebug() << "MenuBar::~MenuBar()";
};