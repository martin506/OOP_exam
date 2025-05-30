#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <regex>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>


using namespace std;

vector<string> existing_urls;

bool is_real_url(const string& url) {
    return find(existing_urls.begin(), existing_urls.end(), url) != existing_urls.end();
}

bool is_valid_character(char c) {
    char invalid_chars[] = {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~'};
    for (char invalid : invalid_chars) {
        if (c == invalid) {
            return false;
        }
    }

    return true;
}

string clean_word(const string& word) {
    size_t start = 0;
    size_t end = word.size();

    while (start < end && !is_valid_character(word[start])) {
        ++start;
    }

    while (end > start && !is_valid_character(word[end - 1])) {
        --end;
    }

    string result = word.substr(start, end - start);

    transform(result.begin(), result.end(), result.begin(), ::tolower);

    return result;
}

int main() {
    ifstream in("existing_urls.txt");
    if (!in) {
        cerr << "Nepavyko atidaryti existing_urls.txt" << endl;
        return 1;
    }
    string url;
    while (in >> url) {
        if (!url.empty())
            existing_urls.push_back(url);
    }
    in.close();

    ifstream text_in("text.txt");
    if (!text_in) {
        cerr << "Nepavyko atidaryti text.txt" << endl;
        return 1;
    }

    unordered_map<string, int> word_count;
    unordered_map<string, vector<int>> word_lines;
    vector<string> lines;
    vector<string> urls;
    string line;
    int line_num = 0;

    while (getline(text_in, line)) {
        ++line_num;
        lines.push_back(line);

        istringstream iss(line);
        string word;
        unordered_set<string> words_in_line;
        while (iss >> word) {
            string cleaned = clean_word(word);
            if (cleaned.empty()) continue;
            word_count[cleaned]++;
            if (words_in_line.insert(cleaned).second) {
                word_lines[cleaned].push_back(line_num);
            }
        }

        word = "";

        istringstream iss2(line);

        bool is_url = false;
        while (iss2 >> word) {
            for (int i = 0; i < word.size(); ++i) {
                if (word[i] == '.') {
                    if (i > 2 && word[i-1] ==  'w' && word[i-2] == 'w' && word[i-3] == 'w') {
                        is_url = true;
                        break;
                    } else {
                        i++;
                        string ending_of_word = "";
                        while (i < word.size()) {
                            ending_of_word += toupper(word[i]);
                            ++i;
                        }

                        if (is_real_url(ending_of_word)) {
                            is_url = true;
                            break;
                        }
                    }
                }
            }

            if (is_url) {
                urls.push_back(word);
            }
        }
    }
    text_in.close();

    ofstream url_out("urls.txt");
    for (const string& url : urls) {
        url_out << url << "\n";
    }
    url_out.close();

    ofstream out("words_count.txt");
    for (const auto& [word, count] : word_count) {
        if (count > 1)
            out << word << " " << count << "\n";
    }
    out.close();

    ofstream cross("cross_reference.txt");
    for (const auto& [word, lines_vec] : word_lines) {
        if (word_count[word] > 1) {
            cross << word << ": ";
            for (size_t i = 0; i < lines_vec.size(); ++i) {
                cross << lines_vec[i];
                if (i + 1 < lines_vec.size()) cross << ", ";
            }
            cross << "\n";
        }
    }
    cross.close();

    cout << "Atlikta. Rezultatai: words_count.txt, cross_reference.txt" << endl;
    return 0;
}