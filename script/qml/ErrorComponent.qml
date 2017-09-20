import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    anchors.fill: parent
    Text{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        text: "Syntax error. Don't worry,\n all you need to do is just correct it! It will not need re-build."
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 20
        color: "blue"
    }
}
