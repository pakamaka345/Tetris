#pragma once

namespace Command
{
	enum class ID
	{
		MoveLeft,
		MoveRight,
		RotateClockwise,
		RotateCounterClockwise,
		Drop,
		Quit,
		Invalid,
		count
	};
}