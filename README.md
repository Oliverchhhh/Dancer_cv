# 仓库指南

这是`Robocup`仿人组赛道`ZJU·Dancer`队视觉组图像检测模块。实现以下功能：

- 输入：双目RGB图像

- 输出

  1. 检测出图像中的白线、白色圆心、白色标点

  2. 计算<1>中检测出在目标在机器人世界坐标系下的方程（待定）

- 要求

  该方法应当适应以下环境：

  - 白色干扰（球场周边有大片白色）
  - 反光 （待定）
  - 图片亮、暗不同 
  - 机器人遮挡

  