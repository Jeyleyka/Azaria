#pragma once

enum SwordTypesStates {NON, COM, FR};

class SwordStates
{
private:
	unsigned short type;

public:
	SwordStates(unsigned short type = SwordTypesStates::NON);
	~SwordStates();

	const unsigned short& GetType() const;
	void SetType(unsigned short type);
};

