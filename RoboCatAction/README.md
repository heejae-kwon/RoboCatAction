# RoboCatAction
> This project includes RoboCatAction which is a game part of [RoboCatAction](https://github.com/heejae-kwon/RoboCatAction)

The codes in this project is a example code of 


## Tech/framework used
- [CppRestSDK](https://github.com/microsoft/cpprestsdk)
- [SDL2](https://libsdl.org/download-2.0.php)


## Prerequisites
#### Client
* Visual Studio 19 or newer
#### Server
* g++
* make

## Build
#### Client
Run Release mode build in Visual Studio.
#### Server
```sh
make server
```

## Run
```sh
RoboCatServer.exe 3300
RoboCatClient.exe http://127.0.0.1:3100 usr pwd
```


<!-- Markdown link & img dfn's -->

