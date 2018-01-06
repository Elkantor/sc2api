var sc2api = null;

if (process.env.DEBUG) {
  sc2api = require('./build/Debug/sc2api.node');
} else {
  sc2api = require('./build/Release/sc2api.node');
}

module.exports = sc2api;
