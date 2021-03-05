import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("SereneLinux Update Wizard")

    Frame {
        id: frame
        x: 22
        y: 34
        width: 309
        height: 223

        CheckBox {
            id: mugshot_fix
            x: -12
            y: -12
            text: qsTr("Xfce mugshot fix")
            checkable: false
            checked: true
        }
    }

    Label {
        id: label
        x: 22
        y: 9
        text: qsTr("Update Contents")
    }

    Button {
        id: installbutton
        x: 458
        y: 393
        text: qsTr("Install")
    }

}
