#pragma once
#include <QGuiApplication> /* GUI 应用程序 */
class QGuiApplication;
#include <QQmlApplicationEngine> /* QML引擎 */
class QQmlApplicationEngine;
#include <QQmlComponent> /* 在C++创建Qml实体时用到 */
class QQmlComponent;
#include <QObject> /* 在C++层创建Qt对象 */
class QObject;
#include <QDebug> /* 调试打印 */
class QDebug;
#include <QDir> /* main.cpp中打印qrc层级时用到 */
class QDir;
#include <QTimer> /* 定时器 */
class QTimer;
#include <QJsonDocument> /* 用于处理JSON数据 */
class QJsonDocument;
#include <QJsonObject> /* 用于获取QJsonDocument类中的对象并使用对象方法 */
class QJsonObject;
#include <QAxObject> /* 用于操作Excel */
class QAxObject;
#include <QFileDialog> /* 用于打开文件对话框 */
class QFileDialog;

#include <QNetworkAccessManager>  // 处理网络请求的类
class QNetworkAccessManager;
#include <QNetworkReply>          // 处理响应数据的类
class QNetworkReply;
#include <QNetworkRequest>        // 定义网络请求（URL、请求头等）的类
class QNetworkRequest;
#include <QUrlQuery>              // 用于便捷地在 URL 中拼接 GET 方法的参数
class QUrlQuery;

class QtCommonClass;

class QtCommonClass {
    public:
        QtCommonClass() {
            this->m_class_object = this;
        };
        ~QtCommonClass() {
            this->m_class_object = nullptr;
        };
        static QtCommonClass* m_class_object;
    public:
        // QQmlEngine engine; // 是QQmlApplicationEngine的父类
        QQmlApplicationEngine engine; // 会自动清理和删除在QML文件中创建的对象
};