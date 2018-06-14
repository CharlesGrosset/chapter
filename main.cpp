#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <unistd.h>
#include <boost/regex.hpp>
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

bool containsCorrectNitFormat(std::string msg) {
    std::string lowered_msg = msg;
    const boost::regex nit_pattern(".*\\s(nit)\\s.*");
    const boost::regex nit_format_pattern("Nit:.*");
    std::transform(lowered_msg.begin(), lowered_msg.end(), lowered_msg.begin(), ::tolower);

    if (regex_match(lowered_msg, nit_pattern)) {
        if (!regex_match(msg, nit_format_pattern)) {
            return false;
        }
    }

    return true;
}

bool containsCorrectWIPFormat(std::string msg) {
    std::string lowered_msg = msg;
    const boost::regex WIP_pattern(".*\\s(wip)\\s.*");
    const boost::regex WIP_format_pattern("WIP:.*");
    std::transform(lowered_msg.begin(), lowered_msg.end(), lowered_msg.begin(), ::tolower);

    if (regex_match(lowered_msg, WIP_pattern)) {
        if (!regex_match(msg, WIP_format_pattern)) {
            return false;
        }
    }

    return true;
}

bool isSummaryMaxLength(std::string msg) {
    if (msg.length() > 50) return true;
    return false;
}

bool containsDescription(std::string msg) {
    // TODO: Formatting and character length
    const boost::regex desc_pattern("[a-zA-Z0-9_\\s]*\\n\\n([a-zA-Z0-9_\\s]*)");

    if (!regex_match(msg, desc_pattern)) {
        return false;
    }

    return true;
}

bool containsBulletPoints(std::string msg) {
    // Formatting and # of bullets (default 3)
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

    if (!isFirstLetterCapitalized(commit_msg)) {
        printf("Error: First letter must be capitalized. \U0000274C\n");
    }

    if (!containsCorrectNitFormat(commit_msg)) {
        printf("Error: \"Nit:\" commits must have the correct format. \U0000274C\n");
    }

    if (!containsCorrectWIPFormat(commit_msg)) {
        printf("Error: \"WIP:\" commits must have the correct format. \U0000274C\n");
    }

    if (isSummaryMaxLength(commit_msg)) {
        printf("Error: Summary must not exceed 50 characters. \U0000274C\n");
    }

    if (!containsDescription(commit_msg)) {
        printf("Error: Description is required. \U0000274C\n");
    }

    return 0;
}
