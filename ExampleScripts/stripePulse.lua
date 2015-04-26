--[[
	This script will give the keyboard alternating rows of red, green, and blue.
	The color will pulse in intesifty, fading between a weak glow and maximum brightness.
]]

function onCreate()
	if (not initializeKeyboard(KEYBOARD_K70)) then
		error("Failed to initialize keyboard!")
	end
end

function onIndicatorStateChange(type, state) end

function onTimer(ticks, lastTicks) --this is called roughly once every 100 MS

	local grade = (ticks / 10 % 400)
	if (grade > 200) then
		grade = 200 - (grade - 200)
	end

	grade = grade + 56
	
	for i = 1, 144 do
		local section = i % 3
		if (section == 0) then
			setKeyColor(i - 1, grade, 0, 0)
		elseif (section == 1) then
			setKeyColor(i - 1, 0, grade, 0)
		elseif (section == 2) then
			setKeyColor(i - 1, 0, 0, grade)
		end
	end

	if (not updateKeyboard()) then
		error("Failed to update keyboard!")
	end
end