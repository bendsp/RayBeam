/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** file_parser.cpp
*/

#include <libconfig.h++>
#include <iostream>

int parse_file(char *filepath)
{
    libconfig::Config cfg;
    try {
        cfg.readFile(filepath);
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return (84);
    }
    catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        return (84);
    }
    return (0);
}
