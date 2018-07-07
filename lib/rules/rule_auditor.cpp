#include <iostream>
#include <boost/regex.hpp>

const std::string VALID_MSG_CHARS = "\u0020-\u007E";

void normalizeEndOfCapture(std::string& capture) {
    // Remove last '\n' character if captured with double new line
    const int length = capture.length();
    if (capture[length - 2] == '\n' && capture[length - 1] == '\n') {
        capture.replace(length - 1, 1, "");
    }
}

void removePointsFromDesc(std::string& msg) {
    for (int i = 0; i < msg.length(); i++) {
        if ((msg[i - 1] == '\n' || i == 0) && (msg[i] == '+' || msg[i] == '*' || msg[i] == '-')) {
            int j = i;

            // Look for end of line
            while (msg[j] != '\n') {
                j++;
            }

            msg.replace(i, j - i + 1, "");
            i = i - 1;
        }
    }

    normalizeEndOfCapture(msg);
}

void removeDescFromPoints(std::string& msg) {
    for (int i = 0; i < msg.length(); i++) {
        if ((msg[i - 1] == '\n' || i == 0) && msg[i] != '+' && msg[i] != '*' && msg[i] != '-') {
            int j = i;

            // Look for end of line
            while (msg[j] != '\n') {
                j++;
            }

            msg.replace(i, j - i + 1, "");
            i = i - 1;
        }
    }

    normalizeEndOfCapture(msg);
}

int getBulletPointCount(const std::string points) {
    const int length = points.length();
    int count = 0;

    for (int i = 0; i < length; i++) {
        if (points[i] == '\n') count++;
    }

    if (length > 0 && count == 0) {
        count++;
    }

    return count;
}

bool containsBulletPoints(const std::string msg, const int requiredCount) {
    const boost::regex pointPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    boost::smatch pointResult;

    if (boost::regex_search(msg, pointResult, pointPattern)) {
        std::string points(pointResult[1].first, pointResult[1].second);
        removeDescFromPoints(points);

        return getBulletPointCount(points) == requiredCount;
    }

    return false;
}

std::string getBulletPoints(const std::string msg) {
    const boost::regex pointPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    boost::smatch pointResult;

    if (boost::regex_search(msg, pointResult, pointPattern)) {
        std::string points(pointResult[1].first, pointResult[1].second);
        removeDescFromPoints(points);

        return points;
    }

    // Throw error for not containing bullet points
    return "";
}

bool isBulletPointsMaxLength(const std::string msg, const int length) {
    const boost::regex pointPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    boost::smatch pointResult;

    if (boost::regex_search(msg, pointResult, pointPattern)) {
        std::string points(pointResult[1].first, pointResult[1].second);
        removeDescFromPoints(points);

        return points.length() - getBulletPointCount(points) > length;
    }

    return false;
}

bool isBulletPointsMinLength(const std::string msg, const int length) {
    const boost::regex pointPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    boost::smatch pointResult;

    if (boost::regex_search(msg, pointResult, pointPattern)) {
        std::string points(pointResult[1].first, pointResult[1].second);
        removeDescFromPoints(points);

        return points.length() - getBulletPointCount(points) < length;
    }

    return false;
}

bool containsCorrectDocFormat(const std::string msg) {
    const boost::regex docPattern("\\s?(documentation|doc[s]|todo|readme|[a-zA-Z0-9]+\\.md|[a-zA-Z0-9]+\\.txt):?\\s",
                                      boost::regex::icase);

    if (regex_match(msg, docPattern)) {
        if (msg.substr(0, 6).compare("Docs: ") != 0) {
            return false;
        }
    }

    return true;
}

bool containsCorrectNitFormat(const std::string msg) {
    const boost::regex nitPattern("\\s?(nit):?\\s", boost::regex::icase);

    if (regex_match(msg, nitPattern)) {
        if (msg.substr(0, 5).compare("Nit: ") != 0) {
            return false;
        }
    }

    return true;
}

bool containsCorrectWIPFormat(const std::string msg) {
    const boost::regex WIPPattern("\\s?(wip|work\\sin\\sprogress):?\\s", boost::regex::icase);

    if (regex_match(msg, WIPPattern)) {
        if (msg.substr(0, 5).compare("WIP: ") != 0) {
            return false;
        }
    }

    return true;
}

