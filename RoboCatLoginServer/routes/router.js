
/* eslint-disable space-before-function-paren */
'use strict';
const APIRouter = require('./api/v1/apiRouter.js');

/**
 * Router.
 * @class
 * @param {express} app - express app.
 */
class Router {
  constructor(app) {
    this.apiRouter = new APIRouter();
    /** Using api router */
    app.use('/api', this.apiRouter.getRouter());
  }
}
/**
 * Module for Routing.
 * @module Router
 */
module.exports = Router;
