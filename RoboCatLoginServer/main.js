/* eslint-disable space-before-function-paren */
/* eslint-disable no-unused-vars */

'use strict';
/** main file of CS261 assignment 2. */
const express = require('express');
const Router = require('./routes/router.js');
const userDB = require('./userDatabase.js');
const userSessionDB = require('./userSession.js');

/**
 * main class.
 * @class
 */
class App {
  constructor() {
    this.app = express();
    this.app.use(express.json());
    this.app.use(express.urlencoded({ extended: true }));
    this.router = new Router(this.app);
    this.db = userDB.db;
    this.sessiondb = userSessionDB.redisClient;
  }

  runDB() {
    return new Promise((resolve, reject) => {
      this.db.on('error', (err) => {
        if (err) {
          reject(err);
        }
      });

      this.db.once('open', () => {
        resolve();
      });
    });
  }

  async run() {
    try {
      await this.runDB();
    } catch (e) {
      console.log(e);
      return;
    }

    this.app.listen(process.env.EXPRESS_PORT, () => {
    });
  }
}

const server = new App();
server.run();
