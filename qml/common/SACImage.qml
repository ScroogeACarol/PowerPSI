import QtQuick 2.14
import QtQuick.Controls 2.14
/*
    // 本质是一个Image, 具备正常Image的所有属性和信号
    [只读]source: 图片的最终路径
    targetSource: 图片的真实路径
    defaultSource: 图片加载失败时的默认图片路径
    imageLoadingDebugOutput: 图片加载失败时的打印输出, 建议填写使用该控件的文件路径，以便排查问题
*/
Image {
    id: root
    property string targetSource: ""
    property string defaultSource: ""
    property string imageLoadingDebugOutput: ""
    property bool checkIsFinish: false
    source: get_source()
    cache: false
    smooth: false
    // sourceSize: Qt.size(width, height)
    function get_source() {
        // if (!Tools.exists(root.targetSource) && Tools.exists(root.defaultSource)) {
        //     return root.defaultSource;
        // }
        return root.targetSource;
    }
}