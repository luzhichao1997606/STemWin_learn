
<!--
 * @fileName: 
 * @description: 
 * @version: 
 * @author: lzc
 * @date: Do not edit
 * @lastEditors: lzc
 * @lastEditTime: Do not Edit
--> 
# STemWin_learn
测试`STemWin`的实际效果，基于`HAL`以及`STM32F103ZET6` 正点原子精英板

## 2020年10月12日 
> ### 完成`HAL`的基于`FSMC`的`LCD`功能实现

## 2020年10月12日
> ### 添加`STemWin`功能，`GUI`测试完成。`STemWin`版本较老为`5.26`

## 2020年10月12日
> ### 添加`RT-Thread`操作系统，但是`emWin`还是无操作系统。版本为`5.26`，无触摸。
> ### 遇到一个问题，如果`STemWin` 进行显示字符串之后串口输出就会停止，甚至`HAL`库的底层函数都无法调用，最后通过程序初始化串口解决。