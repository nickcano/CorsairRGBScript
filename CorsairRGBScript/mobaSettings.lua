--[[
	This script will give the keyboard a blue background with highlights on important MOBA keys

	When a lock key (caps, num, scroll) is toggled, that key's light will be changed:
		Toggled on: green
		Toggle off: no light

	The light of the winlock and brightness buttons will be used to make the state of caps and num lock even more obvious
]]


function onCreate()
	if (not initializeKeyboard(KEYBOARD_K70)) then
		error("Failed to initialize keyboard!")
	end

	--make all keys blue
	for i = 1, 144 do
		setKeyColor(i - 1, 0, 170, 255)
	end

	setKeyGroupColor("moba_all", 255, 0, 0) --highlight MOBA ability keys
	setKeyGroupColor("numrow_1_6", 255, 255, 255) --highlight MOBA item keys

	setKeyColor(KEYMAP["space"], 255, 255, 255) --highlight space bar

	setKeyGroupColor("fkeys_even", 170, 0, 255) --stagger fkeys so it looks interesting
	setKeyGroupColor("fkeys_odd", 170, 0, 127) --stagger fkeys so it looks interesting

	setKeyGroupColor("modifiers", 190, 85, 0) --give modifiers a unique orage color

	setKeyGroupColor("arrows_vert", 255, 255, 255) --stripe arrow keys
	setKeyGroupColor("arrows_horiz", 255, 0, 0) --stripe arrow keys

	setKeyGroupColor("navblock_sides", 255, 255, 255) --stripe nav keys
	setKeyGroupColor("navblock_center", 255, 0, 0) --stripe nav keys

	setKeyGroupColor("mediarow", 255, 255, 0) --yellow media keys

	--corners of number pad
	setKeyColor(KEYMAP["numpad1"], 255, 0, 0)
	setKeyColor(KEYMAP["numpad3"], 255, 0, 0)
	setKeyColor(KEYMAP["numpad7"], 255, 0, 0)
	setKeyColor(KEYMAP["numpad9"], 255, 0, 0)


	if (not updateKeyboard()) then
		error("Failed to update keyboard!")
	end
end

function onIndicatorStateChange(type, state)
	-- only time we update is when an indicator key is changed
	local keyToChange = INDICATOR_KEYMAP[type]
	local anotherKeyToChange = SECONDARY_INDICATOR_KEYMAP[type]

	if (state == INDICATOR_STATE_ON) then
		setKeyColor(keyToChange, 0, 255, 0)
		if (anotherKeyToChange ~= nil) then
			setKeyColor(anotherKeyToChange, 0, 170, 255)
		end
	else
		setKeyColor(keyToChange, 0, 0, 0)
		if (anotherKeyToChange ~= nil) then
			setKeyColor(anotherKeyToChange, 0, 0, 0)
		end
	end

	if (not updateKeyboard()) then
		error("Failed to update keyboard!")
	end
end

function onTimer(ticks, lastTicks) end