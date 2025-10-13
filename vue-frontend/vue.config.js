const { defineConfig } = require('@vue/cli-service');

module.exports = defineConfig({
  transpileDependencies: true,

  // Configuration for the development server
  devServer: {
    // Assign a specific port to avoid conflicts with the backend
    port: 8081,

    // When running `npm run serve`, all API and WebSocket requests will be proxied
    // from the frontend server (localhost:8081) to the backend Spring Boot server (localhost:8080).
    proxy: {
      // Proxy WebSocket connection requests
      '/ws': {
        target: 'http://localhost:8080',
        ws: true, // This is crucial for WebSockets
        changeOrigin: true
      },
      // You can add other API endpoints here if needed in the future
      '/api': {
        target: 'http://localhost:8080',
        changeOrigin: true
      }
    }
  }
});
