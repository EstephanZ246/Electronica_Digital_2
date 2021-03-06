# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui/main_gui.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(519, 456)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("ui\\../assets/icon.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        MainWindow.setWindowIcon(icon)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout()
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.lvPorts = QtWidgets.QListWidget(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lvPorts.sizePolicy().hasHeightForWidth())
        self.lvPorts.setSizePolicy(sizePolicy)
        self.lvPorts.setMinimumSize(QtCore.QSize(0, 150))
        self.lvPorts.setMaximumSize(QtCore.QSize(16777215, 150))
        self.lvPorts.setObjectName("lvPorts")
        self.verticalLayout.addWidget(self.lvPorts)
        spacerItem = QtWidgets.QSpacerItem(20, 15, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        self.verticalLayout.addItem(spacerItem)
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.btnSearch = QtWidgets.QPushButton(self.centralwidget)
        self.btnSearch.setMinimumSize(QtCore.QSize(0, 30))
        self.btnSearch.setObjectName("btnSearch")
        self.horizontalLayout.addWidget(self.btnSearch)
        self.btnConnect = QtWidgets.QPushButton(self.centralwidget)
        self.btnConnect.setMinimumSize(QtCore.QSize(0, 30))
        self.btnConnect.setObjectName("btnConnect")
        self.horizontalLayout.addWidget(self.btnConnect)
        self.btnDisconnect = QtWidgets.QPushButton(self.centralwidget)
        self.btnDisconnect.setMinimumSize(QtCore.QSize(0, 30))
        self.btnDisconnect.setObjectName("btnDisconnect")
        self.horizontalLayout.addWidget(self.btnDisconnect)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.verticalLayout_3.addLayout(self.verticalLayout)
        spacerItem1 = QtWidgets.QSpacerItem(20, 20, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        self.verticalLayout_3.addItem(spacerItem1)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout()
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        spacerItem2 = QtWidgets.QSpacerItem(10, 20, QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem2)
        self.txtContador = QtWidgets.QLineEdit(self.centralwidget)
        self.txtContador.setMinimumSize(QtCore.QSize(0, 30))
        self.txtContador.setObjectName("txtContador")
        self.horizontalLayout_2.addWidget(self.txtContador)
        spacerItem3 = QtWidgets.QSpacerItem(5, 20, QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem3)
        self.btnSend = QtWidgets.QPushButton(self.centralwidget)
        self.btnSend.setMinimumSize(QtCore.QSize(0, 30))
        self.btnSend.setObjectName("btnSend")
        self.horizontalLayout_2.addWidget(self.btnSend)
        spacerItem4 = QtWidgets.QSpacerItem(10, 20, QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem4)
        self.verticalLayout_2.addLayout(self.horizontalLayout_2)
        self.verticalLayout_3.addLayout(self.verticalLayout_2)
        spacerItem5 = QtWidgets.QSpacerItem(20, 30, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        self.verticalLayout_3.addItem(spacerItem5)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.lblP1 = QtWidgets.QLabel(self.centralwidget)
        font = QtGui.QFont()
        font.setPointSize(20)
        self.lblP1.setFont(font)
        self.lblP1.setTextFormat(QtCore.Qt.PlainText)
        self.lblP1.setAlignment(QtCore.Qt.AlignCenter)
        self.lblP1.setObjectName("lblP1")
        self.horizontalLayout_3.addWidget(self.lblP1)
        self.lblP2 = QtWidgets.QLabel(self.centralwidget)
        font = QtGui.QFont()
        font.setPointSize(20)
        self.lblP2.setFont(font)
        self.lblP2.setAlignment(QtCore.Qt.AlignCenter)
        self.lblP2.setObjectName("lblP2")
        self.horizontalLayout_3.addWidget(self.lblP2)
        self.verticalLayout_3.addLayout(self.horizontalLayout_3)
        self.gridLayout.addLayout(self.verticalLayout_3, 0, 0, 1, 1)
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Comunicador serial"))
        self.btnSearch.setText(_translate("MainWindow", "Buscar puertos"))
        self.btnConnect.setText(_translate("MainWindow", "Conectarse"))
        self.btnDisconnect.setText(_translate("MainWindow", "Desconectar"))
        self.btnSend.setText(_translate("MainWindow", "Enviar"))
        self.lblP1.setText(_translate("MainWindow", "Pot1: 0.00V"))
        self.lblP2.setText(_translate("MainWindow", "Pot2: 0.00V"))
