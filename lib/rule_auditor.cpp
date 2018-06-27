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

const std::string VALID_CHARS_PATTERN = "\u0021-\u007E\\s";

bool containsBulletPoints(const std::string msg, const int count) {
    // const boost::regex point_pattern("[" + VALID_CHARS_PATTERN + "]+\n\n[" + VALID_CHARS_PATTERN + "]*\n\n([\\+|-|\\*"
                                        // + VALID_CHARS_PATTERN + "]{" + std::to_string(count) + "})");
    const boost::regex pointPattern("[" + VALID_CHARS_PATTERN + "]+\n\n[" + VALID_CHARS_PATTERN + "]*\n\n(["
                                        + VALID_CHARS_PATTERN + "\n]+)");

    if (regex_match(msg, pointPattern)) {
        return true;
    }

    return false;
}

bool containsCorrectDocFormat(const std::string msg) {
    std::string loweredMsg = msg;
    const boost::regex docPattern(".*(documentation).*");
    const boost::regex docFormatPattern("Documentation:\\s.*");
    std::transform(loweredMsg.begin(), loweredMsg.end(), loweredMsg.begin(), ::tolower);

    if (regex_match(loweredMsg, docPattern)) {
        if (!regex_match(msg, docFormatPattern)) {
            return false;
        }
    }

    return true;
}

bool containsCorrectNitFormat(const std::string msg) {
    std::string loweredMsg = msg;
    const boost::regex nitPattern(".*(nit).*");
    const boost::regex nitFormatPattern("Nit:\\s.*");
    std::transform(loweredMsg.begin(), loweredMsg.end(), loweredMsg.begin(), ::tolower);

    if (regex_match(loweredMsg, nitPattern)) {
        if (!regex_match(msg, nitFormatPattern)) {
            return false;
        }
    }

    return true;
}

bool containsCorrectWIPFormat(const std::string msg) {
    std::string loweredMsg = msg;
    const boost::regex WIPPattern(".*(wip).*");
    const boost::regex WIPFormatPattern("WIP:\\s.*");
    std::transform(loweredMsg.begin(), loweredMsg.end(), loweredMsg.begin(), ::tolower);

    if (regex_match(loweredMsg, WIPPattern)) {
        if (!regex_match(msg, WIPFormatPattern)) {
            return false;
        }
    }

    return true;
}

bool containsDescription(const std::string msg) {
    const boost::regex descPattern("[" + VALID_CHARS_PATTERN + "]+\n\n([" + VALID_CHARS_PATTERN + "\n]+)");
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
    const boost::regex descPattern("[" + VALID_CHARS_PATTERN + "]+\n\n([" + VALID_CHARS_PATTERN + "\n]+)");
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
    const boost::regex descPattern("[" + VALID_CHARS_PATTERN + "]+\n\n([" + VALID_CHARS_PATTERN + "\n]+)");
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
    const boost::regex summaryPattern("([" + VALID_CHARS_PATTERN + "]+)[\n" + VALID_CHARS_PATTERN + "]*");
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
    const boost::regex summaryPattern("([" + VALID_CHARS_PATTERN + "]+).*");
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
    const boost::regex summaryPattern("([" + VALID_CHARS_PATTERN + "]+).*");
    boost::smatch result;

    if (boost::regex_search(msg, result, summaryPattern)) {
        const std::string submatch(result[1].first, result[1].second);
        if (submatch.length() < length) {
            return true;
        }
    }

    return false;
}
