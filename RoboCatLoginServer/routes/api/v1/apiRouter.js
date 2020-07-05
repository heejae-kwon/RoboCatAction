/* eslint-disable no-unused-vars */
/* eslint-disable space-before-function-paren */
/* eslint-disable no-array-constructor */
/* eslint-disable quotes */

'use strict';
const base64url = require('base64url');
const express = require('express');
const SetUpdateUserRouting = require('./put/updateUser.js');
const SetGetUserRouting = require('./get/getUser.js');
const SetFindUserByName = require('./get/findUserByName.js');
const SetCreateUserRouting = require('./post/createUser.js');
const SetLoginRouting = require('./post/login.js');
const SetConnectRouting = require('./post/connect.js');

/**
 * API Router class.
 * @class
 */
class APIRouter {
  constructor() {
    this.router = express.Router();
    const initialValue = {
      id: base64url('usr'),
      username: 'usr',
      password: 'pwd',
      avatar: 'avatar1.png'
    };

    SetUpdateUserRouting(this.router);
    SetFindUserByName(this.router);
    SetGetUserRouting(this.router);
    SetCreateUserRouting(this.router);
    SetLoginRouting(this.router);
    SetConnectRouting(this.router);
    /** default routing */
    this.router.get('/', (req, res) => {
      res.json({
        status: 'API Its Working',
        message: 'Welcome to RESTHub crafted with love!'
      });
    });
  }

  /**
     * Return api router.
     * @return {express.Router} - express.Router().
     */
  getRouter() {
    return this.router;
  }
}
/**
 * api router module.
 * @module APIRouter
 * @type {class}
 */
module.exports = APIRouter;
