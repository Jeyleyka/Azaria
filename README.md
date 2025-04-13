# Azaria
**Azaria** - the game based on the prototype of Suraj Sharma's game with the addition of my own ideas and sequels, a game where you can create your own map and play for points fighting off enemies or go through a campaign

**Original game template** - [Suraj Sharma](https://github.com/SurajSharma90/SFML_RPG)
___

The large project combining the standard library **STL** and **SFML** and their features

for the game to work you need to have the minimum elements of SFML such as **audio**, **graphics**, **network**, **system**, **window** and also **cmake** files

The project uses **Multithreading** to separate tasks in order to speed up the game

``` cpp
    if (this->buySwordsmen)
    {
        std::thread swThread([&]() {swordsmen->Update(dt, mousePosView, view); });
        swThread.join();
        
        this->swordsmen->Update(dt, this->mousePosView, this->view);
    }

    // When an assistant appears, a separate thread is created to update its tasks
```

Using STL containers like **Deque** and **Stack**

``` cpp
if (this->buttons["CAMPANY_STATE"]->IsPressed())
{
	this->states->push(new LevelsState(this->stateData, this->loadLevel));

	if (this->player->GetNewWeapon())
	{
		this->states->top()->EndState();
		delete this->states->top();
		this->states->push(new LevelsState(this->stateData, this->loadLevel + 1));
	}
}
```

Animation playback system:
``` cpp
const bool& AnimationComponent::Play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation) //If there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If the priority animation is done, remove it
			if (this->animations[key]->Play(dt, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->Play(dt, abs(modifier / modifier_max));
	}

	return this->animations[key]->IsDone();
}
```

enemy auto-targeting system:
``` cpp
void AIFollow::Update(const float& dt)
{
	sf::Vector2f moveVec;
	bool isMoving = true;

	moveVec.x = entity.GetPosition().x - self.GetPosition().x;
	moveVec.y = entity.GetPosition().y - self.GetPosition().y;

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

	moveVec /= vecLength;

	if (self.GetPosition().x != entity.GetPosition().x && isMoving)
		self.Move(moveVec.x, moveVec.y, dt);
}
```
___
**This game was not originally created for playing, but for practical use of the above methods.**