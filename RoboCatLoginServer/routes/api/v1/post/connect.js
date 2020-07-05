'use strict';
const userDB = require('../../../../userDatabase.js');
const userSessionDB = require('../../../../userSession.js');
/**
     * Set Routing to connect.
     * @param {express.Router} router - expres.Router().
     */
const SetConnectRouting = (router) => {
  router.post('/v1/connect', async (req, res) => {
    // Retrieving fails with no session
    if (!req.body.session ||
      !req.body.token) {
      res.status(401).send();
      return;
    }

    let isSessionValid = null;
    let isTokenValid = null;
    try {
      isSessionValid = await userSessionDB.getSession(`session:${req.body.session}`);
      isTokenValid = await userSessionDB.getSession(`token:${req.body.token}`);
    } catch (error) {
      res.status(500).send();
      return;
    }
    if (!isSessionValid || !isTokenValid) {
      /** Updating fails with bad session */
      /** Updating fails with bad username (bad session) */
      res.status(401).send();
      return;
    }

    let userInfo = null;
    try {
      userInfo = await userDB.findUser({ id: isSessionValid.id });
    } catch (err) {
      res.status(500).send();
      return;
    }

    const responseBody = {
      id: userInfo.id.toString(),
      username: userInfo.username.toString(),
      avatar: userInfo.avatar.toString(),
      server: '127.0.0.1:3300'
    };

    res.status(200);// Set status to 404 as movie was not found
    res.json(responseBody);
  });
}

/**
 * connect module.
 * @module SetConnectRouting
 * @type {function}
 */
module.exports = SetConnectRouting;
