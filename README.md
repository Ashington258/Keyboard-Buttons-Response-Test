1.时间侦测精度问题，你已经解决了
2.需要 “触发” + “松开” 两个行为的具体时间戳，同时计算出两者之间的时间差
3.当同时触发两个方向键时（这里的方向键不是必须指定为 W S A D 的），我需要计算出两者速度的矢量和以及方向
//具体的单位时间加速度我去详细了解一下再告诉你，你先整一个构思

4.（这一点暂时处在构想阶段，属于我负责的UI部分）需要一个持续运行的时间轴（长宽和大小待定），
当我按下任意按键时（按键支持数量待定），按键的触发松开、持续时间都能够在该时间轴上得到体现
