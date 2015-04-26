--[[
	This script will give the keyboard alternating rows of red and blue.
	When a lock key (caps, num, scroll) is toggled, that key's light will be changed:
		Toggled on: green
		Toggle off: no light
]]


dofile("library.lua")


function onCreate()
	if (not initializeKeyboard(KEYBOARD_K70)) then
		error("Failed to initialize keyboard!")
	end

	-- since it's a solid pattern, we only need to do it once
	for i = 1, 144 do
		local section = i % 2
		if (section == 0) then
			setKeyColor(i - 1, 255, 0, 0)
		elseif (section == 1) then
			setKeyColor(i - 1, 45, 45, 255)
		end
	end

	if (not updateKeyboard()) then
		error("Failed to update keyboard!")
	end
end

function onIndicatorStateChange(type, state)
	-- only time we update is when an indicator key is changed
	local keyToChange = INDICATOR_KEYMAP[type]

	if (state == INDICATOR_STATE_ON) then
		setKeyColor(keyToChange, 0, 255, 0)
	else
		setKeyColor(keyToChange, 0, 0, 0)
	end

	if (not updateKeyboard()) then
		error("Failed to update keyboard!")
	end
end

function onTimer(ticks, lastTicks) end