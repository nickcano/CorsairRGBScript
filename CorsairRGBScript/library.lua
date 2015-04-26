--[[
	This is just a library that defines key maps, keys groups, and useful functions
]]


KEYMAP = {}
KEYMAP["f1"] = 0x0C
KEYMAP["f2"] = 0x18
KEYMAP["f3"] = 0x24
KEYMAP["f4"] = 0x30
KEYMAP["f5"] = 0x3C
KEYMAP["f6"] = 0x48
KEYMAP["f7"] = 0x54
KEYMAP["f8"] = 0x60
KEYMAP["f9"] = 0x6C
KEYMAP["f10"] = 0x78
KEYMAP["f11"] = 0x84
KEYMAP["f12"] = 0x06
KEYMAP["num0"] = 0x79
KEYMAP["num1"] = 0x0D
KEYMAP["num2"] = 0x19
KEYMAP["num3"] = 0x25
KEYMAP["num4"] = 0x31
KEYMAP["num5"] = 0x3D
KEYMAP["num6"] = 0x49
KEYMAP["num7"] = 0x55
KEYMAP["num8"] = 0x61
KEYMAP["num9"] = 0x6D
KEYMAP["minus"] = 0x85
KEYMAP["equals"] = 0x07
KEYMAP["numpad0"] = 0x81
KEYMAP["numpad1"] = 0x5D
KEYMAP["numpad2"] = 0x69
KEYMAP["numpad3"] = 0x75
KEYMAP["numpad4"] = 0x39
KEYMAP["numpad5"] = 0x45
KEYMAP["numpad7"] = 0x09
KEYMAP["numpad6"] = 0x51
KEYMAP["numpad8"] = 0x15
KEYMAP["numpad9"] = 0x21
KEYMAP["numlock"] = 0x50
KEYMAP["numpaddivide"] = 0x5C
KEYMAP["numpadmultiply"] = 0x68
KEYMAP["numpadminus"] = 0x74
KEYMAP["numpadplus"] = 0x80
KEYMAP["numpadenter"] = 0x8C
KEYMAP["numpaddecimal"] = 0x8D
KEYMAP["a"] = 0x0F
KEYMAP["b"] = 0x4C
KEYMAP["c"] = 0x34
KEYMAP["d"] = 0x27
KEYMAP["e"] = 0x26
KEYMAP["f"] = 0x33
KEYMAP["g"] = 0x3F
KEYMAP["h"] = 0x4B
KEYMAP["i"] = 0x62
KEYMAP["j"] = 0x57
KEYMAP["k"] = 0x63
KEYMAP["l"] = 0x6F
KEYMAP["m"] = 0x64
KEYMAP["n"] = 0x58
KEYMAP["o"] = 0x6E
KEYMAP["p"] = 0x7A
KEYMAP["q"] = 0x0E
KEYMAP["r"] = 0x32
KEYMAP["s"] = 0x1B
KEYMAP["t"] = 0x3E
KEYMAP["u"] = 0x56
KEYMAP["v"] = 0x40
KEYMAP["w"] = 0x1A
KEYMAP["x"] = 0x28
KEYMAP["y"] = 0x4A
KEYMAP["z"] = 0x1C
KEYMAP["arrowup"] = 0x67
KEYMAP["arrowdown"] = 0x7F
KEYMAP["arrowleft"] = 0x73
KEYMAP["arrowright"] = 0x8B
KEYMAP["mediastop"] = 0x20
KEYMAP["mediaprev"] = 0x2C
KEYMAP["mediaplaypause"] = 0x38
KEYMAP["medianext"] = 0x44
KEYMAP["mute"] = 0x14
KEYMAP["delete"] = 0x2B
KEYMAP["insert"] = 0x36
KEYMAP["end"] = 0x37
KEYMAP["home"] = 0x42
KEYMAP["pagedown"] = 0x43
KEYMAP["pageup"] = 0x4E
KEYMAP["lshift"] = 0x04
KEYMAP["rshift"] = 0x4F
KEYMAP["lctrl"] = 0x05
KEYMAP["rctrl"] = 0x5B
KEYMAP["backslash"] = 0x66
KEYMAP["forwardslash"] = 0x88
KEYMAP["lwinkey"] = 0x11
KEYMAP["rwinkey"] = 0x65
KEYMAP["alt"] = 0x1D
KEYMAP["altgr"] = 0x59
KEYMAP["rsquare"] = 0x5A
KEYMAP["lsquare"] = 0x86
KEYMAP["printscreen"] = 0x12
KEYMAP["scrolllock"] = 0x1E
KEYMAP["pausebreak"] = 0x2A
KEYMAP["winlock"] = 0x08
KEYMAP["brightness"] = 0x89
KEYMAP["comma"] = 0x70
KEYMAP["period"] = 0x7C
KEYMAP["hash"] = 0x72
KEYMAP["semicolon"] = 0x7B
KEYMAP["escape"] = 0x0
KEYMAP["grave"] = 0x01
KEYMAP["tab"] = 0x02
KEYMAP["capslock"] = 0x03
KEYMAP["backspace"] = 0x1F
KEYMAP["enter"] = 0x7E
KEYMAP["space"] = 0x35
KEYMAP["contextmenu"] = 0x71
KEYMAP["apostrophe"] = 0x87
KEYMAP["macrorecord"] = 0x0b
KEYMAP["macrorecord1"] = 0x17
KEYMAP["macrorecord2"] = 0x23
KEYMAP["macrorecord3"] = 0x2f
KEYMAP["g1"] = 0x0a
KEYMAP["g2"] = 0x16
KEYMAP["g3"] = 0x22
KEYMAP["g4"] = 0x2e
KEYMAP["g5"] = 0x3a
KEYMAP["g6"] = 0x46
KEYMAP["g7"] = 0x52
KEYMAP["g8"] = 0x5e
KEYMAP["g9"] = 0x6a
KEYMAP["g10"] = 0x76
KEYMAP["g11"] = 0x3b
KEYMAP["g12"] = 0x47
KEYMAP["g13"] = 0x53
KEYMAP["g14"] = 0x5f
KEYMAP["g15"] = 0x6b
KEYMAP["g16"] = 0x77
KEYMAP["g17"] = 0x83
KEYMAP["g18"] = 0x8f


