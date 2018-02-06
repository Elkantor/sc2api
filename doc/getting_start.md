# Getting Start with sc2api

First, add this following line to require the module :

```js
// this is how we will require our module
const sc2 = require('./binding.js')
```

Next, you'll need to create a Coordinator object, which handles all the different settings to launch the game

```js
const coordinator = new sc2.SC2Coordinator();
```
