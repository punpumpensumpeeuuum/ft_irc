/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:33:00 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/29 20:03:14 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "messages.hpp"

class Utils
{
	public:
		static std::vector<std::string> split(const std::string &str, char splili);
		static int parseInput(const std::string& portStr, const std::string& pass);
	
	private:
		Utils();
		~Utils();
};

#endif