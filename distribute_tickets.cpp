#include <fstream>
#include <getopt.h>
#include <iostream>
#include <random>

using std::string;

namespace DistributionOptions {
    const int NUM_OPTIONS = 3;
}

struct Options {
    string file;
    unsigned amount_of_tickets{0};
    unsigned parameter{0};
};


unsigned get_ticket_number(const string& name, unsigned amount_of_tickets, unsigned parameter, std::mt19937 *mersenne) {
    unsigned result;
    unsigned sum = 0;
    for (const char& c : name) {
        sum += abs(c);
    }

    result = sum * parameter ^ (*mersenne)();
    return result % amount_of_tickets + 1;
}


bool parse_options(int argc, char* argv[], Options *options) {
    if (!argv || !argc) {
        return EXIT_FAILURE;
    }

    int amount_of_options = 0;
    int result;
    int option_index;
    const char *short_options = "f:n:p:";
    static struct option long_options[] = {
            {"file", required_argument, nullptr, 'f'},
            {"numtickets", required_argument, nullptr, 'n'},
            {"parameter", required_argument, nullptr, 'p'},
            {nullptr, 0, nullptr, 0}
    };


    while ((result = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch(result) {
            case 'f': {
                amount_of_options++;
                string file = optarg;
                std::ifstream infile(file);
                if (!infile.good()) {
                    infile.close();
                    return EXIT_FAILURE;
                }
                options->file = file;
                break;
            }
            case 'n': {
                amount_of_options++;
                long number = strtol(optarg, &optarg, 10);
                if (number < 1) {
                    return EXIT_FAILURE;
                }
                options->amount_of_tickets = number;
                break;
            }
            case 'p': {
                amount_of_options++;
                long number = strtol(optarg, &optarg, 10);
                if (number < 1) {
                    return EXIT_FAILURE;
                }
                options->parameter = number;
                break;
            }
            default: {
                return EXIT_FAILURE;
            }
        }
    }
    return (amount_of_options == DistributionOptions::NUM_OPTIONS) ? EXIT_SUCCESS : EXIT_FAILURE;
}


int main(int argc, char* argv[]) {
    Options options;
    bool is_fail = parse_options(argc, argv, &options);
    if (is_fail) {
        std::cerr << "Usage: wrong options" << std::endl;
        return EXIT_FAILURE;
    }

    string file = options.file;
    unsigned amount_of_tickets = options.amount_of_tickets;
    unsigned parameter = options.parameter;

    std::ifstream input(file);
    std::mt19937 mersenne(parameter);
    unsigned ticket_number;
    for (string line; getline(input, line);) {
        ticket_number = get_ticket_number(line, amount_of_tickets, parameter, &mersenne);
        std::cout << line << ": " << ticket_number << std::endl;
    }

    input.close();
    return EXIT_SUCCESS;
}
