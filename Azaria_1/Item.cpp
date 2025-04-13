#include "stdafx.h"
#include "Item.h"

void Item::InitVariables()
{

}

Item::Item(unsigned level, unsigned value)
{
	this->InitVariables();

	this->level = level;
	this->value = value;
	this->type = ItemTypes::IT_DEFAULT;
}

Item::~Item()
{
}
