
'use strict';
const userDB = require('../../../../userDatabase.js');
const userSessionDB = require('../../../../userSession.js');
/**
     * Set Routing to find user by name.
     * @param {express.Router} router - expres.Router().
     */
const SetFindUserByName = (router) => {
  /** Searching for a user by name with GET on users */
  router.get('/v1/users', async (req, res) => {
    if (!req.body.session ||
      !req.body.token) {
      /**  Searching fails with no session */
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
    if (!req.query.username) {
      // Searching fails with no username (valid session)
      res.status(400).send();
      return;
    }

    let userInfo = null;
    try {
      userInfo = await userDB.findUser({ username: req.query.username });
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
      // Searching for a different user succeeds
      userInfo = { id: userInfo.id, username: userInfo.username, avatar: userInfo.avatar };
    }
    res.status(200);
    res.json(userInfo);
  });
}

/**
 * findUserByName module.
 * @module SetFindUserByName
 * @type {function}
 */
module.exports = SetFindUserByName;
