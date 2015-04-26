--[[
	This script will make a rainbow-like wave swim though the keyboard. It looks sexy.
]]

function onCreate()
	if (not initializeKeyboard(KEYBOARD_K70)) then
		error("Failed to initialize keyboard!")
	end
end

function onIndicatorStateChange(type, state) end

function onTimer(ticks, lastTicks) --this is called roughly once every 200 MS
	for i = 1, 144 do
		local c1 = (((i * 5) % 230) + 25) + ticks / 10
		local c2 = (((i * 2) % 200) + 55) + ticks / 10
		local c3 = (i + 50) + ticks / 10
		setKeyColor(i - 1, c1 % 256, c2 % 256, c3 % 256)
	end

	if (not updateKeyboard()) then
		error("Failed to update keyboard!")
	end
end