bool containsDescription(const std::string msg) {
    const boost::regex descPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    boost::smatch descResult;

    if (boost::regex_search(msg, descResult, descPattern)) {
        std::string description(descResult[1].first, descResult[1].second);
        removePointsFromDesc(description);

        return description.length() > 0;
    }

    return false;
}

std::string getDescription(const std::string msg) {
    const boost::regex descPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    boost::smatch descResult;

    if (boost::regex_search(msg, descResult, descPattern)) {
        std::string description(descResult[1].first, descResult[1].second);
        removePointsFromDesc(description);

        return description;
    }

    // TODO: Throw error for not containing description
    return "";
}

bool isDescriptionMaxLength(const std::string msg, const int length) {
    const boost::regex descPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    boost::smatch descResult;

    if (boost::regex_search(msg, descResult, descPattern)) {
        std::string description(descResult[1].first, descResult[1].second);
        removePointsFromDesc(description);

        return description.length() > length;
    }

    return false;
}

bool isDescriptionMinLength(const std::string msg, const int length) {
    const boost::regex descPattern("^(?:[" + VALID_MSG_CHARS + "]+\\n\\n){1}([" + VALID_MSG_CHARS + "\\n]+)");
    boost::smatch descResult;

    if (boost::regex_search(msg, descResult, descPattern)) {
        std::string description(descResult[1].first, descResult[1].second);
        removePointsFromDesc(description);

        return description.length() < length;
    }

    return false;
}

bool isFirstLetterCapitalized(const std::string msg) {
    const std::vector<std::string> excludedStrings = { "Nit:", "WIP:", "Docs:" };
    const boost::regex summaryPattern("([" + VALID_MSG_CHARS + "]+)[\n" + VALID_MSG_CHARS + "]*");
    boost::smatch summaryResult;

    if (boost::regex_search(msg, summaryResult, summaryPattern)) {
        std::string summary(summaryResult[1].first, summaryResult[1].second);

        // If one of excludedStrings is included, remove from string
        for (const std::string formatWord : excludedStrings) {
            const size_t initialPos = summary.find(formatWord);
            if (initialPos != summary.npos) {
                summary.replace(initialPos, formatWord.length(), "");
                break;
            }
        }

        // Capture initial word in summary 
        const boost::regex wordPattern("$\\s?([a-zA-Z]+).*");
        boost::smatch initialWordResult;

        if (boost::regex_search(summary, initialWordResult, wordPattern)) {
            const std::string initialWord(initialWordResult[1].first, initialWordResult[1].second);

            return isupper(initialWord[0]);
        }

        // Return true if first set of characters is not a word
        return true;
    }

    return false;
}

bool containsSummary(const std::string msg) {
    const boost::regex summaryPattern("^([" + VALID_MSG_CHARS + "]+\n?){1}");
    return regex_match(msg, summaryPattern);
}

std::string getSummary(const std::string msg) {
    const boost::regex summaryPattern("^([" + VALID_MSG_CHARS + "]+\n?){1}");
    boost::smatch summaryResult;

    if (boost::regex_search(msg, summaryResult, summaryPattern)) {
        const std::string summary(summaryResult[1].first, summaryResult[1].second);
        return summary;
    }

    // TODO: Throw error for not containg summary
    return "";
}

bool isSummaryMaxLength(const std::string msg, const int length) {
    const boost::regex summaryPattern("^([" + VALID_MSG_CHARS + "]+\n?){1}");
    boost::smatch summaryResult;

    if (boost::regex_search(msg, summaryResult, summaryPattern)) {
        const std::string summary(summaryResult[1].first, summaryResult[1].second);

        return summary.length() > length;
    }

    return false;
}

bool isSummaryMinLength(const std::string msg, const int length) {
    const boost::regex summaryPattern("^([" + VALID_MSG_CHARS + "]+\n?){1}");
    boost::smatch summaryResult;

    if (boost::regex_search(msg, summaryResult, summaryPattern)) {
        const std::string summary(summaryResult[1].first, summaryResult[1].second);

        return summary.length() < length;
    }

    return false;
}
