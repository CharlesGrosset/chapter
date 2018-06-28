#include <iostream>
#include <boost/regex.hpp>

/*
 * TODO:
 * + Complete typos identification
 * + Fix all regex patterns (lot of work here)
 * + Fix regex for identifying # of bullet points
 * + Improve initial regex for nit/WIP
 * + Combine min/max and nit/WIP functions
 */

const std::string VALID_MSG_CHARS = "\u0021-\u007E\\s";

bool containsBulletPoints(const std::string msg, const int count) {
    // const boost::regex point_pattern("[" + VALID_MSG_CHARS + "]+\n\n[" + VALID_MSG_CHARS + "]*\n\n([\\+|-|\\*"
                                        // + VALID_MSG_CHARS + "]{" + std::to_string(count) + "})");
    const boost::regex pointPattern("[" + VALID_MSG_CHARS + "]+\n\n[" + VALID_MSG_CHARS + "]*\n\n(["
                                        + VALID_MSG_CHARS + "\n]+)");

    if (regex_match(msg, pointPattern)) {
        return true;
    }

    return false;
}

bool containsCorrectDocFormat(const std::string msg) {
    const boost::regex docPattern(".*\\s([D|d]ocumentation|[D|d]oc[s]?):?\\s.*");
    const boost::regex docFormatPattern("Documentation:\\s.*");

    if (regex_match(msg, docPattern)) {
        if (!regex_match(msg, docFormatPattern)) {
            return false;
        }
    }

    return true;
}

bool containsCorrectNitFormat(const std::string msg) {
    const boost::regex nitPattern(".*\\s([N|n]it):?\\s.*");
    const boost::regex nitFormatPattern("Nit:\\s.*");

    if (regex_match(msg, nitPattern)) {
        if (!regex_match(msg, nitFormatPattern)) {
            return false;
        }
    }

    return true;
}

bool containsCorrectWIPFormat(const std::string msg) {
    const boost::regex WIPPattern(".*\\s([[W|w]ip|WIP]):?\\s.*");
    const boost::regex WIPFormatPattern("WIP:\\s.*");

    if (regex_match(msg, WIPPattern)) {
        if (!regex_match(msg, WIPFormatPattern)) {
            return false;
        }
    }

    return true;
}

bool containsDescription(const std::string msg) {
    const boost::regex descPattern("[" + VALID_MSG_CHARS + "]+\n\n([" + VALID_MSG_CHARS + "\n]+)");
    // exclude pattern \n[\+\-\*]\\sText here

    if (regex_match(msg, descPattern)) {
        return true;
    }

    return false;
}

bool containsTypos(const std::string msg) {
    // TODO:
    //  + Generate warning (instead of error) outlining all typos
    //  + Ignore nit and WIP
    return true;
}

bool isDescriptionMaxLength(const std::string msg, const int length) {
    const boost::regex descPattern("[" + VALID_MSG_CHARS + "]+\n\n([" + VALID_MSG_CHARS + "\n]+)");
    boost::smatch result;

    if (boost::regex_search(msg, result, descPattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() > length) {
            return true;
        }
    }

    return false;
}

bool isDescriptionMinLength(const std::string msg, const int length) {
    const boost::regex descPattern("[" + VALID_MSG_CHARS + "]+\n\n([" + VALID_MSG_CHARS + "\n]+)");
    boost::smatch result;

    if (boost::regex_search(msg, result, descPattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() < length) {
            return true;
        }
    }

    return false;
}

// TODO: Only check if correct Nit/Doc/WIP format
bool isFirstLetterCapitalized(const std::string msg) {
    const std::vector<std::string> excludedStrings = { "Nit:", "WIP:", "Documentation:" };
    const boost::regex summaryPattern("([" + VALID_MSG_CHARS + "]+)[\n" + VALID_MSG_CHARS + "]*");
    const boost::regex wordPattern("$\\s?([a-zA-Z]+).*");
    boost::smatch summaryResult;
    boost::smatch initialWordResult;

    if (boost::regex_search(msg, summaryResult, summaryPattern)) {
        std::string summary(summaryResult[1].first, summaryResult[1].second);

        // If exclusions included, remove them from the string
        for (const std::string formatWord : excludedStrings) {
            const size_t initialPos = summary.find(formatWord);
            if (initialPos != summary.npos) {
                summary.replace(initialPos, formatWord.length(), "");
                break;
            }
        }

        // Regex to capture first word in summary
        if (boost::regex_search(summary, initialWordResult, wordPattern)) {
            const std::string initialWord(initialWordResult[1].first, initialWordResult[1].second);

            if (isupper(initialWord[0])) {
                return true;
            }

            return false;
        }

        // If first set of characters is not a word
        return true;
    }

    return false;
}

bool isSummaryMaxLength(const std::string msg, const int length) {
    const boost::regex summaryPattern("([" + VALID_MSG_CHARS + "]+).*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summaryPattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() > length) {
            return true;
        }
    }

    return false;
}

bool isSummaryMinLength(const std::string msg, const int length) {
    const boost::regex summaryPattern("([" + VALID_MSG_CHARS + "]+).*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summaryPattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() < length) {
            return true;
        }
    }

    return false;
}
