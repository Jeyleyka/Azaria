#include "stdafx.h"
#include "EditorMode.h"

EditorMode::EditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData)
	: stateData(stateData), tileMap(tileMap), editorStateData(editorStateData)
{

}

EditorMode::~EditorMode()
{
}

// Functions
const bool EditorMode::GetKeytime()
{
	if (*this->editorStateData->keytime >= *this->editorStateData->keytimeMax)
	{
		*this->editorStateData->keytime = 0.f;
		return true;
	}

	return false;
}
