{
  "targets":
  [
    {
      "target_name": "sc2api",
      "include_dirs" : [
        "include",
        "src/public",
        "<!(node -e \"require('nan')\")"
      ],
      "sources": [
        "src/index.cc",
        "src/private/coordinator.cc",
        "src/private/agent.cc",
        "src/private/player_setup.cc",
        "src/private/bot.cc"
      ],
      "link_settings":
      {
        "libraries" : [
          "\"<(module_root_dir)\\lib\\civetweb.lib\"",
          "\"<(module_root_dir)\\lib\\libprotobuf.lib\"",
          "\"<(module_root_dir)\\lib\\libprotobufd.lib\"",
          "\"<(module_root_dir)\\lib\\sc2api.lib\"",
          "\"<(module_root_dir)\\lib\\sc2apid.lib\"",
          "\"<(module_root_dir)\\lib\\sc2lib.lib\"",
          "\"<(module_root_dir)\\lib\\sc2libd.lib\"",
          "\"<(module_root_dir)\\lib\\sc2protocol.lib\"",
          "\"<(module_root_dir)\\lib\\sc2protocold.lib\"",
          "\"<(module_root_dir)\\lib\\sc2renderer.lib\"",
          "\"<(module_root_dir)\\lib\\sc2rendererd.lib\"",
          "\"<(module_root_dir)\\lib\\sc2utils.lib\"",
          "\"<(module_root_dir)\\lib\\sc2utilsd.lib\""
        ]
      }
    }
  ]
}

