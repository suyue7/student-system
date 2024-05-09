QT       += core gui sql charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accessbrowsedialog.cpp \
    accessgraphic.cpp \
    announcepage.cpp \
    announcepage_teacher.cpp \
    applydialog.cpp \
    applylesson.cpp \
    changepasswd.cpp \
    classtable.cpp \
    dboperator.cpp \
    editinfodialog.cpp \
    favoriteswidget_teacher.cpp \
    forgetview.cpp \
    helpwidget.cpp \
    lessoninfo.cpp \
    logindialog.cpp \
    main.cpp \
    mainpage2.cpp \
    mainwindow.cpp \
    news_ope.cpp \
    news_ope_teacher.cpp \
    queryscoregraphicsdialog.cpp \
    scorefinish.cpp \
    scoreinputdialog.cpp \
    scoreinputdialog_teacher.cpp \
    scorepic.cpp \
    sign_page.cpp \
    studentpage.cpp \
    studentwidget.cpp \
    teacherpage.cpp \
    tpersonalinfo.cpp

HEADERS += \
    DatabaseConection.h \
    accessbrowsedialog.h \
    accessgraphic.h \
    announcepage.h \
    announcepage_teacher.h \
    applydialog.h \
    applylesson.h \
    changepasswd.h \
    classtable.h \
    dboperator.h \
    editinfodialog.h \
    favoriteswidget_teacher.h \
    forgetview.h \
    helpwidget.h \
    lessoninfo.h \
    logindialog.h \
    mainpage2.h \
    mainwindow.h \
    news_ope.h \
    news_ope_teacher.h \
    queryscoregraphicsdialog.h \
    scorefinish.h \
    scoreinputdialog.h \
    scoreinputdialog_teacher.h \
    scorepic.h \
    sign_page.h \
    studentpage.h \
    studentwidget.h \
    teacherpage.h \
    tpersonalinfo.h

FORMS += \
    accessbrowsedialog.ui \
    accessgraphic.ui \
    announcepage.ui \
    announcepage_teacher.ui \
    applydialog.ui \
    applylesson.ui \
    changepasswd.ui \
    classtable.ui \
    editinfodialog.ui \
    favoriteswidget_teacher.ui \
    forgetview.ui \
    helpwidget.ui \
    lessoninfo.ui \
    logindialog.ui \
    mainpage2.ui \
    mainwindow.ui \
    news_ope.ui \
    news_ope_teacher.ui \
    queryscoregraphicsdialog.ui \
    scorefinish.ui \
    scoreinputdialog.ui \
    scoreinputdialog_teacher.ui \
    scorepic.ui \
    sign_page.ui \
    studentpage.ui \
    studentwidget.ui \
    teacherpage.ui \
    tpersonalinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    StudentSystem.pro.user

RESOURCES += \
    image.qrc
