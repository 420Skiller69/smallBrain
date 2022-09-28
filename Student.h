#include <vector>
#include <iterator>



class Student
{
	std::vector<char> word;
	
	public:
		Student()
		{
			word = std::vector<char>(3);
			for(auto &letter: word)
				letter = 'a' + rand()%('z' - 'a' + 1);
		}
		double fitness;
		double getFitness();
		void mutate(double probability, double strength);
		friend void interpolate(const class Student &parent1, const class Student &parent2, class Student &child, double bias);
		void display();
};