INDICATOR_KEYMAP = 
{
	[INDICATOR_CAPSLOCK] = KEYMAP["capslock"],
	[INDICATOR_NUMLOCK] = KEYMAP["numlock"],
	[INDICATOR_SCROLLOCK] = KEYMAP["scrolllock"]
}

SECONDARY_INDICATOR_KEYMAP = 
{
	[INDICATOR_CAPSLOCK] = KEYMAP["winlock"],
	[INDICATOR_NUMLOCK] = KEYMAP["brightness"]
}


GROUP_KEYMAP =
{
	["wasd"] = {KEYMAP["w"], KEYMAP["a"], KEYMAP["s"], KEYMAP["d"]},

	["numrow_full"] = {KEYMAP["num1"], KEYMAP["num2"], KEYMAP["num3"], KEYMAP["num4"], KEYMAP["num5"], KEYMAP["num6"], KEYMAP["num7"], KEYMAP["num8"], KEYMAP["num9"], KEYMAP["num0"]},
	["numrow_1_6"] = {KEYMAP["num1"], KEYMAP["num2"], KEYMAP["num3"], KEYMAP["num4"], KEYMAP["num5"], KEYMAP["num6"]},
	["numrow_7_0"] = {KEYMAP["num7"], KEYMAP["num8"], KEYMAP["num9"], KEYMAP["num0"]},

	["moba_all"] = {KEYMAP["q"], KEYMAP["w"], KEYMAP["e"], KEYMAP["r"], KEYMAP["d"], KEYMAP["f"]},
	["moba_small"] = {KEYMAP["q"], KEYMAP["w"], KEYMAP["e"], KEYMAP["r"]},

	["arrows"] = {KEYMAP["arrowup"], KEYMAP["arrowdown"], KEYMAP["arrowleft"], KEYMAP["arrowright"]},
	["arrows_vert"] = {KEYMAP["arrowup"], KEYMAP["arrowdown"]},
	["arrows_horiz"] = {KEYMAP["arrowleft"], KEYMAP["arrowright"]},

	["fkeys"] = {KEYMAP["f1"], KEYMAP["f2"], KEYMAP["f3"], KEYMAP["f4"], KEYMAP["f5"], KEYMAP["f6"], KEYMAP["f7"], KEYMAP["f8"], KEYMAP["f9"], KEYMAP["f10"], KEYMAP["f11"], KEYMAP["f12"]},
	["fkeys_even"] = {KEYMAP["f2"], KEYMAP["f4"], KEYMAP["f6"], KEYMAP["f8"], KEYMAP["f10"], KEYMAP["f12"]},
	["fkeys_odd"] = {KEYMAP["f1"], KEYMAP["f3"], KEYMAP["f5"], KEYMAP["f7"], KEYMAP["f9"], KEYMAP["f11"]},

	["modifiers"] = {KEYMAP["lshift"], KEYMAP["rshift"], KEYMAP["lctrl"], KEYMAP["rctrl"], KEYMAP["lwinkey"], KEYMAP["rwinkey"], KEYMAP["alt"], KEYMAP["altgr"]},
	["modifiers_left"] = {KEYMAP["lshift"], KEYMAP["lctrl"], KEYMAP["lwinkey"], KEYMAP["alt"]},
	["modifiers_right"] = {KEYMAP["rshift"], KEYMAP["rctrl"], KEYMAP["rwinkey"], KEYMAP["altgr"]},

	["navblock"] = {KEYMAP["insert"], KEYMAP["home"], KEYMAP["pageup"], KEYMAP["delete"], KEYMAP["end"], KEYMAP["pagedown"]},
	["navblock_top"] = {KEYMAP["insert"], KEYMAP["home"], KEYMAP["pageup"]},
	["navblock_bottom"] = {KEYMAP["delete"], KEYMAP["end"], KEYMAP["pagedown"]},
	["navblock_sides"] = {KEYMAP["insert"], KEYMAP["pageup"], KEYMAP["delete"], KEYMAP["pagedown"]},
	["navblock_center"] = {KEYMAP["home"], KEYMAP["end"]},

	["mediarow"] = {KEYMAP["mediastop"], KEYMAP["mediaprev"], KEYMAP["mediaplaypause"], KEYMAP["medianext"], KEYMAP["mute"]}
}


function setKeyGroupColor(groupName, r, g, b)
	local keys = GROUP_KEYMAP[groupName]
	if (keys == nil or not keys) then return false end

	for _, key in ipairs(keys) do
		setKeyColor(key, r, g, b)
	end

	return true
end