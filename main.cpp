#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <unistd.h>
#include <jamspell/spell_corrector.hpp>

// TODO: Place audit methods in lib/
bool containsTypos(std::string msg) {
    return true;
}

bool isFirstLetterCapitalized(std::string msg) {
    if (isupper(msg[0])) {
       return true;
    } else {
       return false;
    }
}

bool containsPeriod(std::string msg) {
    return true;
}

bool isMaxLength(std::string msg) {
    return true;
}

bool containsSummary(std::string msg) {
    return true;
}

bool containsKeyPoints(std::string msg) {
    return true;
}

int main(int argc, char* argv[]) {
    NJamSpell::TSpellCorrector corrector;
    corrector.LoadLangModel("model.bin");
    char buffer[255];
    char* answer = getcwd(buffer, sizeof(buffer));
    std::string s_cwd;

    if (answer) {
        s_cwd = answer;
    }

    std::string commit_msg_path = s_cwd + "/.git/COMMIT_EDITMSG";
    std::ifstream f(commit_msg_path.c_str());
    std::ostringstream out;

    if (f.is_open()) {
        out << f.rdbuf();
    }

    std::string commit_msg = out.str();
    printf("%s", commit_msg.c_str());
    
    printf("Beginning audit... \U00002699\n");

    commit_msg = NJamSpell::WideToUTF8(corrector.FixFragment(NJamSpell::UTF8ToWide(commit_msg)));

    if (isFirstLetterCapitalized(commit_msg)) {
        printf("No errors found. \U0001F3C6\n");
    } else {
        printf("Error: First letter must be capitalized. \U0000274C\n");
    }

    return 0;
}
