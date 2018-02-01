[![npm version](https://badge.fury.io/js/sc2api.svg)](https://badge.fury.io/js/sc2api)  ![stability](https://img.shields.io/badge/stability-unstable-orange.svg)   [![Join the chat at https://gitter.im/sc2api/Lobby](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/sc2api/Lobby)  [![contact](https://img.shields.io/badge/Contact%20me%20on%20Twitter-%40TheElkantor-blue.svg)](https://twitter.com/intent/tweet?screen_name=TheElkantor)

# sc2api
> A node.js module to easily create bots for Starcraft 2 in javascript

The role of this package is to bring the official Starcraft 2 C++ API to node.js, through a native node module.
<br>
The whole API will be usable fully with the power of javascript, to perform an easiest way to create and debug your bot.

<blockquote>
<p><g-emoji class="g-emoji" alias="bulb" fallback-src="https://assets-cdn.github.com/images/icons/emoji/unicode/1f4a1.png" ios-version="6.0"><img class="emoji" alt="bulb" height="20" width="20" src="https://assets-cdn.github.com/images/icons/emoji/unicode/1f4a1.png"></g-emoji> [Warning] This project is currently under development, and is likely to be modified and to include all kinds of bugs. 
</p>
</blockquote>

## Installing / Getting started

Clone this repository in the folder of you choice by typing the following command : 

```shell
git clone https://github.com/Elkantor/sc2api.git
```

Next, you need to initialize a new node.js project with the following command : 
<blockquote>
<p><g-emoji class="g-emoji" alias="bulb" fallback-src="https://assets-cdn.github.com/images/icons/emoji/unicode/1f4a1.png" ios-version="6.0"><img class="emoji" alt="bulb" height="20" width="20" src="https://assets-cdn.github.com/images/icons/emoji/unicode/1f4a1.png"></g-emoji> If you don't have npm installed, use tool like chocolateley to install it, for exemple, or download and install it manually from its official website : [https://nodejs.org/](https://nodejs.org/en/)). 
</p>
</blockquote>

```shell
cd sc2api
npm init
```

Before to be able to install the module, you need to compile it.
<br>
To do that, this project use [node-gyp](https://github.com/nodejs/node-gyp) (a node.js module which works with python 2.7).
So be sure to install python 2.7 as well as the Visual C++ Build Environment (for windows, if it's your OS). 
<br>
Or follow the instructions listed here, to be sure to be able to use node-gyp as expected, depending on your OS specifications : [node-gyp instructions](https://github.com/nodejs/node-gyp#on-windows).
<br>

And finally, initialize a new node project and install the module :

```shell
npm install
```

Or you can directly install the module by using npm, if you already have a node.js project setted up :

```shell
npm install --save sc2api
```

## Documentation 

You will find all the documentation, with exemples, to quickly getting start in the [doc](https://github.com/Elkantor/sc2api/tree/master/doc) folder.
<br>
<blockquote>
<p><g-emoji class="g-emoji" alias="bulb" fallback-src="https://assets-cdn.github.com/images/icons/emoji/unicode/1f4a1.png" ios-version="6.0"><img class="emoji" alt="bulb" height="20" width="20" src="https://assets-cdn.github.com/images/icons/emoji/unicode/1f4a1.png"></g-emoji> [Warning] the documentation is currently under development, and will be available as soon as possible.
</p>
</blockquote>

For exemple, the [getting_start](https://github.com/Elkantor/sc2api/blob/master/doc/getting_start.md) file show you an exemple to quickly create a default bot (wich don't do anything, just sets up the parameters and launch the game with the default bot behavior).

## Developing

### Built With

* [nan](https://github.com/nodejs/nan) (native abstractions for node.js), to be able to use the v8 C++ engine by google, without worring about the versions of v8.
* [node-gyp](https://github.com/nodejs/node-gyp) for compiling C++ native addon modules for Node.js.
* [sc2client-api](https://github.com/Blizzard/s2client-api), the official C++ API by Blizzard, to create bot for Starcraft 2.

## Licensing

(The ISC License)

Copyright (C) 2018 - Victor Gallet <victor.gallet@hotmail.com>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
