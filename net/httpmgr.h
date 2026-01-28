/******************************************************************************
 *
 * @file       httpmgr.h
 * @brief      HTTP管理类
 *
 * @author     ysk
 * @date       2025/12/30
 * @history
 *****************************************************************************/

#ifndef HTTPMGR_H
#define HTTPMGR_H

#include "tool/singleton.h"

class HttpMgr : public QObject, public Singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr> {
    Q_OBJECT
private:
    friend class Singleton<HttpMgr>;
    HttpMgr();

public:
    ~HttpMgr() = default;

    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);

private:    //成员变量
    QNetworkAccessManager _manager;

signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);   //sig_http_finish->slot_http_finish,根据mod选择发送不同的信号

    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_reset_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_login_mod_finish(ReqId id, QString res, ErrorCodes err);

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

};

#endif // HTTPMGR_H
