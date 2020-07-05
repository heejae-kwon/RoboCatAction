module.exports = {
  apps: [{
    name: 'assignment4',
    script: 'assignment4.js',

    // Options reference: https://pm2.keymetrics.io/docs/usage/application-declaration/
    args: 'one two',
    instances: 1,
    autorestart: true,
    watch: false,
    max_memory_restart: '1G',
    env: {
      NODE_ENV: 'development',
      MONGO_IP: 'mongodb://localhost',
      MONGO_PORT: 27017,
      MONGO_NAME: 'assignment4',
      REDIS_IP: '127.0.0.1',
      REDIS_PORT: 6379,
      EXPRESS_PORT: 3100,
      SESSION_DURATION: 10
    },
    env_production: {
      NODE_ENV: 'production'
    }
  }]
};
