#include "SwordStates.h"

SwordStates::SwordStates(unsigned short type)
{
   this->type = type;
}

SwordStates::~SwordStates()
{
}

const unsigned short& SwordStates::GetType() const
{
   return this->type;
}

void SwordStates::SetType(unsigned short type)
{
   this->type = type;
}
