#pragma once
#include "main.h"

class Interface;

class Interface : public QObject {
    Q_OBJECT
    public:
        Interface(QObject* parent = nullptr) {
            Interface::m_class_object = this;
            qmlRegisterSingletonType<Interface>("Class.Interface", 1, 0, "Interface",
                [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
                    Q_UNUSED(engine)
                    Q_UNUSED(scriptEngine)
                    return Interface::m_class_object;
                }
            );
        };
        ~Interface() {};
        void Init();
        static Interface* m_class_object;
    public:
        void onApiResponseReceived(QNetworkReply *reply, const QVariantMap &responseData);
    public:
        Q_INVOKABLE void m_parse_customer_and_product_from_map();
        Q_INVOKABLE void m_parse_customer_and_product_from_excel();
        Q_INVOKABLE void m_parse_psi_data_from_excel();
        Q_INVOKABLE void m_parse_so_data_from_excel();
        Q_INVOKABLE void m_parse_st_data_from_excel();
        Q_INVOKABLE void m_calculate_psi_data();
        Q_INVOKABLE void m_export_psi_data_to_excel();
        Q_INVOKABLE void m_save_psi_data();

};