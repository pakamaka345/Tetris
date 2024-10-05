#pragma once
#include <vector>
#include <string>

class Scene
{
public:
	virtual void run() = 0;
	virtual ~Scene() = default;
	Scene(std::string title) : MenuTitle(title) {}

protected:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void handleEvents() = 0;

protected:
	std::string MenuTitle;
};

