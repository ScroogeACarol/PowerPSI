#include "ArgumentArea.h"

ArgumentArea* ArgumentArea::m_class_object = nullptr;

ArgumentArea::ArgumentArea() {
    qDebug() << "ArgumentArea::ArgumentArea()";
    this->m_class_object = this;
    { /* ArgumentArea.qml */
        QQmlComponent component(&(QtCommonClass::m_class_object->engine), QUrl(QStringLiteral("qrc:/qml/ArgumentArea.qml")));
        if (component.status() != QQmlComponent::Status::Ready) {
            qDebug() << component.status() << component.errorString();
            return;
        }
        this->m_qml_object = component.create();
        if (! this->m_qml_object) {
            qDebug() << "ArgumentArea::ArgumentArea() failed";
            return;
        }
    }
};

ArgumentArea::~ArgumentArea() {
    qDebug() << "ArgumentArea::~ArgumentArea()";
};