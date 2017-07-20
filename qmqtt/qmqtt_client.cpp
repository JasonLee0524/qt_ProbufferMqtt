/*
 * qmqtt_client.cpp - qmqtt client
 *
 * Copyright (c) 2013  Ery Lee <ery.lee at gmail dot com>
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

#include "qmqtt_client.h"
#include "qmqtt_client_p.h"

QMQTT::Client::Client(const QHostAddress& host,
                      const quint16 port,
                      QObject* parent)
    : QObject(parent)
    , d_ptr(new ClientPrivate(this))
{
    Q_D(Client);
    d->init(host, port);
}

QMQTT::Client::Client(const QString &hostName,
                      const quint16 port,
                      const bool ssl,
                      const bool ignoreSelfSigned,
                      QObject* parent)
    : QObject(parent)
    , d_ptr(new ClientPrivate(this))
{
    Q_D(Client);
    d->init(hostName, port, ssl, ignoreSelfSigned);
}

QMQTT::Client::Client(NetworkInterface* network,
                      const QHostAddress& host,
                      const quint16 port,
                      QObject* parent)
    : QObject(parent)
    , d_ptr(new ClientPrivate(this))
{
    Q_D(Client);
    d->init(host, port, network);
}

QMQTT::Client::~Client()
{
}

QHostAddress QMQTT::Client::host() const
{
    Q_D(const Client);
    return d->host();
}

void QMQTT::Client::setHost(const QHostAddress& host)
{
    Q_D(Client);
    d->setHost(host);
}

QString QMQTT::Client::hostName() const
{
    Q_D(const Client);
    return d->hostName();
}

void QMQTT::Client::setHostName(const QString &hostName)
{
    Q_D(Client);
    d->setHostName(hostName);
}

quint16 QMQTT::Client::port() const
{
    Q_D(const Client);
    return d->port();
}

void QMQTT::Client::setPort(const quint16 port)
{
    Q_D(Client);
    d->setPort(port);
}

QString QMQTT::Client::clientId() const
{
    Q_D(const Client);
    return d->clientId();
}

void QMQTT::Client::setClientId(const QString& clientId)
{
    Q_D(Client);
    d->setClientId(clientId);
}

QString QMQTT::Client::username() const
{
    Q_D(const Client);
    return d->username();
}

void QMQTT::Client::setUsername(const QString& username)
{
    Q_D(Client);
    d->setUsername(username);
}

QString QMQTT::Client::password() const
{
    Q_D(const Client);
    return d->password();
}

void QMQTT::Client::setPassword(const QString& password)
{
    Q_D(Client);
    d->setPassword(password);
}

quint16 QMQTT::Client::keepAlive() const
{
    Q_D(const Client);
    return d->keepAlive();
}

void QMQTT::Client::setKeepAlive(const quint16 keepAlive)
{
    Q_D(Client);
    d->setKeepAlive(keepAlive);
}

bool QMQTT::Client::cleanSession() const
{
    Q_D(const Client);
    return d->cleanSession();
}

void QMQTT::Client::setCleanSession(const bool cleanSession)
{
    Q_D(Client);
    d->setCleanSession(cleanSession);
}

bool QMQTT::Client::autoReconnect() const
{
    Q_D(const Client);
    return d->autoReconnect();
}

void QMQTT::Client::setAutoReconnect(const bool value)
{
    Q_D(Client);
    d->setAutoReconnect(value);
}

int QMQTT::Client::autoReconnectInterval() const
{
    Q_D(const Client);
    return d->autoReconnectInterval();
}

void QMQTT::Client::setAutoReconnectInterval(const int autoReconnectInterval)
{
    Q_D(Client);
    d->setAutoReconnectInterval(autoReconnectInterval);
}

QString QMQTT::Client::willTopic() const
{
    Q_D(const Client);
    return d->willTopic();
}

void QMQTT::Client::setWillTopic(const QString& willTopic)
{
    Q_D(Client);
    d->setWillTopic(willTopic);
}

quint8 QMQTT::Client::willQos() const
{
    Q_D(const Client);
    return d->willQos();
}

void QMQTT::Client::setWillQos(const quint8 willQos)
{
    Q_D(Client);
    d->setWillQos(willQos);
}

bool QMQTT::Client::willRetain() const
{
    Q_D(const Client);
    return d->willRetain();
}

void QMQTT::Client::setWillRetain(const bool willRetain)
{
    Q_D(Client);
    d->setWillRetain(willRetain);
}

QString QMQTT::Client::willMessage() const
{
    Q_D(const Client);
    return d->willMessage();
}

void QMQTT::Client::setWillMessage(const QString& willMessage)
{
    Q_D(Client);
    d->setWillMessage(willMessage);
}

QMQTT::ConnectionState QMQTT::Client::connectionState() const
{
    Q_D(const Client);
    return d->connectionState();
}

bool QMQTT::Client::isConnectedToHost() const
{
    Q_D(const Client);
    return d->isConnectedToHost();
}

void QMQTT::Client::connectToHost()
{
    Q_D(Client);
    d->connectToHost();
}

void QMQTT::Client::onNetworkConnected()
{    
    Q_D(Client);
    d->onNetworkConnected();
}

quint16 QMQTT::Client::publish(const Message& message)
{
    Q_D(Client);
    return d->publish(message);
}

quint16 QMQTT::Client::subscribe(const QString& topic, const quint8 qos)
{
    Q_D(Client);
    return d->subscribe(topic, qos);
}

void QMQTT::Client::unsubscribe(const QString& topic)
{
    Q_D(Client);
    d->unsubscribe(topic);
}

void QMQTT::Client::onTimerPingReq()
{
    Q_D(Client);
    d->onTimerPingReq();
}

void QMQTT::Client::disconnectFromHost()
{
    Q_D(Client);
    d->disconnectFromHost();
}

void QMQTT::Client::onNetworkReceived(const QMQTT::Frame& frame)
{
    Q_D(Client);
    d->onNetworkReceived(frame);
}

void QMQTT::Client::onNetworkDisconnected()
{
    Q_D(Client);
    d->onNetworkDisconnected();
}

void QMQTT::Client::onNetworkError(QAbstractSocket::SocketError error)
{
    Q_D(Client);
    d->onNetworkError(error);
}
