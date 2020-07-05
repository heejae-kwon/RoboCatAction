
'use strict';
/**
     * Set Routing to login.
     * @param {express.Router} router - expres.Router().
     */
const uuidv4 = require('uuid/v4');
const userDB = require('../../../../userDatabase.js');
const userSessionDB = require('../../../../userSession.js');

const SetLoginRouting = (router) => {
  router.post('/v1/login', async (req, res) => {
    if (!req.body.username ||
      !req.body.password) {
      res.status(400).send();
      return;
    }

    let user = null;
    try {
      user = await userDB.findUser({ username: req.body.username.toString() });
    } catch (err) {
      res.status(500).send();
      return;
    }

    // Login fails with bad username
    if (!user) {
      res.status(400).send();
      return;
    }
    // Login fails with bad password
    if (user.password !== req.body.password.toString()) {
      res.status(403).send();
      return;
    }
    // Login succeeds with a unique session
    try {
      const oldSession = await userSessionDB.getSession(`id:${user.id}`);
      if (oldSession) {
        await userSessionDB.deleteSession(`id:${oldSession.id}`);
        await userSessionDB.deleteSession(`session:${oldSession.session}`);
        await userSessionDB.deleteSession(`token:${oldSession.token}`);
      }
    } catch (error) {
      res.status(500).send();
      return;
    }
    const newSession = {
      id: user.id,
      session: uuidv4(),
      token: uuidv4()
    };

    try {
      await userSessionDB.createSession(`id:${newSession.id}`, newSession);
      await userSessionDB.createSession(`session:${newSession.session}`, newSession);
      await userSessionDB.createSession(`token:${newSession.token}`, newSession);
    } catch (error) {
      res.status(500).send();
      return;
    }
    res.status(200);
    res.json({ session: newSession.session, token: newSession.token });
  });
}

/**
 * login module.
 * @module SetLoginRouting
 * @type {function}
 */
module.exports = SetLoginRouting;
