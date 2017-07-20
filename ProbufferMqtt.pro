#-------------------------------------------------
#
# Project created by QtCreator 2016-12-29T11:31:46
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProbufferMqtt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    ConnectWidget.cpp \
    Publish.cpp \
    Sublish.cpp \
    Moni/Moni_main.cpp \
    Global_Param.cpp \
    Moni/AlarmDialog.cpp \
    Moni/BasicInfoDialog.cpp \
    Moni/RealtimeInfoDialog.cpp \
    Moni/ServiceInfoDialog.cpp \
    Protobuf/messageall.pb.cc \
    Moni/MessageDialog.cpp \
    Moni/ACPowerChargerDialog.cpp \
    Moni/LocalConfigurationDialog.cpp \
    Moni/RemoteOperationResponseDialog.cpp \
    Moni/cloud2device/RemoteOperationDialog.cpp \
    qmqtt/qmqtt_client.cpp \
    qmqtt/qmqtt_client_p.cpp \
    qmqtt/qmqtt_frame.cpp \
    qmqtt/qmqtt_message.cpp \
    qmqtt/qmqtt_message_p.cpp \
    qmqtt/qmqtt_network.cpp \
    qmqtt/qmqtt_routedmessage.cpp \
    qmqtt/qmqtt_router.cpp \
    qmqtt/qmqtt_routesubscription.cpp \
    qmqtt/qmqtt_socket.cpp \
    qmqtt/qmqtt_ssl_network.cpp \
    qmqtt/qmqtt_ssl_socket.cpp \
    qmqtt/qmqtt_timer.cpp \
    TestWidget.cpp \
    Protobuf/base64.cc
 #   Protobuf/base64.cc

HEADERS  += mainwindow.h \
    ConnectWidget.h \
    mqttform.h \
    Publish.h \
    Sublish.h \
    Moni/Moni_main.h \
    Global_Param.h \
    Moni/AlarmDialog.h \
    Moni/BasicInfoDialog.h \
    Moni/RealtimeInfoDialog.h \
    Moni/ServiceInfoDialog.h \
    Protobuf/messageall.pb.h \
    Moni/MessageDialog.h \
    Moni/ACPowerChargerDialog.h \
    Moni/LocalConfigurationDialog.h \
    Moni/RemoteOperationResponseDialog.h \
    Moni/cloud2device/RemoteOperationDialog.h \
    qmqtt/qmqtt.h \
    qmqtt/qmqtt_client.h \
    qmqtt/qmqtt_client_p.h \
    qmqtt/qmqtt_frame.h \
    qmqtt/qmqtt_global.h \
    qmqtt/qmqtt_message.h \
    qmqtt/qmqtt_message_p.h \
    qmqtt/qmqtt_network_p.h \
    qmqtt/qmqtt_networkinterface.h \
    qmqtt/qmqtt_routedmessage.h \
    qmqtt/qmqtt_router.h \
    qmqtt/qmqtt_routesubscription.h \
    qmqtt/qmqtt_socket_p.h \
    qmqtt/qmqtt_socketinterface.h \
    qmqtt/qmqtt_ssl_network_p.h \
    qmqtt/qmqtt_ssl_socket_p.h \
    qmqtt/qmqtt_timer_p.h \
    qmqtt/qmqtt_timerinterface.h \
    TestWidget.h \
    Protobuf/base64.h
  #  Protobuf/base64.h


FORMS    += mainwindow.ui \
    ConnectWidget.ui \
    Publish.ui \
    Sublish.ui \
    Moni/Moni_main.ui \
    Moni/AlarmDialog.ui \
    Moni/BasicInfoDialog.ui \
    Moni/RealtimeInfoDialog.ui \
    Moni/ServiceInfoDialog.ui \
    Moni/MessageDialog.ui \
    Moni/ACPowerChargerDialog.ui \
    Moni/LocalConfigurationDialog.ui \
    Moni/RemoteOperationResponseDialog.ui \
    Moni/cloud2device/RemoteOperationDialog.ui \
    TestWidget.ui


win32: LIBS +=  -L$$PWD/Protobuf/lib/mingw/ -lprotobuf \
                        -L$$PWD/Protobuf/lib/mingw/ -lprotoc \
                        -L$$PWD/Protobuf/lib/mingw/ -lprotobuf-lite

INCLUDEPATH += $$PWD/Protobuf/src
DEPENDPATH += $$PWD/Protobuf/src

INCLUDEPATH += $$PWD/mqtt
DEPENDPATH += $$PWD/mqtt

DISTFILES += \
    qmqtt/qmqtt_global.h~


