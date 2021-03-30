import QtQuick 2.12
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.1
ApplicationWindow {
    id:mainwin
    objectName: "MainWindowkun"
    width:480
    height:240
    visible: true
    title: qsTr("Serene Updater")
    signal enterOkButton();
    MessageDialog {
        id: successMessageDialog
        objectName: "success_dialog"
        title: qsTr("Serene Updater")
        text: qsTr("Success Update")
        onAccepted: {
            Qt.quit()
        }
        visible: false
    }
        Text {
            id: text1
            x: 47
            y: 16
            width: 388
            height: 52
            text: qsTr("Update these contents")
            font.pixelSize: 24
        }

        Label {
            id: textArea
            x: 99
            y: 82
            width: 336
            height: 63
            text: qsTr("●Browser from Flast to Firefox
●Change LightDM Greeter")
        }

        Button {
            id: okbutton
            x: 335
            y: 176
            text: qsTr("OK")
            onClicked: {
                enterOkButton();
            }
        }

        Button {
            id: cancelbutton
            x: 47
            y: 176
            text: qsTr("Cancel")
            onClicked: {
                Qt.quit()
            }
        }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
