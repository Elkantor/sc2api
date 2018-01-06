// this is how we will require our module
const sc2 = require('./binding.js')

const vec1 = new sc2.SC2Coordinator(20, 10, 0)

var settings={
    path_exe: "D:\\StarCraft II\\Versions\\Base60321\\SC2.exe",
    realtime: true,
    //map: "D:\\Projects\\SC2API\\maps\\Ladder\\(2)Bel'ShirVestigeLE (Void).SC2Map"
}
// var result = vec1.loadSettings(settings);
var agent = new sc2.SC2Agent(2);
var player = {
    type: "Participant",
    race: "Terran",
    difficulty: "Easy"
}
var player_setup = new sc2.SC2PlayerSetup(player, agent);
console.log(player_setup);