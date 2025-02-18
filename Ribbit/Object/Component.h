#pragma once

namespace rib
{
	class GameObject;

	class Component
	{
	public:
		//--------------------------------------------------
		//    Constructor and Destructor
		//--------------------------------------------------
		explicit Component(GameObject& parent);
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;


		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		virtual void Start();
		virtual void Update() = 0;
		virtual void LateUpdate();
		virtual void FixedUpdate();
		virtual void Render()				const;


		//--------------------------------------------------
		//    Accessors & Mutators
		//--------------------------------------------------
		void FlagForDeletion();
		bool IsFlaggedForDeletion()			const;

		GameObject* GetParent() const;

	private:
		GameObject* m_pParent{};

		bool m_DeletionFlag{ false };
	};
}
