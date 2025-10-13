# Acaddia-Web 测控终端

本项目是一个基于Web技术的现代化测控终端，旨在通过网页界面实现与硬件设备的串口通信和控制。项目采用前后端分离架构，提供了美观、响应式的用户界面和稳定、可扩展的后端服务。

## 技术选型

- **前端**: **Vue.js** 负责构建用户操作界面，使用 **Element Plus** 组件库保证UI的简洁与美观。
- **后端**: **Java** 和 **Spring Boot** 框架作为强大的后端，处理所有业务逻辑和数据交互。
- **串口通信**: **jSerialComm** 库作为Java操作串口的底层工具，稳定可靠。
- **实时通信**: **WebSocket** 作为前端和后端之间的主要通信线路，确保低延迟、双向的数据交换。
- **项目构建**: **Maven** 和 **NPM** 分别负责后端和前端的依赖管理和构建。

## Maven 模块结构

项目采用多模块结构，职责清晰，易于维护和扩展。

```
acaddia-web/                <-- 根目录
├── pom.xml                 <-- 父POM文件，统一管理依赖和模块
├── serial-core/            <-- 【模块一：串口通信服务】负责与硬件串口的直接交互。
├── protocol/               <-- 【模块二：通信协议服务】负责自定义数据帧的打包与解包。
├── webapp/                 <-- 【模块三：核心业务与Web端点】Spring Boot应用，负责业务流程编排和WebSocket通信。
└── vue-frontend/           <-- 【模块四：前端界面】所有Vue.js相关的代码、组件和资源。
```

## 主要版本信息

| 技术栈 | 版本 |
| :--- | :--- |
| Java (JDK) | 21.0.8 |
| Node.js | 22.20.0 (LTS) |
| Spring Boot | 3.2.5 |
| Vue.js | 3.2.13 |
| Element Plus | 2.2.17 |
| jSerialComm | 2.10.4 |
| Maven | 3.x+ |

---

## 项目启动与开发

我们推荐在开发环境中使用前后端分离的模式进行启动，以获得最佳的开发体验（如热重载）。

### 开发环境启动 (推荐)

**1. 启动后端服务**

- 在您的IDE（如IntelliJ IDEA）中，找到 `webapp` 模块下的 `src/main/java/com/dctrans/Application.java` 文件。
- 右键点击该文件并选择 `Run 'Application.main()'`。
- 后端服务将启动在 `http://localhost:8080`。

**2. 启动前端服务**

- 在您的IDE中打开终端，或使用独立的命令行工具，进入 `vue-frontend` 目录：
  ```bash
  cd E:/acaddia-web/vue-frontend
  ```
- 首先，安装前端依赖（仅第一次或依赖更新后需要执行）：
  ```bash
  npm install
  ```
- 然后，启动前端开发服务器：
  ```bash
  npm run serve
  ```
- 前端服务通常会启动在 `http://localhost:8081` 或其他可用端口。

**3. 访问应用**

- 打开浏览器，访问前端开发服务器提供的地址（例如 `http://localhost:8081`）。
- 前端页面发出的所有对后端API和WebSocket的请求都会被自动代理到 `http://localhost:8080`，实现无缝开发。

### 生产环境打包与启动

当您需要将整个项目打包成一个独立的可执行文件进行部署时，请执行以下步骤。

**1. 构建整个项目**

- 在项目根目录 `acaddia-web/` 下，打开终端，执行以下Maven命令：
  ```bash
  mvn clean install
  ```
- 此命令会将前端项目构建并打包进后端的JAR文件中。

**2. 运行打包后的应用**

- 构建成功后，可执行的JAR文件会生成在 `webapp/target/` 目录下。
- 使用以下命令启动应用：
  ```bash
  java -jar webapp/target/webapp-1.0.0-SNAPSHOT.jar
  ```
- 此时，只需访问 `http://localhost:8080` 即可使用完整的应用。
