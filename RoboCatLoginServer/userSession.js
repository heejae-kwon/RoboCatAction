/* eslint-disable space-before-function-paren */
/* eslint-disable promise/param-names */
/* eslint-disable no-unused-vars */
'use strict';

const redis = require('redis');

/**
 * Redis for user session.
 * @class
 */
class UserSession {
  constructor() {
    this.redisClient = redis.createClient(process.env.REDIS_PORT, process.env.REDIS_IP);
  }

  /**
  * Add session data of user to Redis.
  * @param {Object} key - key object.
  * @param {Object} newSession - {id,session,token}.
  * @returns {Promise} - Promise object of user session.
  */
  createSession(key, newSession) {
    return new Promise((resolve, reject) => {
      this.redisClient.hmset(key.toString(), (newSession), (err, result) => {
        if (err) {
          reject(err);
        } else {
          this.redisClient.expire(key, process.env.SESSION_DURATION);
          resolve(result);
        }
      });
    });
  }

  /**
* Find session data from Redis.
* @param {Object} key - key object.
* @returns {Promise} - Promise object of user session.
*/
  getSession(key) {
    return new Promise((resolve, reject) => {
      this.redisClient.hgetall(key.toString(), (error, result) => {
        if (error) {
          reject(error);
        } else {
          resolve(result);
        }
      });
    });
  }

  /**
* Delete session data from Redis.
* @param { Object } key - key object.
* @returns { Promise } - Promise object of result of deleting.
*/
  deleteSession(key) {
    return new Promise((resolve, reject) => {
      this.redisClient.del(key.toString(), (err, response) => {
        if (err) {
          reject(err);
        } else if (response === 1) {
          resolve(true);
        } else {
          resolve(false);
        }
      });
    });
  }
}

const userSessionDB = new UserSession();
/**
 * Singleton object of UserSession.
 * @module userSessionDB
 * @type {UserSession}
 */
module.exports = userSessionDB;
