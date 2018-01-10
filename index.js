// this is how we will require our module
const sc2 = require('./binding.js')

const vec1 = new sc2.SC2Coordinator()

var settings={
    path_exe: "D:\\StarCraft II\\Versions\\Base60321\\SC2.exe",
    realtime: true,
    //map: "D:\\Projects\\SC2API\\maps\\Ladder\\(2)Bel'ShirVestigeLE (Void).SC2Map"
}
// var result = vec1.loadSettings(settings);

function isFoo(str){
    return str === 'foo';
}

var agent_test = new sc2.SC2Agent();
agent_test.onGameStart = isFoo;
console.log("done");

var player = {
    type: "Participant",
    race: "Terran",
    difficulty: "Easy"
}
var player_setup = new sc2.SC2PlayerSetup(player);
player_setup.setAgent(agent_test);
console.log(player_setup);
console.log("done");

