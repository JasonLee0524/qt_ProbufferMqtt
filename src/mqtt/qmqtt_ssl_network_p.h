/*
 * qmqtt_ssl_network_p.h - qmqtt SSL network private header
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
#ifndef QMQTT_SSL_NETWORK_P_H
#define QMQTT_SSL_NETWORK_P_H

#include "qmqtt_networkinterface.h"
#include "qmqtt_frame.h"
#include <QByteArray>
#include <QObject>
#include <QTcpSocket>
#include <QPointer>
#include <QByteArray>
#include <QHostAddress>

#ifndef QT_NO_SSL

namespace QMQTT {

class SocketInterface;
class TimerInterface;

class SslNetwork : public NetworkInterface
{
    Q_OBJECT

public:
    SslNetwork(bool ignoreSelfSigned, QObject* parent = NULL);
    SslNetwork(SocketInterface* socketInterface, TimerInterface* timerInterface,
            QObject* parent = NULL);
    ~SslNetwork();

    void sendFrame(Frame& frame);
    bool isConnectedToHost() const;
    bool autoReconnect() const;
    void setAutoReconnect(const bool autoReconnect);
    QAbstractSocket::SocketState state() const;
    int autoReconnectInterval() const;
    void setAutoReconnectInterval(const int autoReconnectInterval);

public slots:
    void connectToHost(const QHostAddress& host, const quint16 port);
    void connectToHost(const QString& hostName, const quint16 port);
    void disconnectFromHost();

protected slots:
    void onSocketError(QAbstractSocket::SocketError socketError);

protected:
    void initialize();
    int readRemainingLength();

    quint16 _port;
    QString _hostName;
    QByteArray _buffer;
    bool _autoReconnect;
    int _autoReconnectInterval;
    int _bytesRemaining;
    quint8 _header;
    SocketInterface* _socket;
    TimerInterface* _autoReconnectTimer;

protected slots:
    void onSocketReadReady();
    void onDisconnected();
    void connectToHost();

private:
    Q_DISABLE_COPY(SslNetwork)
};

} // namespace QMQTT

#endif // QT_NO_SSL

#endif // QMQTT_SSL_NETWORK_P_H
