
#include <algorithm>
#include <cassert>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

inline std::string file_slurp (const std::string & filename)
{
    std::string retval;
    std::ifstream ifs(filename);
    std::getline(ifs, retval, '\0');
    return retval;
}

inline std::vector<std::string> line_break (const std::string & file)
{
    std::vector<std::string> retval;

    std::string::size_type prev_pos = 0;
    while (true) {
        std::string::size_type pos = file.find('\n', prev_pos);
        if (pos == std::string::npos)
            break;
        retval.push_back(file.substr(prev_pos, pos - prev_pos));
        prev_pos = pos + 1;
    }

    retval.push_back(file.substr(prev_pos));

    return retval;
}

void find_samples (const std::vector<std::string> & lines,
                   std::map<std::string, std::string> & samples)
{
    const std::string sample_str = "sample";
    const std::string end_str = "end-sample";

    std::string current_sample_name;
    auto current_sample_indentation = 0;
    for (const std::string & line : lines) {
        const auto comment_index = line.find("//");
        const bool comment_line = comment_index != std::string::npos;
        std::string::size_type sample_pos = line.find(sample_str);
        std::string::size_type end_pos = line.find(end_str);
        if (comment_line && end_pos != std::string::npos) {
            samples[current_sample_name] += "```";
            current_sample_name = "";
            current_sample_indentation = 0;
        } else if (comment_line && sample_pos != std::string::npos) {
            sample_pos += sample_str.size() + 1;
            std::string::size_type close_paren = line.find(")", sample_pos);
            current_sample_name =
                line.substr(sample_pos, close_paren - sample_pos);
            current_sample_indentation = comment_index;
            std::string::size_type size_minus_3 =
                samples[current_sample_name].size() - 3;
            if (samples[current_sample_name].rfind("```") == size_minus_3) {
                samples[current_sample_name].resize(
                    samples[current_sample_name].size() - 3
                );
            } else {
                samples[current_sample_name] += "```cpp\n";
            }
        } else if (current_sample_name != "") {
            samples[current_sample_name] += line.substr(current_sample_indentation) + '\n';
        }
    }
}


int main (int argc, char * argv[])
{
    assert(3 <= argc);
    int result = 0;
    const char * in_filename = argv[1];

    std::vector<std::string> file_lines = line_break(file_slurp(in_filename));

    std::map<std::string, std::string> samples;
    std::for_each(argv + 3, argv + argc,
                  [&](const char * filename) {
                      find_samples(line_break(file_slurp(filename)), samples);
                  });

    for (std::string & line : file_lines) {
        std::string::size_type sample_ref_pos = line.find("%%");
        if (sample_ref_pos != std::string::npos) {
            sample_ref_pos += 2;
            std::string::size_type sample_ref_end_pos =
                line.find("%%", sample_ref_pos);
            const std::string sample_name = line.substr(
                sample_ref_pos,
                sample_ref_end_pos - sample_ref_pos
            );
            try {
                line = samples.at(sample_name);
            }
            catch(...) {
                std::cerr << "ERROR: Failed to retrieve sample: " << sample_name << std::endl;
                result = 1;
            }
        }
    }
    if (result != 0) {
        std::cerr << "Note: Samples loaded:" << std::endl;
        for(auto&& p:samples) std::cerr << p.first << std::endl;
        return result;
    }

    const char * out_filename = argv[2];
    std::ofstream ofs(out_filename);
    for (const std::string & line : file_lines) {
        ofs << line << "\n";
    }

    return result;
}
