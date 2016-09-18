#-------------------------------------------------
#
# Project created by QtCreator 2016-04-20T12:55:49
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LSBPT
TEMPLATE = app
DESTDIR = apps

SOURCES += main.cpp\
        mainwindow.cpp \
    image.cpp\
    imageblock.cpp \
    node.cpp \
    edge.cpp \
    rag.cpp \
    edgeheap.cpp \
    statistics.cpp \
    initializer.cpp \
    histogrammodel.cpp \
    io.cpp \
    regionModel.cpp \
    compoundmodel.cpp \
    hoovermetrics.cpp \
    hoovercalculator.cpp \
    imagecropper.cpp \
    probabilitymodel.cpp \
    workingboundary.cpp \
    probabilityfilecropper.cpp

HEADERS  += mainwindow.h \
    image.h\
    imageblock.h \
    node.h \
    edge.h \
    rag.h \
    edgeheap.h \
    statistics.h \
    initializer.h \
    histogrammodel.h \
    io.h \
    regionModel.h \
    compoundmodel.h \
    hoovermetrics.h \
    hoovercalculator.h \
    imagecropper.h \
    probabilitymodel.h \
    workingboundary.h \
    probabilityfilecropper.h \
    enumerators.h

FORMS    += \
    hoovercalculator.ui \
    mainwindow.ui \
    imagecropper.ui \
    probabilityfilecropper.ui




## Add libraries

unix: {
     # use pkgconfig to find libs
    CONFIG += link_pkgconfig

    ## Add opencv
    PKGCONFIG += opencv
    ## if the pkg config is not working, add libs manualy
#    LIBS += -L/usr/lib64 -lopencv_calib3d -lopencv_contrib -lopencv_core \
#            -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui \
#            -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect \
#            -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres \
#            -lopencv_ts -lopencv_video -lopencv_videostab
#    INCLUDEPATH +=/usr/include/opencv


    ## Add gdal
    PKGCONFIG += gdal
    ## if the pkg config doesn't work for gdal, add manually
#    LIBS += -L/usr/lib64 -lgdal
#    INCLUDEPATH +=/usr/include/gdal

    # enable openmp
    QMAKE_CXXFLAGS += -fopenmp # for using parallel
    LIBS += -fopenmp


}




mac:{
CONFIG += c++11
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

LIBS += -L/Users/ytarabal/src/opencv_libs/ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs
INCLUDEPATH += /Users/ytarabal/src/opencv_include
INCLUDEPATH += /usr/local/Cellar/libiomp/20150701/include/libiomp/
INCLUDEPATH += /usr/local/Cellar/gdal/1.11.3_1/include/
LIBS += -L/usr/local/Cellar/gdal/1.11.3_1/lib -lgdal


QMAKE_CXXFLAGS += -fopenmp # for using parallel
LIBS += -fopenmp
}


