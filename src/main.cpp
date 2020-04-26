#include <iostream>
#include "Multiplicator.h"
#include <memory>
#include <fstream>


double timer(const std::unique_ptr<Multiplicator>& ptr, const size_t& i)
{
	Number exm1 = ptr->generate_random(i);
	Number exm2 = ptr->generate_random(i);

	clock_t begin = clock(), end;
	Number res = ptr->multiply(exm1, exm2);
	end = clock();
	return (double)(end - begin) / CLOCKS_PER_SEC;
}

void csv_writer(const size_t& n1, const size_t& n2, const std::string& path, const size_t step, const size_t& constant)
{
	std::fstream fs;
	fs.open(path, std::fstream::in | std::fstream::app | std::fstream::out);

	std::vector<std::unique_ptr<Multiplicator>> ptr_array(3);
	ptr_array[0] = std::make_unique<Grade_school> ();
	ptr_array[1] = std::make_unique<D_C>();
	ptr_array[2] = std::make_unique<Karatsuba>();

	size_t number_of_tests = 0;

	double Grade_school_sum = 0;
	double D_C_sum = 0;
	double Karatsuba_sum = 0;

	if (!fs.is_open())
		std::cout << "opening file error!!!\nPlease, try again later...";
	else
	{
		for (size_t i = n1; i < n2;)
		{
			Grade_school_sum += timer(ptr_array[0], i);
			D_C_sum += timer(ptr_array[1], i);
			Karatsuba_sum += timer(ptr_array[2], i);

			number_of_tests++;

			if (number_of_tests == 3)
			{
				fs  << i << ";"
					<< (double)(Grade_school_sum / 3) << ";"
					<< (double)(D_C_sum / 3) << ";"
					<< (double)(Karatsuba_sum / 3) << "\n";

				Grade_school_sum = 0;
				D_C_sum = 0;
				Karatsuba_sum = 0;

				number_of_tests = 0;
				if (i >= 1000)
					i += step * constant;
				else
					i += step;
			}
			std::cout << i << "\n";
		}
		fs.close();
	}
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	Number frst, scnd;

	int n1, n2, steps, constnant;

	std::cout << "type in borders (n1 and n2): ";
	std::cin >> n1 >> n2;

	std::string name, path;

	std::cout << "type in the name of the future csv file: ";
	std::cin >> path;

	name = path + ".csv";

	std::cout << "type in the number of steps and constant: ";
	std::cin >> steps >> constnant;

	std::cout << "loading...\n";

	csv_writer(n1, n2, name, steps, constnant);

	std::cout << "calculations are finished, check " + name + " file";

	system("pause");
}