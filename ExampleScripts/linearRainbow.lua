--[[
	This script will make a gentle rainbow neatly scroll across the keyboard.
]]


function onCreate()
	if (not initializeKeyboard(KEYBOARD_K70)) then
		error("Failed to initialize keyboard!")
	end
end

function onIndicatorStateChange(type, state) end

function onTimer(ticks, lastTicks) --this is called roughly once every 200 MS
	for i = 1, 144 do
		local idx = i + ticks / 10

		local c1 = ((idx * 5) % 230) + 25
		local c2 = ((idx * 2) % 200) + 55
		local c3 = idx + 50
		setKeyColor(i - 1, c1, c2, c3)
	end

	if (not updateKeyboard()) then
		error("Failed to update keyboard!")
	end
end