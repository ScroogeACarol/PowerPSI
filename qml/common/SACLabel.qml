import QtQuick 2.14
import QtQuick.Controls 2.14
/*
    // 本质是一个Label, 具备正常Label的所有属性和信号
*/
Label {
    id: root
    width: this.contentWidth
    height: this.contentHeight
    verticalAlignment: Text.AlignVCenter
    lineHeight: this.font.pixelSize
    lineHeightMode: Text.FixedHeight
    text: ""
    color: "black"
    font.family: "SimHei"
    font.pixelSize: 12
}

/*
    宋体 SimSun
    黑体 SimHei
    微软雅黑 Microsoft YaHei
    微软正黑体 Microsoft JhengHei
    新宋体 NSimSun
    新细明体 PMingLiU
    细明体 MingLiU
    标楷体 DFKai-SB
    仿宋 FangSong
    楷体 KaiTi
    仿宋_GB2312 FangSong_GB2312
    楷体_GB2312 KaiTi_GB2312
*/