#pragma once

#include "tests/Test.h"

namespace test {
	class TestClearColor: public Test
	{
	private:
		float m_ClearColor[4];
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}
