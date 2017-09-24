import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import qmllive.logger 1.0 as MyLog

ApplicationWindow {
    visible: true
    width: 600
    height: 400
    title: qsTr("Game Center Dev")

    property alias headerItemAlias: header.item
    property alias contentItemAlias: content.item

    header: Loader {
        id: header
        source: "HeaderComponent.qml"
        objectName: "header"
        active: true
        Binding {
            target: contentItemAlias
            property: 'currentIndex'
            // ensure the current status is not null
            value: if (header.status == Loader.Ready) header.item.currentIndex
            // the content is ready
            when: content.status === Loader.Ready
        }
    }

    Loader {
        id: content
        anchors.fill: parent
        source: "ContentComponent.qml"
        objectName: "content"
        active: true
        focus: true // should add this because we use FocusScope below which will forward key and mouse to focus: true
        Binding {
            target: headerItemAlias
            property: 'currentIndex'
            value: if (content.status == Loader.Ready) content.item.currentIndex
            when: header.status === Loader.Ready
        }
    }

    Shortcut {
        sequence: "Ctrl+L"
        onActivated: logcurtain.clear()
    }

    Shortcut {
        sequence: "Ctrl+M"
        onActivated: {
            logcurtain.visible = !logcurtain.visible
        }
    }

    FocusScope{
        focus: false
        enabled: false
        width: parent.width
        height: parent.height
        TextEdit {
            id:logcurtain
            width: parent.width
            height: parent.height
            focus: false
            activeFocusOnPress: false
            cursorVisible: false
            readOnly: true
            wrapMode: TextEdit.WordWrap
            visible: false
            Connections {
                target: MyLog.Logger
                onMessage: logcurtain.append(msg)
            }
        }
    }


}


