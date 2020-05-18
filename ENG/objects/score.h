class ScoreBoard {
public:
	std::vector<std::pair<std::string,int>> scores;

	void UpdateScore(std::string name,int d){
		for(auto s: ScoreBoard)
			if (s.first ==name) s.second += d;
	}
};