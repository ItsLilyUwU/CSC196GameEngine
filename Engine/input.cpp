#include "input.h"
#include <SDL.h>

bool Input::Initialize()
{
	int numKeys;
	const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);

	m_keyboardState.resize(numKeys);

	std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());

	m_prevKeyboardState = m_keyboardState;

	return true;
}

void Input::Shutdown()
{

}

void Input::Update()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	// keyboard input
	m_prevKeyboardState = m_keyboardState;
	const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
	std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

	int x, y;
	int32_t buttonState = SDL_GetMouseState(&x, &y);

	m_mousePos.x = (float)x;
	m_mousePos.y = (float)y;

	// 000 <- button state                   // 001 <- button state
	// 001 <- button mask                    // 001 <- button mask
	// 000 (Set to false if both aren't 1)   // 001
	m_prevMouseButtonState = m_mouseButtonState;

	m_mouseButtonState[0] = buttonState & SDL_BUTTON_LMASK;
	m_mouseButtonState[1] = buttonState & SDL_BUTTON_MMASK;
	m_mouseButtonState[2] = buttonState & SDL_BUTTON_RMASK;
}
