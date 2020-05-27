#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>
#include <random>


void print_introduction(int add_hint, int multiply_hint)
{
	std::cout << "The game is to enter 3 numbers, the numbers must sum to " 
		      << add_hint << " and must multiply to " << multiply_hint << "!\n";

	std::cout << "If you would like to solve this yourself, enter \"ME\",\n"
				 "If you would like to use your PC to solve, enter \"PC\",\n\n";
}


int get_int()
{
	std::string string_convert_num;
	int int_code_guess = 0;
	while (true)
	{
		std::cout << "Please enter a valid number:\n";
		std::getline(std::cin, string_convert_num);

		std::stringstream ss_code_guess(string_convert_num);
		
		if (ss_code_guess >> int_code_guess)
		{
			std::cout << int_code_guess << " has been recorded.\n";
			return int_code_guess;
		}
			
		else
		{
			std::cout << "That was not a valid number. ";
		}
	}
}


int sum(int code_a, int code_b, int code_c)
{
	return code_a + code_b + code_c;
}


int multiply(int code_a, int code_b, int code_c)
{
	return code_a * code_b * code_c;
}


int random_number_generator(int min_num, int max_num)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist9(min_num, max_num);
	return dist9(rng);
}


std::tuple<int, int, int> pc_solve(int multiply_hint, int add_hint)
{
	std::vector<int> num_list;
	int i = 0;
	while (i < 9)
	{
		++i;
		num_list.push_back(i);

	}

	int num1 = 0, num2 = 0, num3 = 0;
	int& ref1 = num1; int& ref2 = num2; int& ref3 = num3;

	for (int num1 : num_list)
	{
		ref1++;
		for (int num2 : num_list)
		{
			ref2++;
			for (int num3 : num_list)
			{
				ref3++;

				if (ref1 > 9) {ref1 = 1; } if (ref2 > 9) {ref2 = 1; } if (ref3 > 9) {ref3 = 1; }
				std::cout << ref1 << " " << ref2 << " " << ref3 << " " << sum(ref1, ref2, ref3) 
						  << " " << multiply(ref1, ref2, ref3) << " \n";

				if ((sum(ref1, ref2, ref3) == add_hint) && (multiply(ref1, ref2, ref3) == multiply_hint))
				{
					return std::make_tuple(ref1, ref2, ref3);
				}
			}
		}
	}
	return std::make_tuple(ref1, ref2, ref3);
}


bool user_solve(int multiply_hint, int add_hint)
{
	int int_code_a_guess, int_code_b_guess, int_code_c_guess;
	int& int_a_ref = int_code_a_guess; int& int_b_ref = int_code_b_guess; int& int_c_ref = int_code_c_guess;

	int count = 0;

	while ((sum(int_code_a_guess, int_code_b_guess, int_code_c_guess) != add_hint) && 
		   (multiply(int_code_a_guess, int_code_b_guess, int_code_c_guess != multiply_hint)))
	{
		if (count != 0)
		{
			std::cout << "One (or all) of your numbers are incorrect!, please re-enter your numbers\n";
		}
		std::cout << "Please enter your numbers each seperated by a newline -\n";
		
		int_code_a_guess = get_int(); int_code_b_guess = get_int();  int_code_c_guess = get_int();
		count++;
	}

	if (sum(int_code_a_guess, int_code_b_guess, int_code_c_guess) == add_hint &&
		multiply(int_code_a_guess, int_code_b_guess, int_code_c_guess) == multiply_hint)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}


int main()
{
	int code_a, code_b, code_c, multiply_hint_num, add_hint_num;
	code_a = random_number_generator(1, 9); 
	code_b = random_number_generator(1, 9); 
	code_c = random_number_generator(1, 9);
	add_hint_num = sum(code_a, code_b, code_c); multiply_hint_num = multiply(code_a, code_b, code_c);
	std::cout << code_a << " " << code_b << " " << code_c << "\n";

	print_introduction(add_hint_num, multiply_hint_num);

	std::string our_string;
	std::getline(std::cin, our_string);
	
	while ((our_string != "PC") && (our_string != "ME"))
	{
		std::cout << "Please enter PC or ME-\n";
		std::getline(std::cin, our_string);
	}
		
	if (our_string == "PC")
	{
		pc_solve(multiply_hint_num, add_hint_num);
	}
	else
	{
		int Level = 1;
		int LevelNum = 1;
		const int MaxLevel = 9;
		
		while (Level <= 9)
		{
			if (Level > 5)
			{
				LevelNum = 5;
			}
			else
			{
				LevelNum = Level;
			}

			if (user_solve(multiply_hint_num, add_hint_num))
			{
				Level++;
				if (Level == 10)
				{
					std::cout << "You beat all levels, congrats!" << std::endl;
					break;
				}
				std::cout << "You have beaten level " << Level-1 <<", leveled up to " << Level << "! "
					      << MaxLevel - Level << " levels remaining!\n\n\n\n";

				code_a = random_number_generator(LevelNum, MaxLevel);
				code_b = random_number_generator(LevelNum, MaxLevel);
				code_c = random_number_generator(LevelNum, MaxLevel);
				add_hint_num = sum(code_a, code_b, code_c); multiply_hint_num = multiply(code_a, code_b, code_c);
				std::cout << "Level " << Level <<" hints:\nSum of the 3 numbers is: " << add_hint_num
					<< " and the product is: " << multiply_hint_num << std::endl;
				std::cout << code_a << " " << code_b << " " << code_c << "\n";
			}
		}
	}
	return 0;
}
