#include <iostream>
#include <limits>
#include <cmath>
#include <vector>

class IStatistics
{
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char *name() const = 0;
};

class Min : public IStatistics
{
public:
	Min() : m_min{std::numeric_limits<double>::min()}
	{
	}

	virtual void update(double next) override
	{
		if (next < m_min)
			m_min = next;
	}

	virtual double eval() const override
	{
		return m_min;
	}

	virtual const char *name() const override
	{
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics
{
public:
	Max() : m_max{std::numeric_limits<double>::max()}
	{
	}

	virtual void update(double next) override
	{
		if (next > m_max)
			m_max = next;
	}
	virtual double eval() const override
	{
		return m_max;
	}
	virtual const char *name() const override
	{
		return "max";
	}

private:
	double m_max;
};

class Mean : public IStatistics
{
public:
	Mean() : sum{0}, quantity{0}
	{
	}

	virtual void update(double next) override
	{
		sum += next;
		quantity++;
	}
	virtual double eval() const override
	{
		return sum / quantity;
	}
	virtual const char *name() const override
	{
		return "sum";
	}

private:
	double sum;
	int quantity;
};

class Std : public IStatistics
{
public:
	Std() : std_sum{0}
	{
	}

	virtual void update(double next) override
	{
		std_sum += next;
		sequence.push_back(next);
	}
	virtual double eval() const override
	{
		double average = std_sum / sequence.size();
		double sigma;
		for (double el : sequence)
		{
			sigma += std::pow((el - average), 2) / sequence.size();
		}
		delete &sequence;
		return std::sqrt(sigma);
	}
	virtual const char *name() const override
	{
		return "Std";
	}

private:
	double std_sum;
	std::vector<double> sequence;
};

int main()
{
	const size_t statistics_count = 4;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};

	double val = 0;
	while (std::cin >> val)
	{
		for (size_t i = 0; i < statistics_count; ++i)
		{
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good())
	{
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i)
	{
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i)
	{
		delete statistics[i];
	}

	return 0;
}