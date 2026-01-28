#include "httpmgr.h"

HttpMgr::HttpMgr()
{
    //连接http请求和完成信号，信号槽机制保证队列消费
    connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)    //异步发送
{
    AsyncLog::getInstance().log(LogLevel::LogINFO, "PostHttpReq");

    QByteArray data = QJsonDocument(json).toJson();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));

    auto self = shared_from_this(); //延长HttpMgr的生命周期，在下面lamda表达式中传入self，引用计数+1，this析构后，仍存在智能指针延长生命周期

    QNetworkReply* reply = _manager.post(request, data);
    connect(reply, &QNetworkReply::finished, this, [reply, self, req_id, mod](){
        //处理错误的情况
        if(reply->error() != QNetworkReply::NoError)
        {
            AsyncLog::getInstance().log(LogLevel::LogERROR, "response error is {}", reply->error());

            //发送信号通知完成
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }

        //无错误则读回请求
        QString res = reply->readAll();

        AsyncLog::getInstance().log(LogLevel::LogINFO, "PostHttpReq Success");

        //发送信号通知完成
        emit self->sig_http_finish(req_id, res, ErrorCodes::Success, mod);
        reply->deleteLater();
        return;
    });
}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if(mod == Modules::REGISTERMOD)
    {
        //发送信号通知指定模块http响应结束
        emit sig_reg_mod_finish(id, res, err);
    }

    if(mod == Modules::RESETMOD)
    {
        AsyncLog::getInstance().log(LogLevel::LogINFO, "this is emit sig_reset_mod_finish");
        //发送信号通知指定模块http响应结束
        emit sig_reset_mod_finish(id, res, err);
    }

    if(mod == Modules::LOGINMOD)
    {
        AsyncLog::getInstance().log(LogLevel::LogINFO, "emit sig_login_mod_finish");
        emit sig_login_mod_finish(id, res, err);
    }
}
