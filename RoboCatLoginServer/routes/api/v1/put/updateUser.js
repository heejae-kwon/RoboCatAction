'use strict';
const userDB = require('../../../../userDatabase.js');
const userSessionDB = require('../../../../userSession.js');
/**
     * Set Routing to update user info.
     * @param {express.Router} router - expres.Router().
     */
const SetUpdateUserRouting = (router) => {
  // PUT
  /** Updating a user by ID with PUT on users/:id. */
  router.put('/v1/users/:id', async (req, res) => {
    if (!req.body.session ||
      !req.body.token) {
      // Updating fails with no session
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
      userSession = await userSessionDB.getSession(`id:${req.params.id}`);
    } catch (err) {
      res.status(500).send();
      return;
    }

    if (!userSession) {
      // Updating fails with bad username (bad session)
      res.status(401).send();
      return;
    }

    if (!(userSession.session === req.body.session &&
      userSession.token === req.body.token)) {
      // Updating fails on different user
      res.status(403).send();
      return;
    }

    // Updating succeeds with new data
    const oldUserInfo = userInfo;
    const newUserInfo = {
      id: oldUserInfo.id.toString(),
      username: req.body.username.toString(),
      password: req.body.password.toString(),
      avatar: req.body.avatar.toString()
    };
    try {
      const findUserAndUpdate = await userDB.findUserAndUpdate(newUserInfo);
      res.status(200);
      res.json(findUserAndUpdate);
    } catch (e) {
      res.status(500).send();
    }
  });
}

/**
 * updateUser module.
 * @module SetUpdateUserRouting
 * @type {function}
 */
module.exports = SetUpdateUserRouting;
