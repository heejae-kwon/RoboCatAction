
'use strict';
const base64url = require('base64url');
const userDB = require('../../../../userDatabase.js');

/**
     * Set Routing to create user.
     * @param {express.Router} router - expres.Router().
     */
const SetCreateUserRouting = (router) => {
  // Post
  /** Creating a user with POST on users/ */
  router.post('/v1/users', async (req, res) => {
    if (!req.body.username ||
      !req.body.password ||
      !req.body.avatar) {
      res.status(400).send();
      return;
    }
    // Create duplicate user
    let findUser = null;
    try {
      findUser = await userDB.findUser({ username: req.body.username });
      if (findUser) {
        res.status(409).send();
        return;
      }
    } catch (err) {
      res.status(500).send();
      return;
    }

    // Create a new user succeeds
    const newUser = {
      id: base64url(req.body.username).toString(),
      username: req.body.username.toString(),
      password: req.body.password.toString(),
      avatar: req.body.avatar.toString()
    };
    try {
      const insertUser = await userDB.findUserAndUpdate(newUser);
      res.status(200);
      res.json(insertUser);
    } catch (err) {
      res.status(500).send();
    }
  });
}

/**
 * createUser module.
 * @module SetCreateUserRouting
 * @type {function}
 */
module.exports = SetCreateUserRouting;
