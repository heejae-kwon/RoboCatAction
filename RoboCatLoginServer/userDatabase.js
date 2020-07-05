
'use strict';
/* eslint-disable promise/param-names */
/* eslint-disable space-before-function-paren */
/* eslint-disable no-unused-vars */
const mongoose = require('mongoose');

/**
 * MongoDB for user data.
 * @class
 */
class UserDatabase {
  constructor() {
    mongoose.connect(process.env.MONGO_IP + ':' +
      process.env.MONGO_PORT.toString() + '/' +
      process.env.MONGO_NAME, {
      useNewUrlParser: true,
      useCreateIndex: true,
      useUnifiedTopology: true,
      useFindAndModify: false
    });

    const userSchema = new mongoose.Schema({
      id: String,
      username: String,
      password: String,
      avatar: String
    });
    userSchema.index({ id: 1, username: 1 }, { unique: true });

    this._userCollections = mongoose.model('users', userSchema);
    this.db = mongoose.connection;
  }

  /**
     * Add new user data to database.
     * @param {Object} newUser - {id, username, password, avatar}.
     * @returns {Promise} - Promise object of user.
     */
  findUserAndUpdate(newUser) {
    return new Promise((resovle, reject) => {
      this._userCollections.findOneAndUpdate(
        { id: newUser.id },
        {
          $set: {
            username: newUser.username,
            password: newUser.password,
            avatar: newUser.avatar
          }
        },
        {
          new: true,
          upsert: true
        },
        (err, model) => {
          if (err) {
            // res.sendStatus(500);
            return reject(err);
          }
          resovle(model);
        });
    });
  }

  /**
    * Find user from database.
    * @param {Object} filter - key object.
    * @returns {Promise} - Promise object of user.
    */
  findUser(filter) {
    return new Promise((resovle, reject) => {
      this._userCollections.findOne(
        filter,
        (err, model) => {
          if (err) {
            return reject(err);
          }
          resovle(model);
        });
    });
  }
}

const userDB = new UserDatabase();
/**
 * Singleton object of UserDatabase.
 * @module userDB
 * @type {UserDatabase}
 */
module.exports = userDB;
