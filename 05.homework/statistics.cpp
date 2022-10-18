#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

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
	Min() : m_min{std::numeric_limits<double>::max()}
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
	Max() : m_max{std::numeric_limits<double>::min()}
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
		return std::sqrt(sigma);
	}
	virtual const char *name() const override
	{
		return "std";
	}

private:
	double std_sum;
	std::vector<double> sequence;
};

class pct : public IStatistics
{
public:
	pct() : pct_value{0}, i_percent{100} { do_name(); }
	pct(int pct) : pct_value{0}, i_percent{pct} { do_name(); }

	virtual void update(double next) override
	{
		sequence.push_back(next);
		std::setprecision(5);
		// std::sort(sequence.begin(), sequence.end());
		double rank = static_cast<double>(i_percent) / 100 * (sequence.size() + 1);
		rank = std::round(rank * 1000.0);
		rank /= 1000.0;
		if (rank - (int)rank == 0)
		{
			pct_value = sequence[rank - 1];
		}
		else
		{
			pct_value = rank - (int)rank;
			pct_value *= std::abs(sequence[(int)rank - 1] - sequence[(int)rank]);
			pct_value += sequence[(int)rank];
		}
	}
	virtual double eval() const override
	{
		return pct_value;
	}
	virtual const char *name() const override
	{

		return result_name;
	}

private:
	double pct_value;
	std::vector<double> sequence;

	int i_percent;
	char ch_percent[3];
	char result_name[7] = "pct";

	void do_name()
	{
		std::sprintf(ch_percent, "%d", i_percent);
		strcat(result_name, ch_percent);
	}
};

int main()
{
	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};
	statistics[4] = new pct{90};
	statistics[5] = new pct{95};

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