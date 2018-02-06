# Getting Start with sc2api

First, add this following line to require the module :

```js
// this is how we will require our module
const sc2 = require('./binding.js')
```

Next, you'll need to create a Coordinator object, which handles all the different settings to launch the game (like the executable path of the game for exemple).

```js
const coordinator = new sc2.SC2Coordinator();
```

Then, you can define the settings in a js object, and pass it to the coordinator :
<blockquote>
<p><g-emoji class="g-emoji" alias="bulb" fallback-src="https://assets-cdn.github.com/images/icons/emoji/unicode/1f4a1.png" ios-version="6.0"><img class="emoji" alt="bulb" height="20" width="20" src="https://assets-cdn.github.com/images/icons/emoji/unicode/1f4a1.png"></g-emoji> Just like the official Starcraft 2 C++ API, this repository only comes with a few maps for testing. Additional maps and replays can be found <a href="https://github.com/Blizzard/s2client-proto#downloads">here</a>.
</p>
</blockquote>
```js
var settings={
    path_exe: "D:\\StarCraft II\\Versions\\Base60321\\SC2.exe", // the path of your Starcraft 2 executable file
    realtime: true, // if the game should be play in realtime (true) or in the fast mode (false)
    map: "D:\\Projects\\SC2API\\maps\\Ladder\\(2)Bel'ShirVestigeLE (Void).SC2Map" // the map which you want to launch to test your bot
}

coordinator.loadSettings(settings);
```
