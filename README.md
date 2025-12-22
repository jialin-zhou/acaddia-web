# Acaddia-Web (Web Serial 版)

本项目是一个基于 Web Serial API 的现代化串口测控终端。它完全脱离了传统的后端依赖（如 Java/Python），直接通过浏览器驱动硬件串口，实现了轻量化、高性能的数据交互与可视化。

## 🌟 项目特性

零后端依赖: 仅使用浏览器原生的 Web Serial API，无需安装额外驱动或运行复杂的后端服务。

安全离线运行: 支持在隔离的工业环境下通过本地微型服务器启动，确保安全上下文（Secure Context）以调用硬件接口。

高性能渲染: 采用 Vue 3 响应式架构处理数据，确保高频串口数据流下的流畅交互。

一键启动: 为 Windows 用户内置了 start.bat 脚本，实现“即点即用”的离线体验。

## 🛠️ 技术选型

核心 API: Web Serial API (浏览器原生串口支持)。

前端框架: Vue.js 3 (用户操作界面与业务逻辑)。

UI 组件库: Element Plus (标准化界面组件)。

构建工具: Vue CLI / Webpack。

离线服务: Node.js (用于运行静态资源托管脚本 server.js)。

## 📂 目录结构

项目目前已采用扁平化根目录结构：

``````txt
acaddia-web/                <-- 项目根目录
├── src/                    <-- 核心源码（串口解析、组件逻辑）
├── public/                 <-- 静态资源（图标、基础模板）
├── dist/                   <-- 生产环境产物（执行 npm run build 后生成）
├── node_modules/           <-- 项目依赖文件夹
├── server.js               <-- 微型本地服务器（解决 Web Serial 权限环境要求）
├── start.bat               <-- Windows 一键启动脚本
├── package.json            <-- 依赖管理与项目脚本配置
├── vue.config.js           <-- Vue 项目构建配置
└── README.md               <-- 项目说明文档
``````

## 🚀 快速开始

1. 开发环境启动

   若需进行功能开发，请确保本地已安装 Node.js。

```bash
# 安装项目依赖

npm install

# 启动开发服务器 (默认运行在 http://localhost:8080)

npm run serve
```

2. 生产环境打包
   分发给用户前，需执行打包命令生成优化后的离线文件：

```bash
npm run build
# 产物将生成在 dist/ 文件夹中。
```

3. 离线使用 (最终用户)
   针对现场操作人员，直接使用根目录下的启动工具，无需安装开发环境；

启动服务: 双击运行 start.bat。脚本会自动通过 Node.js 启动本地微型服务器。

浏览器访问: 脚本将引导 Chrome/Edge 浏览器自动访问 http://localhost:8080。

选择设备: 点击页面上的“连接”按钮，在浏览器弹窗中选择对应的硬件串口设备。

注意: 必须使用支持 Web Serial API 的浏览器（推荐最新版 Chrome 或 Edge）。

## 🔌 硬件兼容性

支持所有标准串口设备（USB 转 TTL、RS232、RS485 等）。

连接步骤: 硬件连接后，需在浏览器弹出请求时手动授权对应的通讯端口。