module.exports = {
    root: true,
    env: {
        node: true
    },
    extends: [
        // 这一行是关键，它会启用所有 Vue 3 的推荐规则
        'plugin:vue/vue3-recommended',
        'eslint:recommended'
    ],
    parserOptions: {
        parser: '@babel/eslint-parser',
        requireConfigFile: false // 解决某些 babel 报错
    },
    rules: {
        // 在这里可以自定义你的规则，比如：
        'no-console': process.env.NODE_ENV === 'production' ? 'warn' : 'off',
        'no-debugger': process.env.NODE_ENV === 'production' ? 'warn' : 'off',
        'vue/multi-word-component-names': 'off' // 关闭组件名必须为多词的规则
    }
};