# RoboCatLoginServer
> This project includes RoboCatLoginServer which is a part of [RoboCatAction](https://github.com/heejae-kwon/RoboCatAction)


## Tech/framework used
- [Mongoose](https://www.npmjs.com/package/mongoose)
- [Express](https://www.npmjs.com/package/express)
- [Redis](https://www.npmjs.com/package/redis)


## Prerequisites
* [Node.js 12 or newer](https://nodejs.org/en/)
* [RoboCatAction](https://github.com/heejae-kwon/RoboCatAction/tree/master/RoboCatAction)
* [MongoDB](https://www.mongodb.com/)
* [Redis](https://redis.io/)
* [pm2](https://www.npmjs.com/package/pm2)
* [VSCode](https://code.visualstudio.com/) (for development)

## Installation
```sh
npm install
```

## Run
```sh
pm2 start
```


## List of API call
### 1. findUserByName
  Returns json data about user information.

* **URL**
  /api/v1/users?username=

* **Method:**
  `GET`
  
*  **URL Params**
   * **Required:**
      username=[string]

* **Data Params**
      session=[string]
      token=[string]

* **Success Response:**
  * **Code:** 200 
  * **Content:** `UserInfo`(application/json)
 ```typescript
 // Example interface
 interface UserInfo { 
  id: string;
  username: string;
  avatar: string;
 }
 ```
* **Error Response:**
  * **Code:** 400, 401, 404, 500
  * **Content:** NONE

### 2. getUser
  Returns json data about user information.

* **URL**
  /api/v1/users/:id

* **Method:**
  `GET`
  
*  **URL Params**
   * **Required:**
      id=[string]

* **Data Params**
      session=[string]
      token=[string]

* **Success Response:**
  * **Code:** 200 
  * **Content:** `UserInfo`(application/json)
 ```typescript
 // Example interface
 interface UserInfo { 
  id: string;
  username: string;
  avatar: string;
 }
 ```
* **Error Response:**
  * **Code:** 400, 401, 404, 500
  * **Content:** NONE

### 3. connect
  Connect RoboCatClient with RoboCatServer
  Returns json data about user information and server address.

* **URL**
  /api/v1/connect

* **Method:**
  `POST`
  
*  **URL Params**
   * **Required:**
      NONE

* **Data Params**
      session=[string]
      token=[string]

* **Success Response:**
  * **Code:** 200 
  * **Content:** `ConnectInfo`(application/json)
 ```typescript
 // Example interface
 interface ConnectInfo { 
  id: string;
  username: string;
  avatar: string;
  // Address of RoboCatActionServer
  server: string;
 }
 ```
* **Error Response:**
  * **Code:** 400, 401, 404, 500
  * **Content:** NONE

### 4. createUser
  Create user. Returns json data about user information.

* **URL**
  /api/v1/users

* **Method:**
  `POST`
  
*  **URL Params**
   * **Required:**
      NONE

* **Data Params**
      username=[string]
      password=[string]
      avatar=[string]

* **Success Response:**
  * **Code:** 200 
  * **Content:** `UserIdInfo`(application/json)
 ```typescript
 // Example interface
 interface UserIdInfo { 
  id: string;
  username: string;
  password: string;
  avatar: string;
 }
 ```
* **Error Response:**
  * **Code:** 400, 401, 404, 500
  * **Content:** NONE


### 5. login
  Login user. Returns json data about session.

* **URL**
  /api/v1/login

* **Method:**
  `POST`
  
*  **URL Params**
   * **Required:**
      NONE

* **Data Params**
      username=[string]
      password=[string]

* **Success Response:**
  * **Code:** 200 
  * **Content:** `SessionInfo`(application/json)
 ```typescript
 // Example interface
 interface SessionInfo{ 
   session : string;
   token: string;
 }
 ```
* **Error Response:**
  * **Code:** 400, 401, 404, 500
  * **Content:** NONE

### 6. updateUser
  Update user information. Returns json data about session.

* **URL**
  /api/v1/users/:id

* **Method:**
  `PUT`
  
*  **URL Params**
   * **Required:**
      id=[string]

* **Data Params**
      session=[string]
      token=[string]

* **Success Response:**
  * **Code:** 200 
  * **Content:** `UserIdInfo`(application/json)
 ```typescript
 // Example interface
 interface UserIdInfo{ 
   id : string;
   username: string;
   password: string;
   avatar: string;
 }
 ```
* **Error Response:**
  * **Code:** 400, 401, 404, 500
  * **Content:** NONE





## License
                                 Apache License
                           Version 2.0, January 2004
                        http://www.apache.org/licenses/

Made by [Heejae Kwon](https://github.com/heejae-kwon)
<!-- Markdown link & img dfn's -->

