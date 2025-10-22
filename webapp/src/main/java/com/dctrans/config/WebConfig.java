package com.dctrans.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.cors.CorsConfiguration;
import org.springframework.web.cors.UrlBasedCorsConfigurationSource;
import org.springframework.web.filter.CorsFilter;

import java.util.List;

/**
 * @class WebConfig
 * @brief 配置应用的全局 Web 相关设置，特别是 CORS 策略。
 * @details
 * 此配置使用基于 Filter 的方式，它比基于 WebMvcConfigurer 的方式具有更高的优先级，
 * 能更可靠地解决跨域问题，特别是当项目中未来可能引入 Spring Security 时。
 */
@Configuration
public class WebConfig {

    @Bean
    public CorsFilter corsFilter() {
        UrlBasedCorsConfigurationSource source = new UrlBasedCorsConfigurationSource();
        CorsConfiguration corsConfig = new CorsConfiguration();

        // 允许来自前端开发服务器的请求。在开发环境中，允许所有来源 (*) 是最直接的解决方案。
        corsConfig.setAllowedOriginPatterns(List.of("*"));

        // 允许所有请求头
        corsConfig.addAllowedHeader("*");

        // 允许所有 HTTP 方法 (GET, POST, etc.)
        corsConfig.addAllowedMethod("*");

        // 允许浏览器发送凭据 (如 cookies)
        corsConfig.setAllowCredentials(true);

        // 将此 CORS 配置应用到所有 /api/ 路径下的接口
        source.registerCorsConfiguration("/api/**", corsConfig);

        return new CorsFilter(source);
    }
}
