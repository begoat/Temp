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
        Binding {
            target: headerItemAlias
            property: 'currentIndex'
            value: if (content.status == Loader.Ready) content.item.currentIndex
            when: header.status === Loader.Ready
        }
    }

    //    Shortcut {
    //        sequence: "Ctrl+M"
    //        onActivated: curtain.hidelog()
    //    } //默认设置为不可见

    TextEdit {
        id:curtain
        focus: false
        activeFocusOnPress: false
        selectByMouse: false
        selectByKeyboard: false
        cursorVisible: false
//        contentWidth:
        readOnly: true
        wrapMode: TextEdit.WrapAnywhere // 需要调整一下 怎么 弄 才 不让他 出界
    }

    Connections {
        target: MyLog.Logger
        onMessage: curtain.append("This is atest")
    }

}


