
'use strict';
const userDB = require('../../../../userDatabase.js');
const userSessionDB = require('../../../../userSession.js');
/**
     * Set Routing to get user with id.
     * @param {express.Router} router - expres.Router().
     */
const GetUser = (router) => {
  // Get
  /** Retrieve a user by ID with GET on users/:id */
  router.get('/v1/users/:id', async (req, res) => {
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
      userInfo = await userDB.findUser({ id: req.params.id });
    } catch (err) {
      res.status(500).send();
      return;
    }

    if (!userInfo) {
      // Updating fails with bad username (valid session)
      res.status(404).send();
      return;
    }

    let userSession = null;
    try {
      userSession = await userSessionDB.getSession(`id:${userInfo.id}`);
    } catch (err) {
      res.status(500).send();
      return;
    }
    if (!userSession) {
      // Updating fails with bad username (bad session)
      res.status(401).send();
      return;
    }

    if (!(userSession.session === req.body.session && userSession.token === req.body.token)) {
      // Retrieving a different user succeeds
      userInfo = { id: userInfo.id, username: userInfo.username, avatar: userInfo.avatar };
    }
    res.status(200);// Set status to 404 as movie was not found
    res.json(userInfo);
  });
}

/**
 * getUser module.
 * @module GetUser
 * @type {function}
 */
module.exports = GetUser;
