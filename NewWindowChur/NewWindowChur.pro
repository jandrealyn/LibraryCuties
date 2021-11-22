QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SystemFiles.cpp \
    adminaddbook.cpp \
    admincatalogue.cpp \
    admindue.cpp \
    admineditbook.cpp \
    adminedituser.cpp \
    adminhome.cpp \
    adminoverdue.cpp \
    adminsystem.cpp \
    adminuser.cpp \
    catalogue.cpp \
    checkoutscreen.cpp \
    dialog.cpp \
    loginscreen.cpp \
    main.cpp \
    mainwindow.cpp \
    overdue.cpp \
    reservebook.cpp \
    signupscreen.cpp \
    signupscreen2.cpp \
    updateuserdetails.cpp \
    updateuserpicture.cpp

HEADERS += \
    SystemFiles.h \
    adminaddbook.h \
    admincatalogue.h \
    admindue.h \
    admineditbook.h \
    adminedituser.h \
    adminhome.h \
    adminoverdue.h \
    adminsystem.h \
    adminuser.h \
    catalogue.h \
    checkoutscreen.h \
    dialog.h \
    loginscreen.h \
    mainwindow.h \
    overdue.h \
    reservebook.h \
    signupscreen.h \
    signupscreen2.h \
    updateuserdetails.h \
    updateuserpicture.h

FORMS += \
    adminaddbook.ui \
    admincatalogue.ui \
    admindue.ui \
    admineditbook.ui \
    adminedituser.ui \
    adminhome.ui \
    adminoverdue.ui \
    adminsystem.ui \
    adminuser.ui \
    catalogue.ui \
    checkoutscreen.ui \
    dialog.ui \
    loginscreen.ui \
    mainwindow.ui \
    overdue.ui \
    reservebook.ui \
    signupscreen.ui \
    signupscreen2.ui \
    updateuserdetails.ui \
    updateuserpicture.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    images/top-books.png \
    umlclassdiagrams.qmodel
