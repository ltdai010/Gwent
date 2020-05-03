#pragma once
class Side
{
public:
	Side(SDL_Renderer* renderer, Faction faction);
	~Side();
	void initRole();
	void initScoreText(SDL_Renderer* renderer, Faction faction);
	void updateScore(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);
	Role* getRole(Lane lane);
	int totalDamage(Role* role);
	int totalMaxDamage(Role* role);
	void clearBuff();
	void doubleDamage(Role* role);
	void clearEffect();
private:
	Role* melee;
	Role* range;
	Role* siege;
	Score* melee_score;
	Score* range_score;
	Score* siege_score;
	Faction faction;
};

