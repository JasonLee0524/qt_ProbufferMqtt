/*
 * qmqtt_ssl_socket.cpp - qmqtt SSL socket
 *
 * Copyright (c) 2013  Ery Lee <ery.lee at gmail dot com>
 * Copyright (c) 2016  Matthias Dieter Wallnöfer
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of mqttc nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "qmqtt_ssl_socket_p.h"
#include <QSslSocket>
#include <QSslConfiguration>
#include <QSslCertificate>
#include <QSslKey>

#ifndef QT_NO_SSL

QMQTT::SslSocket::SslSocket(bool ignoreSelfSigned, QObject* parent)
    : SocketInterface(parent)
    , _socket(new QSslSocket)
    , _ignoreSelfSigned(ignoreSelfSigned)
{
    connect(_socket.data(), &QSslSocket::encrypted,    this, &SocketInterface::connected);
    connect(_socket.data(), &QSslSocket::disconnected, this, &SocketInterface::disconnected);
    connect(_socket.data(),
            static_cast<void (QSslSocket::*)(QAbstractSocket::SocketError)>(&QSslSocket::error),
            this,
            static_cast<void (SocketInterface::*)(QAbstractSocket::SocketError)>(&SocketInterface::error));
    connect(_socket.data(),
            static_cast<void (QSslSocket::*)(const QList<QSslError>&)>(&QSslSocket::sslErrors),
            this,
            &SslSocket::sslErrors);
}

QMQTT::SslSocket::~SslSocket()
{
}

QIODevice *QMQTT::SslSocket::ioDevice()
{
    return _socket.data();
}

void QMQTT::SslSocket::connectToHost(const QHostAddress& address, quint16 port)
{
    Q_UNUSED(address);
    Q_UNUSED(port);

    qCritical("qmqtt: SSL does not work with host addresses!");
    emit _socket->error(QAbstractSocket::ConnectionRefusedError);
}

//put the crt and key file into application running directory
//todo:set file path on instance if necessary
void QMQTT::SslSocket::connectToHost(const QString& hostName, quint16 port)
{
    QSslConfiguration sslConf = _socket.data()->sslConfiguration();
    sslConf.setLocalCertificate(QSslCertificate::fromPath(QStringLiteral("./cert.crt")).first());   //LocalCertificate
    _socket.data()->setSslConfiguration(sslConf);
    _socket.data()->setPrivateKey(QStringLiteral("./cert.key"));                    //LocalPrivateKey
    _socket->connectToHostEncrypted(hostName, port);
    _socket.data()->setPeerVerifyMode(QSslSocket::VerifyNone);                      //important

    if (!_socket->waitForEncrypted())
    {
        qCritical() << QStringLiteral("qmqtt SSL: ") << _socket->errorString();
    }
}

void QMQTT::SslSocket::disconnectFromHost()
{
    _socket->disconnectFromHost();
}

QAbstractSocket::SocketState QMQTT::SslSocket::state() const
{
    return _socket->state();
}

QAbstractSocket::SocketError QMQTT::SslSocket::error() const
{
    return _socket->error();
}

void QMQTT::SslSocket::sslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors);

    if (_ignoreSelfSigned)
    {
        // allow self-signed certificates
        _socket->ignoreSslErrors();
    }
}

#endif // QT_NO_SSL
