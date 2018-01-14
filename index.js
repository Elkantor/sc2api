// this is how we will require our module
const sc2 = require('./binding.js')

const coordinator = new sc2.SC2Coordinator();

var settings={
    path_exe: "D:\\StarCraft II\\Versions\\Base60321\\SC2.exe",
    realtime: true,
    map: "D:\\Projects\\SC2API\\maps\\Ladder\\(2)Bel'ShirVestigeLE (Void).SC2Map"
}

coordinator.loadSettings(settings);

function onGameStart(){
    console.log("the game is started");
}

var agent_test = new sc2.SC2Agent();

agent_test.onGameStart = onGameStart;

var player = {
    type: "Participant",
    race: "Protoss",
    difficulty: "Easy"
}

var player_setup = new sc2.SC2PlayerSetup(player);
player_setup.setAgent(agent_test);

var player_setup2 = new sc2.SC2PlayerSetup({
    type: "Computer",
    race: "Zerg",
    difficulty: "Easy"
});

coordinator.participants = [player_setup, player_setup2];
coordinator.launchStarcraft();

function loopGame(error, result){
    return coordinator.update(loopGame);
}

coordinator.update(loopGame);