#pragma once
class EffectCard : public Card
{
public:
	EffectCard(SDL_Renderer* renderer, int index, Empire empire);
	~EffectCard();
	void setUnEffect(bool unEffect);
	bool isUnEffect();
	Effect getEffect();
private:
	Effect effect;
	bool unEffect;
};

