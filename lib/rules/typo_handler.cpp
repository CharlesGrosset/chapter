#include <locale>
#include <codecvt>
#include <ctype.h>
#include <boost/regex.hpp>
#include <nlohmann/json.hpp>
#include <lib/rules/rule_retriever.hpp>
#include <lib/rules/rule_auditor.hpp>
#include <jamspell/spell_corrector.hpp>

void displayTypos(const std::string commitMsg) {
    NJamSpell::TSpellCorrector corrector;
    corrector.LoadLangModel("model_en.bin");
    std::string msg = NJamSpell::WideToUTF8(corrector.FixFragment(NJamSpell::UTF8ToWide(commitMsg)));
    printf("%s\n\n\n", msg.c_str());
}

std::wstring convertStrToWStr(std::string str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

std::string convertWStrToStr(std::wstring wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

std::vector<std::wstring> splitWStr(std::wstring wstr) {
    std::wstring str;
    std::vector<std::wstring> parts;
    std::wstringstream ws_stream(wstr);

    while (std::getline(ws_stream, str, L' ')) {
        str.erase(std::remove(str.begin(), str.end(), L'\n'), str.end());
        parts.push_back(str);
    }

    return parts;
}

/*
 * getTypos(getSummary(commitMsg))
 * getTypos(getDescription(commitMsg))
 * getTypos(getBulletPoints(commitMsg))
 */
std::vector<std::string> getTypos(std::string msgPartial) {
    NJamSpell::TSpellCorrector corrector;
    corrector.LoadLangModel("model_en.bin");

    // Must be lowercase for checking typos
    std::transform(msgPartial.begin(), msgPartial.end(), msgPartial.begin(), ::tolower);

    // Convert string to wstring
    std::wstring msgWStr = convertStrToWStr(msgPartial);

    // Split wstring on empty space
    std::vector<std::wstring> parts = splitWStr(msgWStr);

    std::vector<std::string> typos;
    for (size_t i = 0; i < parts.size(); i++) {
        std::vector<std::wstring> candidates = corrector.GetCandidates(parts, i);

        if (candidates.size() > 0) {
            std::wstring word;
            std::remove_copy_if(parts[i].begin(), parts[i].end(), std::back_inserter(word), std::ptr_fun<int, int>(&std::ispunct));

            // Compare with best-case candidate
            if (candidates[0].compare(word) != 0) {
                // Convert wstring back to string
                std::string typo = convertWStrToStr(result);
                typos.push_back(typo);
            }
        }
    }

    return typos;
}
