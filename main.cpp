#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <exception>
#include <iomanip>

void print(std::string l, int w);

int main()
{
	std::ifstream file{ "words1.txt" };
	const std::string line{ "-=" };
	const int width{ 235 };
	const int element_space{ 24 };
	const int letters_start{ 1 };
	const int letters_end{ 11 };
	
	if (!file)
	{
		std::cout << "Error opening file" << std::endl;
		return 1;
	}

	std::cout << "Enter a scrambled word: ";

	std::string scrambled_word{};
	std::string word{};
	std::vector<std::string> words;
	std::vector<std::vector<std::string>> sorted_words(50, std::vector<std::string>{});

	std::cin >> scrambled_word;

	for (int i = 0; i < scrambled_word.size(); i++)
	{
		scrambled_word[i] = std::tolower(scrambled_word[i]);
	}

	while (file >> word)
	{
		std::string copy_scrambled{ scrambled_word };
		std::string copy_word{ word };

		std::string::iterator it1 = copy_word.begin();
		std::string::iterator it2 = copy_scrambled.begin();

		while (it1 != copy_word.end())
		{
			if (it2 == copy_scrambled.end())
			{
				break;
			}
			else if (*it1 == *it2)
			{
				it1 = copy_word.erase(it1);
				copy_scrambled.erase(it2);
				it2 = copy_scrambled.begin();
			}
			else
			{
				it2++;
			}
		}

		if (copy_word.empty())
		{
			words.push_back(word);
		}
	}

	for (std::string w : words)
	{
		/*try
		{
			sorted_words.at(w.size()).push_back(w);
		}
		
		catch (const std::out_of_range &e)
		{
			std::cout << w.size() << std::endl;
		}*/

		sorted_words.at(w.size()).push_back(w);
	}

	std::cout << std::endl;
	print(line, width);
	std::cout << std::endl;

	for (int i = letters_start; i < letters_end; i++)
	{
		std::string letters{ std::to_string(i) + " letters" };
		std::cout << std::setw(element_space) << std::left << letters;
	}

	std::cout << std::endl << std::endl;
	print(line, width);
	std::cout << std::endl;

	int index{ 0 };
	int max_size{ 0 };

	for (std::vector<std::string> v : sorted_words)
	{
		if (v.size() > max_size)
		{
			max_size = v.size();
		}
	}
	
	for (int c = 0; c < max_size; c++)
	{
		for (int i = letters_start; i < letters_end; i++)
		{
			if (index < sorted_words[i].size())
			{
				std::cout << std::setw(element_space) << std::left << sorted_words[i][index];
			}
			else
			{
				std::cout << std::setw(element_space) << std::left << "";
			}
		}

		std::cout << std::endl;
		index++;
	}

	std::cout << std::endl;
	print(line, width);
	std::cout << std::endl;

	std::cout << "A total of " << words.size() << " words were found" << std::endl;

	return 0;

}

void print(std::string l, int w)
{
	int width{ w / static_cast<int>(l.size()) };

	for (int i = 0; i < width; i++)
	{
		std::cout << l;
	}

	std::cout << std::endl;
}