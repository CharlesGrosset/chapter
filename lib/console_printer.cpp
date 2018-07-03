#include <ctype.h>
#include <boost/regex.hpp>
#include <nlohmann/json.hpp>
#include <lib/rule_auditor.hpp>
#include <lib/rule_retriever.hpp>
#include <jamspell/spell_corrector.hpp>

/*
 * TODO:
 * + Check all rule types in config file before running audit
 * + Remove success statements (add (\U0001F3C6) trophy statement for no errors/warnings)
 */

void displayAuditResults(nlohmann::json rulesJSON, const std::string commitMsg) {
    NJamSpell::TSpellCorrector corrector;
    corrector.LoadLangModel("model.bin");

    int summaryMinLength = getSummaryMinLength(rulesJSON);
    int summaryMaxLength = getSummaryMaxLength(rulesJSON);
    int bulletPointsVal = getBulletPoints(rulesJSON);
    bool reqNitFormat = requiresNitFormat(rulesJSON);
    bool reqWIPFormat = requiresWIPFormat(rulesJSON);
    bool reqDocFormat = requiresDocFormat(rulesJSON);

    std::cout << "************   \U00002699 Commit message audit...   ************\n";

    // TODO:
    // std::string commit_msg_mod = NJamSpell::WideToUTF8(corrector.FixFragment(NJamSpell::UTF8ToWide(commit_msg)));
    // printf("Testing spell check...\n");
    // printf("%s\n", commit_msg_mod.c_str());

    if (reqNitFormat && reqWIPFormat && reqDocFormat) {
        if (requiresSummaryCapital(rulesJSON) && !isFirstLetterCapitalized(commitMsg)) {
            std::cout << "\U0000274C Error: First letter of summary must be capitalized." << "\n";
        }
    }

    if (requiresNitFormat(rulesJSON) && !containsCorrectNitFormat(commitMsg)) {
        std::cout << "\U0000274C Error: \"Nit:\" commits must have the correct format." << "\n";
    }

    if (requiresWIPFormat(rulesJSON) && !containsCorrectWIPFormat(commitMsg)) {
        std::cout << "\U0000274C Error: \"WIP:\" commits must have the correct format." << "\n";
    }

    if (requiresDocFormat(rulesJSON) && !containsCorrectDocFormat(commitMsg)) {
        std::cout << "\U0000274C Error: \"Documentation:\" commits must have the correct format." << "\n";
    }

    if (isSummaryMinLength(commitMsg, summaryMinLength)) {
        std::cout << "\U0000274C Error: Summary must be above " << summaryMinLength << " characters.\n";
    }

    if (isSummaryMaxLength(commitMsg, summaryMaxLength)) {
        std::cout << "\U0000274C Error: Summary must not exceed " << summaryMaxLength << " characters.\n";
    }

    if (requiresDescription(rulesJSON)) {
        if (containsDescription(commitMsg)) {
            int descMinLength = getDescriptionMinLength(rulesJSON);
            int descMaxLength = getDescriptionMaxLength(rulesJSON);

            if (isDescriptionMinLength(commitMsg, descMinLength)) {
                std::cout << "\U0000274C Error: Description must be above " << descMinLength << " characters.\n";
            }

            if (isDescriptionMaxLength(commitMsg, descMaxLength)) {
                std::cout << "\U0000274C Error: Description must not exceed " << descMaxLength << " characters.\n";
            }
        } else {
            std::cout << "\U0000274C Error: Description is required. \n";
        }
    }

    if (bulletPointsVal != 0) {
        if (!containsBulletPoints(commitMsg, bulletPointsVal)) {
            std::cout << "\U0000274C Error: " << bulletPointsVal << " bullet points are required. \n";
        }
    }

    std::cout << "************        \U00002699 End of audit.        ************\n";
}
