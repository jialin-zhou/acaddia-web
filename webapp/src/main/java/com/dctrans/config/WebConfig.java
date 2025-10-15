package com.dctrans.config;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

/**
 * @class WebConfig
 * @brief 配置应用的全局 Web 相关设置，例如 CORS 策略。
 */
@Configuration
public class WebConfig implements WebMvcConfigurer {

    /**
     * @brief 配置跨域资源共享 (CORS)。
     *
     * 允许来自前端开发服务器 (通常是 localhost:5173) 的请求访问后端的 API。
     * 这是解决浏览器中 "Failed to fetch" 错误的标准方法。
     *
     * @param registry CORS 配置注册表。
     */
    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/api/**") // 仅对 /api 路径下的接口生效
                .allowedOrigins("http://localhost:5173") // 允许的前端服务器地址
                .allowedMethods("GET", "POST", "PUT", "DELETE", "OPTIONS") // 允许的 HTTP 方法
                .allowedHeaders("*") // 允许所有请求头
                .allowCredentials(true); // 是否允许发送 Cookie
    }
}
