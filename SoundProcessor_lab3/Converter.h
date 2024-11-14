#include <vector>

class Converter {
public:
	virtual ~Converter() = default;

	virtual std::vector<int16_t> process(const std::vector<int16_t>& input) = 0;


};

class MuteConverter: public Converter {
public:
	MuteConverter(int start, int end);
	std::vector<int16_t> process(const std::vector<int16_t>& input) override;
private: int start, end;
};