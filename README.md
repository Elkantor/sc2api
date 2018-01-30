# sc2api
> A node.js module to easily create bots for Starcraft 2

The role of this package is to bring the official Starcraft 2 C++ API to node.js, through a native node module.
The whole API will be usable fully with the power of javascript, to perform an easiest way to create and debugg your bot.

<code>
Warning : This project is currently under development, and is likely to include all kinds of bugs.
</code>

## Installing

Clone this repository in the folder of you choice by typing the following command : 

```shell
git clone https://github.com/Elkantor/sc2api.git
```

And type this command to install the module :

```shell
npm install
```

Or you can directly install the module by using npm like this, if you already have a node.js project sets up :

```shell
npm install --save sc2api
```

## Developing

### Built With

[nan](https://github.com/nodejs/nan) (native abstractions for node.js), to be able to use the v8 C++ engine by google, without worring about the versions of v8
[node-gyp](https://github.com/nodejs/node-gyp) for compiling C++ native addon modules for Node.js
[sc2client-api](https://github.com/Blizzard/s2client-api), the official C++ API by Blizzard, to create bot for Starcraft 2

### Prerequisites

This node.js module is a native node module, which means you need to compile it when you install it, before to be able to use it.
To do that, this project use [node-gyp](https://github.com/nodejs/node-gyp) module (which works with python 2.7).
So be sure to install python 2.7 as well as the Visual C++ Build Environment (for windows). 
Or follow the instructions listed here, to be sure to be able to use node-gyp as expected : [node-gyp instructions](https://github.com/nodejs/node-gyp).

###  Getting started

You will find all the documentation, with exemples, to quickly getting start in the [doc](https://github.com/Elkantor/sc2api/tree/master/doc) folder.

For exemple, the [getting_start](https://github.com/Elkantor/sc2api/blob/master/doc/getting_start.md) file show you an exemple to quickly create a default bot (wich don't do anything, just sets up the parameters and launch the game with the default bot behavior).

## Licensing

(The MIT License)

Copyright (c) 2018 Victor Gallet <victor.gallet@hotmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


