// 引入 Node.js 内置模块
const http = require('http'); // 用于创建 HTTP 服务器
const fs = require('fs');     // 用于读取磁盘上的文件
const path = require('path'); // 用于处理文件路径

const PORT = 8080; // 定义服务器运行的端口号
// 定义静态资源所在的文件夹（即 Vue 打包生成的 dist 目录）
const DIST_DIR = path.join(__dirname, 'dist');

// 创建服务器实例
http.createServer((req, res) => {
    // 1. 将请求的 URL 转换为磁盘上的实际文件路径
    // 如果访问根路径 "/"，则默认指向 "index.html"
    let filePath = path.join(DIST_DIR, req.url === '/' ? 'index.html' : req.url);

    // 2. 获取文件的后缀名（如 .html, .js）
    const extname = path.extname(filePath);

    // 3. 设置 MIME 类型，告诉浏览器这是一个什么文件，否则浏览器可能无法正确解析 JS 或 CSS
    const contentType = {
        '.html': 'text/html',
        '.js': 'text/javascript',
        '.css': 'text/css'
    }[extname] || 'text/plain';

    // 4. 从磁盘读取对应的文件
    fs.readFile(filePath, (err, content) => {
        if (err) {
            // 如果文件不存在（比如路径写错了），返回 404 错误
            res.writeHead(404);
            res.end('File not found');
        } else {
            // 如果读取成功，发送 200 状态码和文件内容给浏览器
            res.writeHead(200, { 'Content-Type': contentType });
            res.end(content, 'utf-8');
        }
    });
}).listen(PORT); // 让服务器开始监听 8080 端口

console.log(`Server running at http://localhost:${PORT}`);