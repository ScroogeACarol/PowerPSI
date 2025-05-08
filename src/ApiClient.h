#pragma once
#include "main.h"

const QString SERVER_BASE_URL = "http://localhost:3636"; // 本地服务器

class ApiClient;

class ApiClient : public QObject {
    Q_OBJECT // 使用 Qt 的信号槽机制
    public:
        ApiClient(QObject *parent = nullptr) {
            ApiClient::m_class_object = this;
            m_manager = new QNetworkAccessManager(this); // 设置网络管理器（QNetworkAccessManager
            connect(m_manager, &QNetworkAccessManager::finished, this, &ApiClient::onRequestFinished); // 当网络请求完成时，触发 onRequestFinished 槽函数
        }
        ~ApiClient() {};
        static ApiClient* m_class_object;
    public:
        Q_INVOKABLE void sendRequest(const QString &endpoint, const QVariantMap &data = {}, const QString &httpMethod = "GET", const QString &requestId="default");

    signals:
        void responseReceived(QNetworkReply *reply, const QVariantMap &responseData); // 这个信号在请求完成后发送给其他类对象

    private slots:
        void onRequestFinished(QNetworkReply *reply); // 收到响应后的处理函数

    private:
        QNetworkAccessManager *m_manager; // 网络管理器，用于发起和管理 HTTP 请求
};