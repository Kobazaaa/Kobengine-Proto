#include "IntUIComponent.h"
#include <iostream>
#include "TextRendererComponent.h"

//--------------------------------------------------
//    Constructor
//--------------------------------------------------
kob::IntUIComponent::IntUIComponent(GameObject& parent, const std::string& prefix, int initialValue, const std::string& postfix, Event<int>& listenEvent)
	: Component(parent)
	, m_Prefix(prefix)
	, m_Postfix(postfix)
{
	// Get
	m_pTextRenderer = parent.GetComponent<TextRendererComponent>();
	if (!m_pTextRenderer)
		std::cerr << "An Int UI Component needs the parent to have a TextRenderer Component!\n";

	OnValueChange(initialValue);
	listenEvent += &m_pEventCallback;
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::IntUIComponent::Update()
{}


//--------------------------------------------------
//    Event
//--------------------------------------------------
void kob::IntUIComponent::OnValueChange(int value) const
{
	if (!m_pTextRenderer) return;

	std::stringstream newTxt;
	newTxt << m_Prefix;
	newTxt << std::to_string(value);
	newTxt << m_Postfix;
	m_pTextRenderer->SetText(newTxt.str());
}
