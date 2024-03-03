# snake

## 介绍
基于面向对象的C++贪吃蛇小游戏，并采用easyx框架做界面渲染。

food为食物类，负责游戏中的食物显示；
snake为贪吃蛇类，由蛇头和蛇身组成；
game为游戏引擎类，负责游戏的初始化以及画面实时渲染等；
main为程序入口。

游戏由一个主线程与两个子线程组成，主线程负责游戏的逻辑，第一个子线程负责键盘指令接受，第二个子线程负责画面渲染。


方向键：
上：↑，下：↓，左：←，右：→

速度键：
加速：F1，减速：F2

暂停\开始键：space

退出键：ESC
