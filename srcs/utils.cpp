/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:39:44 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/27 04:56:22 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/utils.hpp"

std::vector<std::string> Utils::split(const std::string &str, char splili)
{
    std::vector<std::string> args;
    std::string line;

    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] == splili)
        {
            if (!line.empty())
            {
                args.push_back(line);
                line.clear();
            }
        }
        else
        {
            line += str[i];
        }
    }
    if (!line.empty())
        args.push_back(line);
    return (args);
}
