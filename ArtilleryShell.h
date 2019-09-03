#pragma once


#include <GeometricPrimitive.h>
#include <SimpleMath.h>

#include "GameObject.h"


class ArtilleryShell :	public GameObject
{
	public:
		static const float MOVE_SPEED;
		static const float MAXIMUM_RANGE;


	private:
		std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
		DirectX::SimpleMath::Vector3                 m_velocity;
		DirectX::SimpleMath::Vector3                 m_origin;


	public:
		ArtilleryShell(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& azimuth);

	public:
		~ArtilleryShell();


	public:
		void Update(float elapsedTime) override;
		void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;
};
