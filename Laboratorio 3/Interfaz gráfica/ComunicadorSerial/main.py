# pyuic5 -x ui/main_gui.ui -o gui.py
# pyinstaller -F --onefile -w --name=Comunicador serial --icon=./resources/logo.ico ./scripts/main.py
# pyinstaller -F --onefile -w --name=ComunicadorSerial --icon=./assets/icon.ico ./main.py

from PyQt5 import QtWidgets
from gui import Ui_MainWindow
import sys
from Serial import Serial


class Main(object):

    def __init__(self):
        app = QtWidgets.QApplication(sys.argv)
        MainWindow = QtWidgets.QMainWindow()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(MainWindow)
        self.setActionButtons()
        self.serialConnection = Serial()
        app.aboutToQuit.connect(self.onClosingEvent)
        MainWindow.show()
        sys.exit(app.exec_())

    def setActionButtons(self):
        self.ui.btnSearch.clicked.connect(self.getSerialPorts)
        self.ui.btnConnect.clicked.connect(self.connect)
        self.ui.btnDisconnect.clicked.connect(self.disconnect)
        self.ui.btnSend.clicked.connect(self.send)

    def getSerialPorts(self):
        self.ui.lvPorts.clear()
        self.ports = self.serialConnection.getPorts()
        items = [f'{n.device} - {n.description}' for n in self.ports]
        self.ui.lvPorts.addItems(items)

    def connect(self):
        indexes = self.ui.lvPorts.selectedIndexes()

        if len(indexes) > 0:
            port = self.ports[indexes[0].row()].device
            self.serialConnection.connect(port, self.ui.lblP1, self.ui.lblP2)

    def send(self):
        text = self.ui.txtContador.text().strip()

        if len(text) > 0:
            self.serialConnection.send(text)
            self.ui.txtContador.clear()

    def disconnect(self):
        self.serialConnection.disconnect()

    def onClosingEvent(self):
        self.serialConnection.disconnect()


if __name__ == '__main__':
    Main()
