/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_replacer.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 12:14:31 by smun              #+#    #+#             */
/*   Updated: 2022/01/31 13:08:25 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

static std::string& replaceAll(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;

	while(true)
	{
		start_pos = str.find(from, start_pos);
		if (start_pos == std::string::npos)
			break;
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

static std::string readFromStdin()
{
	std::stringstream ss;

	while(true)
	{
		std::string line;
		if (!std::getline(std::cin, line))
			break;
		ss << line << std::endl;
	}
	return ss.str();
}

int main(int argc, char* argv[])
{
	std::string arg;
	if (argc >= 2)
		arg = argv[1];
	else
		arg = readFromStdin();

	replaceAll(arg, "\n", "");
	replaceAll(arg, "      ", " ");
	replaceAll(arg, "std::__1::basic_string<char>", "std::string");
	replaceAll(arg, " >", ">");
	replaceAll(arg, "::__1", "");
	replaceAll(arg, "std::allocator<ft::pair<const std::pair<int, std::string>, std::string>>", "ALLOCATOR");
	replaceAll(arg, "std::pair<int, std::string>", "KEYPAIR");
	replaceAll(arg, "tree<KEYPAIR, std::string, ft::pair<const KEYPAIR, std::string>, std::less<KEYPAIR>, ALLOCATOR>", "TREE");
	std::cout << arg << std::endl;
	return 0;
}
