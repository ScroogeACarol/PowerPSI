#include "ApiClient.h"

ApiClient* ApiClient::m_class_object = nullptr;

void ApiClient::sendRequest(const QString &apiPath, const QVariantMap &data, const QString &httpMethod, const QString &requestId) {
    // 通用请求接口：发送 HTTP 请求到指定的 apiPath
    // 参数：
    // - apiPath: API 路径，指明请求的具体地址（例如 "/api/user"）
    // - data: 请求的 JSON 数据，默认为空 QVariantMap（适用于 GET 请求）
    // - httpMethod: 请求方法，默认为 "GET"，支持 "GET", "POST", "PUT", "DELETE"
    // - 接收一个请求 ID 作为参数，用来标识每个请求

    QUrl url = QUrl(SERVER_BASE_URL + apiPath); // 构建请求 URL

    QNetworkRequest request(url);

    QNetworkReply *reply = nullptr;

    // 根据 HTTP 方法选择相应的请求类型

    // 如果是 GET 请求，并且有传递的查询参数，则将其附加到 URL 上
    if (httpMethod == "GET" && !data.isEmpty()) {
        QUrlQuery query;
        for (auto it = data.begin(); it != data.end(); ++it) {
            query.addQueryItem(it.key(), it.value().toString());
        }
        url.setQuery(query); // 设置 URL 的查询部分
        request.setUrl(url); // 更新请求的 URL
    }

    if (httpMethod == "GET") {
        // 发送 GET 请求
        reply = m_manager->get(request);
        // qDebug() << "Raw request data: " << data;
        // qDebug() << "URL: " << request.url();
    } else if (httpMethod == "POST") {
        // 设置请求头，指定请求内容类型为 JSON
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        // 将请求数据转换为 JSON 格式，并发送 POST 请求
        QJsonDocument doc = QJsonDocument::fromVariant(data);
        QByteArray requestBody = doc.toJson();

        qDebug() << "Request body:" << requestBody;
        qDebug() << "Request URL:" << request.url();

        reply = m_manager->post(request, requestBody);

    } else if (httpMethod == "PUT") {
        // 设置请求头，指定请求内容类型为 JSON
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        // 将请求数据转换为 JSON 格式，并发送 PUT 请求
        QJsonDocument doc = QJsonDocument::fromVariant(data);
        reply = m_manager->put(request, doc.toJson());
    } else if (httpMethod == "DELETE") {
        // 发送 DELETE 请求。DELETE 请求通常没有请求体
        reply = m_manager->deleteResource(request);
    }

    // 如果无法识别的 HTTP 方法，则输出警告
    if (!reply) {
        qWarning() << "Unknown HTTP method: " << httpMethod;
    }

    // 设置请求标识符，方便响应回调时识别
    reply->setProperty("requestId", requestId);
}

void ApiClient::onRequestFinished(QNetworkReply *reply) {
    // 解析服务器返回的数据并触发 responseReceived 信号

    // 获取请求标识符
    QString requestId = reply->property("requestId").toString();
    qDebug() << "Request ID:" << requestId;

    qDebug() << "Reply data: " << reply;

    if (!reply) return;  // 如果回复为空，返回
    
    QVariantMap responseData;

    // 检查请求是否发生错误
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "HTTP Status Code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qWarning() << "Request failed with error:" << reply->errorString();
        responseData["code"] = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        responseData["message"] = reply->errorString();
        emit responseReceived(reply, responseData);  // 发出包含错误信息的信号
        reply->deleteLater();  // 删除 reply 对象
        return;
    }

    // 请求成功，解析响应数据
    QByteArray rowData = reply->readAll();
    // qDebug() << "Raw response data: " << rowData;

    // 尝试将字节数据解析为 QJsonDocument
    QJsonDocument doc = QJsonDocument::fromJson(rowData);

    if (!doc.isObject()) { // 如果解析失败，或者不是 JSON 对象，输出警告
        qWarning() << "Failed to parse JSON response!";
        responseData["code"] = 500;
        responseData["message"] = "Failed to parse JSON response!";
        emit responseReceived(reply, responseData);  // 发出包含错误信息的信号
        reply->deleteLater();  // 删除 reply 对象
    }

    responseData = doc.object().toVariantMap(); // 如果解析成功并且是一个 JSON 对象，则返回该对象的 QVariantMap 形式
    // qDebug() << "Response data: " << responseData;

    emit responseReceived(reply, responseData);  // 发出信号，传递响应数据

    reply->deleteLater();  // 删除 reply 对象
}
