#include "keyboardScript.h"

#include "luaScript.h"
#include "corsairRGBKeyboard.h"
#include "corsairRGBKeyboardK70.h"

#include "utilities.h"

#include <Windows.h>


keyboardScript::keyboardScript(void)
{
	this->inErrorState = false;

	this->scriptInstance = std::shared_ptr<luaScript>(new luaScript(&keyboardScript::displayLUAError, static_cast<void*>(this)));

	this->scriptInstance->pushNumber("KEYBOARD_K70", KEYBOARD_K70);

	this->scriptInstance->pushNumber("INDICATOR_CAPSLOCK", INDICATOR_CAPSLOCK);
	this->scriptInstance->pushNumber("INDICATOR_NUMLOCK", INDICATOR_NUMLOCK);
	this->scriptInstance->pushNumber("INDICATOR_SCROLLOCK", INDICATOR_SCROLLOCK);

		this->scriptInstance->pushNumber("INDICATOR_STATE_OFF", INDICATOR_STATE_OFF);
	this->scriptInstance->pushNumber("INDICATOR_STATE_ON", INDICATOR_STATE_ON);

	this->scriptInstance->pushFunction("wait", LUA_EXPORT_GETNAME(lua_Wait)); //(milliseconds)
	this->scriptInstance->pushFunction("initializeKeyboard", LUA_EXPORT_GETNAME(lua_InitializeKeyboard)); //(keyboardType)
	this->scriptInstance->pushFunction("setKeyColor", LUA_EXPORT_GETNAME(lua_SetKeyColor)); //(key, r, g, b)
	this->scriptInstance->pushFunction("updateKeyboard", LUA_EXPORT_GETNAME(lua_UpdateKeyboard)); //()


	this->keyboardInstance = nullptr;
}


keyboardScript::~keyboardScript(void)
{
}

void keyboardScript::doFile(const wchar_t* fileName)
{
	this->scriptInstance->doFile(fileName);
}

/* MAIN LOOP */
void keyboardScript::doMainLoop()
{
	static int lastCapsState = -1;
	static int lastNumState = -1;
	static int lastScrollState = -1;

	this->fireEvent("onCreate");

	uint32_t lastLoopFireTime = 0;
	while (!this->inErrorState)
	{
		auto startTime = timeGetHighResTime();
		auto nowTime = startTime;

		this->fireEvent("onTimer", startTime, lastLoopFireTime);
		lastLoopFireTime = startTime;

		startTime = timeGetHighResTime();

		
		/* check for events for the next 200 MS */
		do
		{
			/* check indicator states */
			int capsState = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) ? INDICATOR_STATE_ON : INDICATOR_STATE_OFF;
			int numState = ((GetKeyState(VK_NUMLOCK) & 0x0001) != 0) ? INDICATOR_STATE_ON : INDICATOR_STATE_OFF;
			int scrollState = ((GetKeyState(VK_SCROLL) & 0x0001) != 0) ? INDICATOR_STATE_ON : INDICATOR_STATE_OFF;

			if (capsState != lastCapsState)
				this->fireEvent("onIndicatorStateChange", INDICATOR_CAPSLOCK, capsState);
			if (numState != lastNumState)
				this->fireEvent("onIndicatorStateChange", INDICATOR_NUMLOCK, numState);
			if (scrollState != lastScrollState)
				this->fireEvent("onIndicatorStateChange", INDICATOR_SCROLLOCK, scrollState);

			lastCapsState = capsState;
			lastNumState = numState;
			lastScrollState = scrollState;

			/* something else might go here */

			/* wait a tiny bit before repeating */
			Sleep(10);


			nowTime = timeGetHighResTime();
		} while (nowTime - startTime < 100);
	}
}

void keyboardScript::fireEvent(const char* eventHandler, std::vector<int> arguments)
{
	this->scriptInstance->beginExecuteFunction(eventHandler);
	int argCount = arguments.size();
	for (int i = 0; i < argCount; i++)
		this->scriptInstance->pushFunctionArg(arguments[i]);
	this->scriptInstance->endExecuteFunction(argCount, 0);
}


/* EXPORTED LUA FUNCTIONS */
int keyboardScript::lua_Wait(lua_State* L)
{
	if (!verifyParameters(L, "lua_Wait", 1))
		return 1;

	auto time = keyboardScript::getIntegerParameter(L, 1);
	Sleep(time);
	lua_pushboolean(L, true);
	return 1;
}

int keyboardScript::lua_InitializeKeyboard(lua_State* L)
{
	if (!verifyParameters(L, "lua_InitializeKeyboard", 1))
		return 1;

	auto type = keyboardScript::getIntegerParameter(L, 1);

	switch (type)
	{
		case KEYBOARD_K70:
			this->keyboardInstance = std::shared_ptr<corsairRGBKeyboard>(new corsairRGBKeyboardK70());
			break;
		default:
			break;
	}
		
	lua_pushboolean(L, this->keyboardInstance != nullptr && this->keyboardInstance->isValid());
	return 1;
}

int keyboardScript::lua_SetKeyColor(lua_State* L)
{
	if (!verifyParameters(L, "lua_SetKeyColor", 4))
		return 1;

	auto key = keyboardScript::getIntegerParameter(L, 1);
	auto r = keyboardScript::getIntegerParameter(L, 2);
	auto g = keyboardScript::getIntegerParameter(L, 3);
	auto b = keyboardScript::getIntegerParameter(L, 4);

	if (this->keyboardInstance != nullptr)
	{
		auto ret = this->keyboardInstance->setKey((uint8_t)key, (uint8_t)r, (uint8_t)g, (uint8_t)b);
		lua_pushboolean(L, ret);
	}
	else
		lua_pushboolean(L, false);

	return 1;
}

int keyboardScript::lua_UpdateKeyboard(lua_State* L)
{
	if (!verifyParameters(L, "lua_UpdateKeyboard", 0))
		return 1;

	if (this->keyboardInstance != nullptr)
	{
		this->keyboardInstance->updateKeyboard();
		lua_pushboolean(L, true);
	}
	else
		lua_pushboolean(L, false);

	return 1;
}


/* UTILITY STUFF */
void keyboardScript::displayLUAError(char* error, lua_State* L)
{
	printf("Lua error: %s\n", error);
	getInstanceFromLuaState(L)->inErrorState = true;
}

keyboardScript* keyboardScript::getInstanceFromLuaState(lua_State *L)
{
	return luaScript::getInstance(L)->getExtraData<keyboardScript*>();
}

bool keyboardScript::verifyParameters(lua_State *L, const char* functionName, int argCount)
{
	if (lua_gettop(L) != argCount)
	{
		printf("Invalid number of parameters passed to %s! Expected %d, got %d\n", argCount, lua_gettop(L));
		lua_pushboolean(L, false);
		return false;
	}
	return true;
}

int keyboardScript::getIntegerParameter(lua_State *L, int stackIndex)
{
	if (lua_isstring(L, stackIndex))
		return atoi(lua_tostring(L, stackIndex));
	else
		return lua_tonumber(L, stackIndex);
}
std::string keyboardScript::getStringParameter(lua_State *L, int stackIndex)
{
	if (lua_isstring(L, stackIndex))
	{
		const char* ret = lua_tostring(L, stackIndex);
		if (ret)
			return std::string(ret);
		else
			return "";
	}
	else
		return std::to_string((long long)lua_tonumber(L, stackIndex));
}